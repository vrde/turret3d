#include "Terrain.h"
#include "Vector.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

Terrain::Terrain(float _width, float _length) : width(_width), length(_length) {
	srand ( time(NULL) );
	// azzero la matrice
	for(int i = 0; i < MAX_X; i++)
		for(int j = 0; j < MAX_Z; j++)
			values[i][j] = 0;
	float disp = 1.0;
	for(int k = 1; k < 1000; k++) {
		//disp = (-k+700)/300;
		// creo una retta casuale
		float v = rand();
		float a = sin(v);
		float b = cos(v);
		float d = sqrt(width*width + length*length);
		float c = ((float)rand() / RAND_MAX) * d - d/2.0;
		for(float i = 0; i < MAX_X; i++)
			for(float j = 0; j < MAX_Z; j++)
				if(a*i + b*j - c > 0)
					values[(int)i][(int)j] += disp;
				else
					values[(int)i][(int)j] -= disp;
	}
}

float Terrain::getWidth() {
	return width;
}

float Terrain::getLength() {
	return length;
}

int Terrain::getCols() {
	return MAX_X;
}

int Terrain::getRows() {
	return MAX_Z;
}

float Terrain::getHeightOf(float _x, float _z) {
	float cc=0, rc=0, hc=0, c2=0, r2=0, h2=0, c3=0, r3=0, h3=0, temp = 0;

	_x += width/2;
	_z += length/2;
	float c = MAX_X * _x / width;
	float r = MAX_Z * _z / length;
	float xMul = width / MAX_X;
	float zMul = length / MAX_Z;
	cc = round(c);
	rc = round(r);
	hc = values[(int)cc][(int)rc];
	if(cc < c) {
		if(rc < r)		{c2 =  1; r2 =  0; c3 =  0; r3 =  1;}
		else if((c-cc)>(rc-r))	{c2 =  1; r2 = -1; c3 =  1; r3 =  0;}
		else			{c2 =  0; r2 = -1; c3 =  1; r3 = -1;}
	}
	else if(r < rc)			{c2 = -1; r2 =  0; c3 =  0; r3 = -1;}
	else if((cc-c)>(r-rc))		{c2 = -1; r2 =  1; c3 = -1; r3 =  0;}
	else				{c2 =  0; r2 =  1; c3 = -1; r3 =  1;}

	if( (cc < 1) || (cc >= MAX_X-1) || (rc < 1) || (rc >= MAX_Z-1) )
		return 0;

	h2 = values[(int)(cc+c2)][(int)(rc+r2)];
	h3 = values[(int)(cc+c3)][(int)(rc+r3)];
	Vector v1(c2 * xMul, h2 - hc, r2 * zMul);
	Vector v2(c3 * xMul, h3 - hc, r3 * zMul);

	Vector normal = Vector::crossProd(v2, v1);
	normal.normalize();
	//utilizzo equazione del piano per trovare y:
	temp =normal.coords[0] * (cc*xMul) +\
		normal.coords[1] * hc +\
		normal.coords[2] * (rc*zMul) -\
		normal.coords[0] * _x -\
		normal.coords[2] * _z;
	temp /= normal.coords[1];
	
	return temp;
}

Terrain::~Terrain() {}
