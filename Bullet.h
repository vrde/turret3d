#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
#include "Terrain.h"

/**
 * Questa classe appartiene al Modello dell'architettura MVC.
 * Rappresenta un proiettile.
 */
class Bullet : public Entity {
    public:
	/**
	 * Il costruttore prende in input una posizione e un terreno.
	 * Il vettore velocità in questo metodo è nullo.
	 *
	 * \param _ray il raggio dell'entità;
	 * \param _x la posizione x;
	 * \param _y la posizione y;
	 * \param _z la posizione z;
	 * \param _pTerrain il terreno del modello.
	 */
	Bullet(float _ray, float _x, float _y, float _z, Terrain* _pTerrain);

	/**
	 * Il costruttore prende in input una posizione e un terreno.
	 *
	 * \param _ray il raggio dell'entità;
	 * \param _x la posizione \p x;
	 * \param _y la posizione \p y;
	 * \param _z la posizione \p z;
	 * \param _vx la componente \p x della vettore velocità;
	 * \param _vy la componente \p y della vettore velocità;
	 * \param _vz la componente \p z della vettore velocità;
	 * \param _pTerrain il terreno del modello.
	 */
	Bullet(float _ray, float _x, float _y, float _z, float _vx, float _vy, float _vz, Terrain* _pTerrain);

	/**
	 * Metodo che ricalcola la nuova posizione dell'entità.
	 *
	 * \param _dt l'intervallo di tempo trascorso dalla precedente chiamata.
	 */
	void calc(float _dt);

	/**
	 * Distruttore.
	 */
	~Bullet();
};

#endif
