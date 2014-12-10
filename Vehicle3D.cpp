#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>

#include "Vehicle3D.h"
#include "Vector.h"
#include "tgautils.h"

using namespace std;
Vehicle3D::Vehicle3D(Vehicle* _pVehicle) : Entity3D(_pVehicle) {
	loadTex();
	createDisplayList();
}

void Vehicle3D::draw() {
	float rotation = 0;
	Vector* pVelocity = pEntity->getVelocity();
	glPushMatrix();
	//glDisable(GL_TEXTURE_2D);
	//risposta della primitiva
	GLfloat ambiente[4] = {0.2, 0.2, 0.2, 1};
	GLfloat direttiva[4] = {0.7, 0.7, 0.7, 1};
	GLfloat brillante[4] = {0.0, 0.0, 0.0, 1};

	glMateriali(GL_FRONT, GL_SHININESS, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
	glTranslatef(pEntity->getX(), pEntity->getY(), pEntity->getZ());

	if( (pVelocity->coords[0] == 0) && (pVelocity->coords[2] >= 0) )
		rotation = -90;
	else if( (pVelocity->coords[0] == 0) && (pVelocity->coords[2] < 0) )
		rotation = 90;
	else if(pVelocity->coords[0] > 0)
		rotation =  atan(pVelocity->coords[2] / pVelocity->coords[0]) * 57.295779;
	else
		rotation = 180.0 + atan(pVelocity->coords[2] / pVelocity->coords[0]) * 57.295779;
	//cout << rotation << " ";
	glRotatef(-rotation, 0, 1, 0);
	glScalef(1, 2, 1);
	glTranslatef(3, 0, 2);
	glCallList(displayList[CATERPILLAR]);
	glTranslatef(0, 0, -4);
	glCallList(displayList[CATERPILLAR]);
	glTranslatef(0, 0.5,  2);
	glCallList(displayList[BODY]);
	//glEnable(GL_TEXTURE_2D);

	glPopMatrix();
}

Vehicle3D::~Vehicle3D() {}

void Vehicle3D::loadTex() {
	if(Vehicle3D::texture[0] != 0) return;
	Vehicle3D::texture[0] = load_tex("tex/cat.tga", true);
	Vehicle3D::texture[1] = load_tex("tex/rusty.tga", true);
}

void Vehicle3D::createDisplayList() {
	if(displayList[CATERPILLAR] != 0) return;
	displayList[CATERPILLAR] = DisplayListPanel::getInstance()->getUniqueInt();

	glNewList(displayList[CATERPILLAR], GL_COMPILE);
	GLfloat ambiente[4] = {0.3, 0.3, 0.3, 1};
	GLfloat direttiva[4] = {0.4, 0.4, 0.4, 1};
	GLfloat brillante[4] = {0.0, 0.0, 0.0, 1};

	glMateriali(GL_FRONT, GL_SHININESS, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glTranslatef(0, 0,  1);	
	glBegin(GL_QUADS);
	//parete laterale
		glNormal3f(0, 0, 1);
		glVertex3f(-3.5,   0, 0);
		glVertex3f(   0,   0, 0);
		glVertex3f(   1,   1, 0);
		glVertex3f(  -4, 0.5, 0);
	//altra parete laterale
		glNormal3f(0, 0, -1);
		glVertex3f(-3.5,   0, -2);
		glVertex3f(  -4, 0.5, -2);
		glVertex3f(   1,   1, -2);
		glVertex3f(   0,   0, -2);
	//parte superiore
		glNormal3f(0, 1, 0);
		glTexCoord2f(1, 0); glVertex3f(  -4, 0.5,  0);
		glTexCoord2f(1, 1); glVertex3f(   1,   1,  0);
		glTexCoord2f(0, 1); glVertex3f(   1,   1, -2);
		glTexCoord2f(0, 0); glVertex3f(  -4, 0.5, -2);
	//parte inferiore
		glNormal3f(0, -1, 0);
		glVertex3f(-3.5, 0, 0);
		glVertex3f(-3.5, 0,-2);
		glVertex3f(   0, 0,-2);
		glVertex3f(   0, 0, 0);
	//parte anteriore
		glNormal3f(0.7, -0.7, 0);
		glTexCoord2f(0, 0); glVertex3f(   0, 0,  0);
		glTexCoord2f(1, 0); glVertex3f(   0, 0, -2);
		glTexCoord2f(1, 1); glVertex3f(   1, 1, -2);
		glTexCoord2f(0, 1); glVertex3f(   1, 1,  0);
	//parte posteriore
		glNormal3f(-0.7, -0.7, 0);
		glVertex3f(  -4, 0.5, 0);
		glVertex3f(  -4, 0.5,-2);
		glVertex3f(-3.5, 0,-2);
		glVertex3f(-3.5, 0, 0);
	glEnd();
	glPopMatrix();
	glEndList();

	displayList[BODY] = DisplayListPanel::getInstance()->getUniqueInt();
	glNewList(displayList[BODY], GL_COMPILE);
	//ambiente4] = {0.3, 0.3, 0.3, 1};
	//direttiva[4] = {0.4, 0.4, 0.4, 1};
	//brillante[4] = {0.0, 0.0, 0.0, 1};

	glMateriali(GL_FRONT, GL_SHININESS, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTranslatef(0, 0,  2);	
	glBegin(GL_QUADS);
	//parete laterale
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 0); glVertex3f(  -3,   0, 0);
		glTexCoord2f(1, 0); glVertex3f(   0,   0, 0);
		glTexCoord2f(1, 1); glVertex3f(   0,   1, 0);
		glTexCoord2f(0, 1); glVertex3f(  -3,   1, 0);
	//altra parete laterale
		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 0); glVertex3f(  -3,   0,-4);
		glTexCoord2f(0, 1); glVertex3f(  -3,   1,-4);
		glTexCoord2f(1, 1); glVertex3f(   0,   1,-4);
		glTexCoord2f(1, 0); glVertex3f(   0,   0,-4);
	//parte superiore
		glNormal3f(0, 1, 0);
		glTexCoord2f(0, 0); glVertex3f(  -3,   1,  0);
		glTexCoord2f(1, 0); glVertex3f(   0,   1,  0);
		glTexCoord2f(1, 1); glVertex3f(   0,   1, -4);
		glTexCoord2f(0, 1); glVertex3f(  -3,   1, -4);
	//parte inferiore
		glNormal3f(0, -1, 0);
		glVertex3f(  -3,   0,  0);
		glVertex3f(  -3,   0, -4);
		glVertex3f(   0,   0, -4);
		glVertex3f(   0,   0,  0);
	//parte anteriore
		glNormal3f(1, 0, 0);
		glTexCoord2f(0, 0); glVertex3f(   0, 0,  0);
		glTexCoord2f(0, 1); glVertex3f(   0, 0, -4);
		glTexCoord2f(1, 1); glVertex3f(   0, 1, -4);
		glTexCoord2f(1, 0); glVertex3f(   0, 1,  0);
	//parte posteriore
		glNormal3f(-1, 0, 0);
		glVertex3f(  -3, 0,  0);
		glVertex3f(  -3, 1,  0);
		glVertex3f(  -3, 1, -4);
		glVertex3f(  -3, 0, -4);
	glEnd();
	glPopMatrix();
	glEndList();
}

GLuint Vehicle3D::texture[2];
GLuint Vehicle3D::displayList[2] = {0, 0};

