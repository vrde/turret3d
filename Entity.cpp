#include "Entity.h"

Entity::Entity(float _ray, float _x, float _y, float _z, Terrain* _pTerrain) : ray(_ray), pTerrain(_pTerrain) {
	pPosition = new Vector(_x, _y, _z);
	pVelocity = new Vector(0.0f, 0.0f, 0.0f);
	pTerrain = 0;
	exists = true;
}

Entity::Entity(float _ray, float _x, float _y, float _z, float _xv, float _yv, float _zv, Terrain* _pTerrain) : ray(_ray), pTerrain(_pTerrain) {
	pPosition = new Vector(_x, _y, _z);
	pVelocity = new Vector(_xv, _yv, _zv);
	exists = true;
}

float Entity::distanceTo(Entity* _pEntity) {
	return pPosition->distanceTo(_pEntity->getPosition());
}

bool Entity::isCollidingWith(Entity* _pEntity) {
	return distanceTo(_pEntity) < ray + _pEntity->getRay();
}

float Entity::getX() {
	return pPosition->coords[0];
}

float Entity::getY() {
	return pPosition->coords[1];
}

float Entity::getZ() {
	return pPosition->coords[2];
}

float Entity::getRay() {
	return ray;
}

void Entity::setRay(float _ray) {
	ray = _ray;
}

bool Entity::getExists() {
	return exists;
}

void Entity::setExists(bool _exists) {
	exists = _exists;
}

Vector* Entity::getPosition() {
	return pPosition;
}

Vector* Entity::getVelocity() {
	return pVelocity;
}

Terrain* Entity::getTerrain() {
	return pTerrain;
}

Entity::~Entity() {
	delete pPosition;
	delete pVelocity;
}
