#include "Vehicle.h"
#include "Terrain.h"

Vehicle::Vehicle(float _ray, float _x, float _y, float _z, Terrain* _pTerrain) :
	Entity(_ray, _x, _y, _z, 0.0f, 0.0f, 0.0f, _pTerrain) {
	pArmament = new Armament(this);
}

Vehicle::Vehicle(float _ray, float _x, float _y, float _z, float _vx, float _vy, float _vz, Terrain* _pTerrain) :
	Entity(_ray, _x, _y, _z, _vx, _vy, _vz, _pTerrain) {
	pArmament = new Armament(this);
}

void Vehicle::calc(float _dt) {
	pPosition->coords[0] += pVelocity->coords[0] * _dt;
	pPosition->coords[1] += pVelocity->coords[1] * _dt;
	pPosition->coords[2] += pVelocity->coords[2] * _dt;
	pPosition->coords[1] = pTerrain->getHeightOf(pPosition->coords[0], pPosition->coords[2]);
}

Armament* Vehicle::getArmament() {
	return pArmament;
}

Vehicle::~Vehicle() {
	delete pArmament;
}
