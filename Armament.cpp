#include "Armament.h"
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#define PI_OVER_180 0.01745329f

Armament::Armament(Entity* _pEntity) : pEntity(_pEntity) {
	//pBullets = new list<Bullet*>;
	lastFire = 0;
	fireDelta = 1000;
}

float Armament::getSight() {
	return sight;
}

void Armament::setSight(float _sight) {
	sight = _sight;
}

float Armament::getRotation() {
	return rotation;
}

void Armament::setRotation(float _rotation) {
	rotation = _rotation;
}

Bullet* Armament::fire() {
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	if( (currentTime - lastFire) < fireDelta ) return 0;
	else {
		lastFire = currentTime;
		return new Bullet(0.3f, 0, pEntity->getTerrain()->getHeightOf(0, 0) + 5, 0,\
			cos(-(rotation + 90)* PI_OVER_180)*25,\
			sin(sight * PI_OVER_180)*25,\
			sin(-(rotation + 90)* PI_OVER_180)*25,
			pEntity->getTerrain());
	}
}

Armament::~Armament() {
	//delete pBullets;
}
