#include <math.h>
#include "Vector.h"

Vector::Vector() {
	coords[0] = 0;
	coords[1] = 0;
	coords[2] = 0;
}

Vector::Vector(float _x, float _y, float _z) {
	coords[0] = _x;
	coords[1] = _y;
	coords[2] = _z;
}

Vector::Vector(const Vector& v) {
	coords[0] = v.coords[0];
	coords[1] = v.coords[1];
	coords[2] = v.coords[2];
}

float Vector::distanceTo(const Vector* _pv) const {
	return sqrt(pow(coords[0] - _pv->coords[0], 2) +
		pow(coords[1] - _pv->coords[1], 2) +
		pow(coords[2] - _pv->coords[2], 2));
}

Vector Vector::crossProd(const Vector& v1, const Vector& v2) {
	return Vector(
		v1.coords[1] * v2.coords[2] - v1.coords[2] * v2.coords[1],
		v1.coords[2] * v2.coords[0] - v1.coords[0] * v2.coords[2],
		v1.coords[0] * v2.coords[1] - v1.coords[1] * v2.coords[0]);
	
}

void Vector::normalize() {
	float length = sqrt(coords[0]*coords[0] + coords[1]*coords[1] + coords[2]*coords[2]);
	coords[0] /= length;
	coords[1] /= length;
	coords[2] /= length;
}

Vector::~Vector() {}
