#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "LightPanel.h"

LightPanel* LightPanel::instance = 0;

LightPanel* LightPanel::getInstance() {
	if(instance == 0) {
		instance = new LightPanel();
	}
	return instance;
}

LightPanel::LightPanel() {
	array[0] = 0;
	array[1] = 0;
	array[2] = 0;
	array[3] = 1;
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, array);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
}

void LightPanel::enable(int _light) {
	glEnable(_light);
}
void LightPanel::disable(int _light) {
	glDisable(_light);
}
	
void LightPanel::setPosition(int _light, float _x, float _y, float _z) {
	array[0] = _x;
	array[1] = _y;
	array[2] = _z;
	array[3] = 1;
	glLightfv(_light, GL_POSITION, array);
}

void LightPanel::setAmbient(int _light, float _r, float _g, float _b, float _a) {
	array[0] = _r;
	array[1] = _g;
	array[2] = _b;
	array[3] = _a;
	glLightfv(_light, GL_AMBIENT, array);
}

void LightPanel::setDiffuse(int _light, float _r, float _g, float _b, float _a) {
	array[0] = _r;
	array[1] = _g;
	array[2] = _b;
	array[3] = _a;
	glLightfv(_light, GL_DIFFUSE, array);
}

void LightPanel::setSpecular(int _light, float _r, float _g, float _b, float _a) {
	array[0] = _r;
	array[1] = _g;
	array[2] = _b;
	array[3] = _a;
	glLightfv(_light, GL_SPECULAR, array);
}

void LightPanel::setGlobalAmbient(float _r, float _g, float _b, float _a) {
	array[0] = _r;
	array[1] = _g;
	array[2] = _b;
	array[3] = _a;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, array);
}
