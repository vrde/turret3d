#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Bullet3D.h"
#include "LightPanel.h"

Bullet3D::Bullet3D(Bullet* _pBullet) : Entity3D(_pBullet) {}

void Bullet3D::draw() {
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	LightPanel* l = LightPanel::getInstance();
	l->enable(GL_LIGHT7);
	l->setDiffuse(GL_LIGHT7, 1, 0, 0, 1);
	l->setPosition(GL_LIGHT7, pEntity->getX(), pEntity->getY(), pEntity->getZ());
	glTranslatef(pEntity->getX(), pEntity->getY(), pEntity->getZ());
	//glRotatef(glutGet(GLUT_ELAPSED_TIME)/100, 0, 1, 0);
	GLfloat ambiente[4] = {0.5, 0.5, 0.5, 1};
	GLfloat direttiva[4] = {0.6, 0.6, 0.6, 1};
	GLfloat brillante[4] = {0.9, 0.9, 0.9, 1};

	glMateriali(GL_FRONT, GL_SHININESS, 10);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
	//glutSolidTeapot(3);
	glutSolidSphere(pEntity->getRay(), 8, 8);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

Bullet3D::~Bullet3D() {
	LightPanel::getInstance()->disable(GL_LIGHT7);
}
