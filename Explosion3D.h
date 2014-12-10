#ifndef EXPLOSION3D_H
#define EXPLOSION3D_H

#include "Object3D.h"

/**
 * La classe simula una esplosione, rappresentata da una sfera che aumenta
 * rapidamente il raggio aumentando la sua trasparenza.
 */
class Explosion3D : public Object3D {
    public:
	/**
	 * Il costruttore prende in input il raggio e una posizione.
	 * Il vettore velocità in questo metodo è nullo.
	 *
	 * \param _ray il raggio dell'entità;
	 * \param _x la posizione x;
	 * \param _y la posizione y;
	 * \param _z la posizione z;
	 */
	Explosion3D(float _ray, float _x, float _y, float _z);

	/**
	 * Metodo per la visualizzazione.
	 */
	void draw();
	
	/**
	 * Il Distruttore.
	 */
	virtual ~Explosion3D();
    protected:
	/**
	 * Variabile inizializzata nel costruttore che rappresenta il
	 * tempo di vita dell'esplosione.
	 */
	float timeToLive;

	/**
	 * Raggio dell'esplosione, è modificato durante il tempo.
	 */
	float ray;
};

#endif
