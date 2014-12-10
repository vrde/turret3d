#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "Turret3D.h"

#include "DisplayListPanel.h"
#include "LightPanel.h"
#include "tgautils.h"

#define NUM_STEP 16
#define RAGGIO 0.5f
#define ALT 4.0f

Turret3D::Turret3D(Turret* _pTurret) : Entity3D(_pTurret) {
	LightPanel* lp = LightPanel::getInstance();
	lp->setPosition(GL_LIGHT0,
		0,
		pEntity->getTerrain()->getHeightOf(0, 0) + 10,
		-5
	);
	lp->enable(GL_LIGHT0);
	lp->setAmbient(GL_LIGHT0, 0.7, 0.7, 0.4, 1);
	loadTex();
	createDisplayList();
}

void Turret3D::draw() {
	glPushMatrix();
	glTranslatef(pEntity->getX(), pEntity->getY(), pEntity->getZ());
	
	glCallList(displayList[BASE]);

	glTranslatef(0, 3, 0);
	glRotatef(((Turret*)pEntity)->getRotation(), 0, 1, 0);
	glRotatef(-90+((Turret*)pEntity)->getSight(), 1, 0, 0);

	glCallList(displayList[CANNON]);

	glPopMatrix();
}

void Turret3D::loadTex() {
	if(Turret3D::texture[0] != 0) return;
	Turret3D::texture[0] = load_tex("tex/muro.tga", true);
	Turret3D::texture[1] = load_tex("tex/sphere.tga", true);
	Turret3D::texture[2] = load_tex("tex/tetto.tga", true);
}

void Turret3D::createDisplayList() {
	if(displayList[BASE] != 0) return;
	displayList[BASE] = DisplayListPanel::getInstance()->getUniqueInt();

	glNewList(displayList[BASE], GL_COMPILE);
	GLfloat ambiente[4] = {0.3, 0.3, 0.3, 1};
	GLfloat direttiva[4] = {0.6, 0.5, 0.5, 1};
	GLfloat brillante[4] = {0.7, 0.7, 0.7, 1};

	glMateriali(GL_FRONT, GL_SHININESS, 30);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, direttiva);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brillante);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
		glNormal3f( 0, 0.3,  0.95);
		glTexCoord2f(0.0f/6, 0.0f/6); glVertex3f(-3, 0,  3);
		glTexCoord2f(6.0f/6, 0.0f/6); glVertex3f( 3, 0,  3);
		glTexCoord2f(5.0f/6, 3.0f/6); glVertex3f( 2, 3,  2);
		glTexCoord2f(1.0f/6, 3.0f/6); glVertex3f(-2, 3,  2);

		glNormal3f( 0.95, 0.3,  0);
		glTexCoord2f(0.0f/6, 0.0f/6); glVertex3f( 3, 0,  3);
		glTexCoord2f(-6.0f/6, 0.0f/6); glVertex3f( 3, 0, -3);
		glTexCoord2f(-5.0f/6, -3.0f/6); glVertex3f( 2, 3, -2);
		glTexCoord2f(-1.0f/6, -3.0f/6); glVertex3f( 2, 3,  2);
		
		glNormal3f( 0, 0.3, -0.95);
		glTexCoord2f(0.0f/6, 0.0f/6); glVertex3f( 3, 0, -3);
		glTexCoord2f(6.0f/6, 0.0f/6); glVertex3f(-3, 0, -3);
		glTexCoord2f(5.0f/6, 3.0f/6); glVertex3f(-2, 3, -2);
		glTexCoord2f(1.0f/6, 3.0f/6); glVertex3f( 2, 3, -2);

		glNormal3f(-0.95, 0.3,  0);
		glTexCoord2f(0.0f/6, 0.0f/6); glVertex3f(-3, 0, -3);
		glTexCoord2f(-6.0f/6, 0.0f/6); glVertex3f(-3, 0,  3);
		glTexCoord2f(-5.0f/6, -3.0f/6); glVertex3f(-2, 3,  2);
		glTexCoord2f(-1.0f/6, -3.0f/6); glVertex3f(-2, 3, -2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
		glNormal3f( 0, 1,  0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-2, 3,  2);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 2, 3,  2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 2, 3, -2);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-2, 3, -2);
	glEnd();

	glEndList();

	displayList[CANNON] = DisplayListPanel::getInstance()->getUniqueInt();
	glNewList(displayList[CANNON], GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glutSolidSphere(1.5, 16, 16);
	glBegin(GL_QUAD_STRIP);
	float incA = 6.28f / NUM_STEP;
	for(float a = 0; a < 6.27f; a += incA) {
		glNormal3f(sin(a), 0, cos(a));
		glVertex3f(RAGGIO * sin(a), ALT, RAGGIO * cos(a));
		glVertex3f(RAGGIO * sin(a), 0, RAGGIO * cos(a));
	}
	glNormal3f(0, 0, 1);
	glVertex3f(0, ALT, RAGGIO);
	glVertex3f(0, 0, RAGGIO);
	glEnd();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glEndList();
}

GLuint Turret3D::texture[3];
GLuint Turret3D::displayList[2] = {0, 0};

Turret3D::~Turret3D() {}
