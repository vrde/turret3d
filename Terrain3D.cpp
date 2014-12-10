#include "Terrain3D.h"
#include "tgautils.h"
#include <stdlib.h>

#define A_R 0.7
#define A_G 0.7
#define A_B 0.4
#define A_A 1

Terrain3D::Terrain3D(Terrain* _pTerrain) : pTerrain(_pTerrain) {
	//calcolo delle normali per il terreno
	xMul = pTerrain->getWidth() / pTerrain->getCols();
	zMul = pTerrain->getLength() / pTerrain->getRows();

	for(int i = 1; i < MAX_X-1; i++)
		for(int j = 1; j < MAX_Z-1; j++) {
			float h = pTerrain->values[i][j];
			Vector v1(1*xMul, pTerrain->values[i+1][j] - h, 0);
			Vector v2(0, pTerrain->values[i][j-1] - h, -1*zMul);
			Vector v3(-1*xMul, pTerrain->values[i-1][j] - h, 0);
			Vector v4(0, pTerrain->values[i][j+1] - h, 1*zMul);
			
			Vector v12 = Vector::crossProd(v1, v2);
			Vector v23 = Vector::crossProd(v2, v3);
			Vector v34 = Vector::crossProd(v3, v4);
			Vector v41 = Vector::crossProd(v4, v1);

			v12.normalize();
			v23.normalize();
			v34.normalize();
			v41.normalize();

			Vector n = Vector(
				v12.coords[0] + v23.coords[0] + v34.coords[0] + v41.coords[0],
				v12.coords[1] + v23.coords[1] + v34.coords[1] + v41.coords[1],
				v12.coords[2] + v23.coords[2] + v34.coords[2] + v41.coords[2]
				);
			n.normalize();
			normals[i][j] = n;
		}

	LightPanel::getInstance()->setGlobalAmbient(A_R, A_G, A_B, A_A);
	FogPanel::getInstance()->enable();
	FogPanel::getInstance()->setDensity(0);
	FogPanel::getInstance()->setColor(1, 1, 1, 1);
	loadTex();
	createDisplayList();
}

void Terrain3D::draw() {
	glCallList(displayList[TERRAIN]);
	if(daylight) {
		glCallList(displayList[SKYBOX]);
	}
}

void Terrain3D::night(float _p) {
	if( (_p < 0) || (_p > 1) ) return;
	LightPanel::getInstance()->setGlobalAmbient(A_R-_p, A_G-_p, A_B-_p, A_A-_p);
	FogPanel::getInstance()->setColor(1-_p, 1-_p, 1-_p, 1);
	FogPanel::getInstance()->setDensity(_p/100);
	if(_p > 0.99) daylight = false;
	else daylight = true;
}

void Terrain3D::loadTex() {
	if(Terrain3D::texture[0] != 0) return;
	Terrain3D::texture[0] = load_tex("tex/terrain.tga", true);
	Terrain3D::texSkybox[BACK] = load_tex("tex/bk.tga");
	Terrain3D::texSkybox[FRONT] = load_tex("tex/ft.tga");
	Terrain3D::texSkybox[LEFT] = load_tex("tex/lt.tga");
	Terrain3D::texSkybox[RIGHT] = load_tex("tex/rt.tga");
	Terrain3D::texSkybox[UP] = load_tex("tex/up.tga");
}

void Terrain3D::createDisplayList() {
	if(displayList[TERRAIN] != 0) return;
	displayList[TERRAIN] = DisplayListPanel::getInstance()->getUniqueInt();
	glNewList(displayList[TERRAIN], GL_COMPILE);
	glPushMatrix();

	glTranslatef(-pTerrain->width/2, 0, -pTerrain->length/2);
	/*
	 * togli il commento se vuoi vedere le normali
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	for(int i = 0; i < MAX_X; i++)
		for(int j = 0; j < MAX_Z; j++) {
			glVertex3f(i*xMul, pTerrain->values[i][j], j*zMul);
			glVertex3f(
				i*xMul + normals[i][j].coords[0],
				pTerrain->values[i][j] + normals[i][j].coords[1],
				j*zMul + normals[i][j].coords[2]);
		}
	glEnd();
	*/
	//
	//risposta della primitiva
	GLfloat ambiente[4] = {0.3, 0.6, 0.3, 1};
	GLfloat direttiva[4] = {0.4, 0.5, 0.0, 1};
	GLfloat brillante[4] = {0.0, 0.0, 0.0, 1};
	glMateriali(GL_FRONT, GL_SHININESS, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);

	glBindTexture(GL_TEXTURE_2D, Terrain3D::texture[0]);

	for(int i = 0; i < MAX_X-1; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for(int j = 0; j < MAX_Z-1; j++) {
			glNormal3fv(normals[i][j].coords);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(i*xMul, pTerrain->values[i][j], j*zMul);

			glNormal3fv(normals[i][j+1].coords);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(i*xMul, pTerrain->values[i][j+1], (j+1)*zMul);
			
			glNormal3fv(normals[i+1][j].coords);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f((i+1)*xMul, pTerrain->values[i+1][j], j*zMul);
			
			glNormal3fv(normals[i+1][j+1].coords);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f((i+1)*xMul, pTerrain->values[i+1][j+1], (j+1)*zMul);

		}
		glEnd();
	}
	glPopMatrix();
	glEndList();
	
	////////////
	// Skybox //
	////////////
	displayList[SKYBOX] = DisplayListPanel::getInstance()->getUniqueInt();
	glNewList(displayList[SKYBOX], GL_COMPILE);
	glPushMatrix();
	glDisable(GL_LIGHTING);

	glTranslatef(0, pTerrain->getHeightOf(0, 0)/2-10, 0);
	glScalef(pTerrain->width/2, pTerrain->width/2, pTerrain->length/2);	
	float r = 1.005;
	glBindTexture(GL_TEXTURE_2D, Terrain3D::texSkybox[FRONT]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(-r, r, -r);
		glTexCoord2f(0, 0);
		glVertex3f(-r, -r, -r);
		glTexCoord2f(1, 0);
		glVertex3f(r,  -r, -r);
		glTexCoord2f(1, 1);
		glVertex3f(r, r, -r);
	glEnd();

	glRotatef(90, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, Terrain3D::texSkybox[RIGHT]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(-r, r, -r);
		glTexCoord2f(0, 0);
		glVertex3f(-r, -r, -r);
		glTexCoord2f(1, 0);
		glVertex3f(r,  -r, -r);
		glTexCoord2f(1, 1);
		glVertex3f(r, r, -r);
	glEnd();

	glRotatef(90, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, Terrain3D::texSkybox[BACK]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(-r, r, -r);
		glTexCoord2f(0, 0);
		glVertex3f(-r, -r, -r);
		glTexCoord2f(1, 0);
		glVertex3f(r,  -r, -r);
		glTexCoord2f(1, 1);
		glVertex3f(r, r, -r);
	glEnd();

	glRotatef(90, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, Terrain3D::texSkybox[LEFT]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(-r, r, -r);
		glTexCoord2f(0, 0);
		glVertex3f(-r, -r, -r);
		glTexCoord2f(1, 0);
		glVertex3f(r,  -r, -r);
		glTexCoord2f(1, 1);
		glVertex3f(r, r, -r);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Terrain3D::texSkybox[UP]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-r,  r, -r);
		glTexCoord2f(1, 0);
		glVertex3f( r,  r, -r);
		glTexCoord2f(1, 1);
		glVertex3f( r,   r, r);
		glTexCoord2f(0, 1);
		glVertex3f(-r,  r,  r);
	glEnd();
	
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glEndList();
}

GLuint Terrain3D::texture[1];
GLuint Terrain3D::texSkybox[6];
GLuint Terrain3D::displayList[2] = {0, 0};

Terrain3D::~Terrain3D() {}
