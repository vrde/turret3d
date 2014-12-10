#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>
#include "LightPanel.h"
#include "Explosion3D.h"

Explosion3D::Explosion3D(float _ray, float _x, float _y, float _z) : Object3D(_x, _y, _z), timeToLive(500.0f), ray(_ray) {
	
}

void Explosion3D::draw() {
	float elapsedTime = glutGet(GLUT_ELAPSED_TIME) - creationTime;
	if(elapsedTime > timeToLive) {
		exists = false;
		return;
	}
	//risposta della primitiva
	GLfloat ambiente[4] = {0.9, 0.9, 0.0, 1 - elapsedTime / timeToLive};
	GLfloat direttiva[4] = {0.9, 0.9, 0.0, 1 - elapsedTime / timeToLive};
	GLfloat brillante[4] = {0.0, 0.0, 0.0, 1 - elapsedTime / timeToLive};

	//rappresenta la brillantezza dell'oggetto,
	//controlla il "cono" di risposta della luce
	//speculare. Piu` l'oggetto e` liscio piu` il cono e` stretto
	//piu` e opaco piu` e` largo.
	glMateriali(GL_FRONT, GL_SHININESS, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);

	float currentRay = ray + 2 * ray * elapsedTime / timeToLive;
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glTranslatef(
		pPosition->coords[0],\
		pPosition->coords[1],\
		pPosition->coords[2]);
	glutSolidSphere(currentRay, 16, 16);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}

Explosion3D::~Explosion3D() {
}
