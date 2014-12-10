#include "Turret.h"

Turret::Turret(float _ray, float _x, float _y, float _z, Terrain* _pTerrain) :
	Vehicle(_ray, _x, _y, _z, 0.0f, 0.0f, 0.0f, _pTerrain) {
	pPosition->coords[1] = pTerrain->getHeightOf(_x, _z);
}

Turret::Turret(float _ray, float _x, float _y, float _z, float _vx, float _vy, float _vz, Terrain* _pTerrain) :
	Vehicle(_ray, _x, _y, _z, _vx, _vy, _vz, _pTerrain) {
	pPosition->coords[1] = pTerrain->getHeightOf(_x, _z);
}

float Turret::getSight() {
	return sight;
}

void Turret::setSight(float _sight) {
	sight = _sight;
	pArmament->setSight(_sight);
}

float Turret::getRotation() {
	return rotation;
}

void Turret::setRotation(float _rotation) {
	rotation = _rotation;
	pArmament->setRotation(_rotation);
}

void Turret::calc(float _dt) {
}

Turret::~Turret() {}
