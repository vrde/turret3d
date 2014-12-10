#include "Controller.h"
#include "Explosion3D.h"
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cstdio>

using namespace std;

#define PI_OVER_180 0.01745329f
#define AMBIENT_R 0.5
#define AMBIENT_G 0.5
#define AMBIENT_B 0.5
#define AMBIENT_A 1

Controller::Controller(int width, int height) {
	pEntities = new list<Entity*>;
	pBullets = new list<Bullet*>;
	pTerrain = new Terrain(300, 300);
	pTurret = new Turret(2.0f, 0.0f, 0.0f, 0.0f, pTerrain);

	pEntities3D = new list<Entity3D*>;
	pTerrain3D = new Terrain3D(pTerrain);
	pTurret3D = new Turret3D(pTurret);

	pObjects3D = new list<Object3D*>;
	lightPanel = LightPanel::getInstance();

	fogPanel = FogPanel::getInstance();
	fogPanel->enable();

	lastTime = glutGet(GLUT_ELAPSED_TIME);

	creationDelay = 5000;
	shakeDelay = 0.500;

	povX = 0;
	povY = 10;
	povZ = 30;
	povRotX = 10;

	turretSight = 0;
	turretRotation = 0;
	mouseLastY = 0;
	mouseLastX = 0;

	windowWidth = width;
	windowHeight = height;

	currentState = PLAYING;
	captureMouse = true;

	createVehicle();
}

void Controller::mouseEvent(int x, int y) {
	if(!captureMouse) return;
	turretSight += (float)(mouseLastY - (y-windowHeight/2)) / 10;
	if(turretSight < -20) turretSight = -20;
	else if(turretSight > 45) turretSight = 45;
	turretRotation += (float)(mouseLastX - (x-windowWidth/2)) / 10;
}

void Controller::processMouse(int button, int state, int x, int y) {
	if (state != GLUT_DOWN) return;
	if (currentState == LOST) return;
	Bullet* b = pTurret->getArmament()->fire();
	if(b != 0) {
		pBullets->push_back(b);
		pEntities3D->push_back( new Bullet3D(b) );
	}
}

void Controller::keyPressed(unsigned char key, int x, int y) {
	switch(key) {
		case 'w':
			if(povZ >= 80) povZ = 80;
			else povZ+=0.5;
			break;
		case 's':
			if(povZ <= 20) povZ = 20;
			else povZ-=0.5;
			break;
		case 'm':
			captureMouse = not(captureMouse);
			if(captureMouse) glutSetCursor(GLUT_CURSOR_NONE);
			else glutSetCursor(GLUT_CURSOR_DESTROY);
			break;
	}
}

void Controller::idleFunction() {
	dt = (glutGet(GLUT_ELAPSED_TIME) - lastTime) / 1000;

	if(glutGet(GLUT_ELAPSED_TIME) - lastCreation >= creationDelay) {
		createVehicle();
		if(creationDelay < 4000) creationDelay = 4000;
			creationDelay -= 50;
	}
	list<Entity*>::iterator i;
	list<Bullet*>::iterator b;
	list<Entity3D*>::iterator j;
	list<Object3D*>::iterator o;

	////////////////////////////////////////
	//elimino gli elementi che non servono//
	////////////////////////////////////////

	//dalla vista
	for(j = pEntities3D->begin(); j != pEntities3D->end(); ) {
		Entity* e = (*j)->getEntity();
		if(!e->getExists()) {
			delete (*j);
			j = pEntities3D->erase(j);
		}
		else j++;
	}
	for(o = pObjects3D->begin(); o != pObjects3D->end(); ) {
		if(!(*o)->getExists()) {
			delete (*o);
			o = pObjects3D->erase(o);
		}
		else o++;

	}
	//dal modello
	for(b = pBullets->begin(); b != pBullets->end(); )
		if(!((*b)->getExists())) {
			delete (*b);
			b = pBullets->erase(b);
		}
		else b++;

	for(i = pEntities->begin(); i != pEntities->end(); )
		if(!((*i)->getExists())) {
			delete (*i);
			i = pEntities->erase(i);
		}
		else i++;

	///////////////////////////////
	//calcoli relativi al modello//
	///////////////////////////////

	//
	//ricalcolo le posizioni
	//
	pTurret->setSight(turretSight);
	pTurret->setRotation(turretRotation);

	//effettuo i nuovi calcoli per la torretta
	pTurret->calc(dt);

	//per tutti i proiettili
	for(b = pBullets->begin(); b != pBullets->end(); b++)
		(*b)->calc(dt);
	
	//e per il resto delle entita`
	for(i = pEntities->begin(); i != pEntities->end(); i++)
		(*i)->calc(dt);


	//
	//controllo le collisioni
	//
	
	//dei proiettili con il suolo oppure con gli altri veicoli
	for(b = pBullets->begin(); b != pBullets->end(); b++)
		if( ((*b)->getY() + (*b)->getRay())< pTerrain->getHeightOf((*b)->getX(), (*b)->getZ()) ) {
			(*b)->setExists(false);
			pObjects3D->push_back( new Explosion3D(2, (*b)->getX(), (*b)->getY(), (*b)->getZ()) );
		}
	for(b = pBullets->begin(); b != pBullets->end(); b++)
		for(i = pEntities->begin(); i != pEntities->end(); i++)
			if( (*b)->isCollidingWith((*i)) ) {
				(*b)->setExists(false);
				(*i)->setExists(false);
				pObjects3D->push_back( new Explosion3D(4, (*b)->getX(), (*b)->getY(), (*b)->getZ()) );
				shakeDelay = 0.499;
			}
	//controllo che i carri non siano arrivati alla torretta
	for(i = pEntities->begin(); i != pEntities->end(); i++) {
		if( ((*i)->isCollidingWith(pTurret)) && (currentState == PLAYING)) {
			currentState = LOST;
			pObjects3D->push_back( new Explosion3D(6, 0, pTerrain->getHeightOf(0, 0), 0));
		}
	}
	///////////////////////////////
	//calcoli relativi alla vista//
	///////////////////////////////
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//posiziono il mondo in relazione
	//alla rotazione data dal mouse
	float noise = 0;
	if( (shakeDelay > 0) && (shakeDelay < 0.5)) {
		shakeDelay -= dt;
		noise = sin(rand())/4;
		lightPanel->setGlobalAmbient(
			AMBIENT_R + noise/2,
			AMBIENT_G + noise/2,
			AMBIENT_B + noise/2,
			AMBIENT_A);
	}
	else {
		shakeDelay = 0.5;
		pTerrain3D->night(lastTime/100000);
	}
	glTranslatef(-povX+noise, -pTerrain->getHeightOf(0, 0)-povY+noise, -povZ+noise);
	glRotatef( povRotX, 1, 0, 0);
	//glRotatef(-turretSight, 1, 0, 0);
	glRotatef(-turretRotation, 0, 1, 0);


	pTerrain3D->draw();

	if(currentState == PLAYING)
		pTurret3D->draw();
	
	for(j = pEntities3D->begin(); j != pEntities3D->end(); j++)
		(*j)->draw();

	for(o = pObjects3D->begin(); o != pObjects3D->end(); o++) 
		(*o)->draw();

	lastTime = glutGet(GLUT_ELAPSED_TIME);

	if(captureMouse)
		glutWarpPointer(windowWidth/2, windowHeight/2);

	glutSwapBuffers();
}

void Controller::setWindowWidth(int width) {
	windowWidth = width;
}

void Controller::setWindowHeight(int height) {
	windowHeight = height;
}

void Controller::createVehicle() {
	float sign = rand() % 2 == 0 ? 1 : -1;
	float x = sign * ((int)fabs(rand()) % 50 + 50);
	sign = rand() % 2 == 0 ? 1 : -1;
	float z = sign * ((int)fabs(rand()) % 50 + 50);

	float vel = ((float)rand() / RAND_MAX) * 5 + 1;
	Vector v = Vector(x, 0, z);
	v.normalize();
	v.coords[0] *= -vel;
	v.coords[2] *= -vel;

	Vehicle* vehicle = new Vehicle(4.0, x, 0, z, v.coords[0], 0, v.coords[2], pTerrain);
	pEntities->push_back(vehicle);
	pEntities3D->push_back( new Vehicle3D(vehicle) );
	lastCreation = glutGet(GLUT_ELAPSED_TIME);
}

void Controller::printInfo() {
	glPushMatrix();
	glTranslatef(0, 0, -1);
	char buf[80];
	sprintf(buf, "FPS: %f", 1.0f/dt);
	printString(buf, 0, 0);
	sprintf(buf, "enemies: %d", pEntities->size());
	printString(buf, 0, 1);
	glPopMatrix();
}

void Controller::printString(char *str, float x, float y) {
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(0, 0, -1);
	glColor3f(1, 1, 1);
	glTranslatef(x, y, 0);
	glScalef(0.0002, 0.0002, 0.0002);

	char *p;
	for (p = str; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	glEnable(GL_LIGHTING); 
	glPopMatrix();
}

Controller::~Controller() {
	delete pTerrain;
	delete pTurret;
	list<Entity*>::iterator i;
	for(i = pEntities->begin(); i != pEntities->end(); i++)
		delete (*i);

	delete pTerrain3D;
	delete pTurret3D;
	list<Entity3D*>::iterator j;
	for(j = pEntities3D->begin(); j != pEntities3D->end(); j++)
		delete (*j);

	list<Object3D*>::iterator o;
	for(o = pObjects3D->begin(); o != pObjects3D->end(); o++) 
		delete (*o);

	list<Bullet*>::iterator b;
	for(b = pBullets->begin(); b != pBullets->end(); b++)
		delete (*b);

	delete pEntities;
	delete pEntities3D;
	delete pObjects3D;
	delete pBullets;
	delete lightPanel;
	delete fogPanel;
	delete DisplayListPanel::getInstance();
}
