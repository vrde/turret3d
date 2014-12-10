#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Object3D.h"

Object3D::Object3D(float _x, float _y, float _z) {
	pPosition = new Vector(_x, _y, _z);
	creationTime = glutGet(GLUT_ELAPSED_TIME);
	exists = true;
}

bool Object3D::getExists() {
	return exists;
}

Object3D::~Object3D() {
	delete pPosition;
}

