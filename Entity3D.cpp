#include "Entity3D.h"

Entity3D::Entity3D(Entity* _pEntity) : pEntity(_pEntity) {}

Entity* Entity3D::getEntity() {
	return pEntity;
}

Entity3D::~Entity3D() {}
