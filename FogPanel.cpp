#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "FogPanel.h"

FogPanel* FogPanel::instance = 0;

FogPanel* FogPanel::getInstance() {
	if(instance == 0) {
		instance = new FogPanel();
	}
	return instance;
}

FogPanel::FogPanel() {
	array[0] = 1;
	array[1] = 1;
	array[2] = 1;
	array[3] = 1;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	/*
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, array);
	glFogf(GL_FOG_DENSITY, 0.35f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 10.0f);
	glFogf(GL_FOG_END, 20.0f);
	*/
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, array);
	glFogf(GL_FOG_DENSITY, 0.01f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glDisable(GL_FOG);
}

void FogPanel::enable() {
	glEnable(GL_FOG);
}
void FogPanel::disable() {
	glDisable(GL_FOG);
}

void FogPanel::setColor(float _r, float _g, float _b, float _a) {
	array[0] = _r;
	array[1] = _g;
	array[2] = _b;
	array[3] = _a;
	glFogfv(GL_FOG_COLOR, array);
	glClearColor(_r, _g, _b, _a);
}

void FogPanel::setDensity(float _density) {
	glFogf(GL_FOG_DENSITY, _density);
}

void FogPanel::setStart(float _start) {
	glFogf(GL_FOG_START, _start);
}

void FogPanel::setEnd(float _end) {
	glFogf(GL_FOG_END, _end);
}
