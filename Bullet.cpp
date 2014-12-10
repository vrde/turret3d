#include "Bullet.h"

Bullet::Bullet(float _ray, float _x, float _y, float _z, Terrain* _pTerrain) :
	Entity(_ray, _x, _y, _z, 0.0f, 0.0f, 0.0f, _pTerrain) {
}

Bullet::Bullet(float _ray, float _x, float _y, float _z, float _vx, float _vy, float _vz, Terrain* _pTerrain) :
	Entity(_ray, _x, _y, _z, _vx, _vy, _vz, _pTerrain)	{
}

void Bullet::calc(float _dt) {
	pPosition->coords[0] += pVelocity->coords[0] * _dt;
	pPosition->coords[1] += pVelocity->coords[1] * _dt;
	pPosition->coords[2] += pVelocity->coords[2] * _dt;
	
	pVelocity->coords[1] -= 9.8 * _dt;
}

Bullet::~Bullet() {}
