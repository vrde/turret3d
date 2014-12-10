#ifndef TURRET_H
#define TURRET_H

#include "Vehicle.h"
#include "Terrain.h"

/**
 * Questa classe rappresenta una torretta all'interno del componente Model
 * dell'architettura MVC.
 * Eredita da Vehicle poiché è considerato un tipo speciale di veicolo.
 */

class Turret : public Vehicle {
    public:
	/**
	 * Il costruttore richiede raggio, posizione e un puntatore al
	 * territorio.
	 *
	 * \param _ray il raggio dell'entità;
	 * \param _x la posizione x;
	 * \param _y la posizione y;
	 * \param _z la posizione z;
	 * \param _pTerrain il terreno del modello.
	 */
	Turret(float _ray, float _x, float _y, float _z, Terrain* _pTerrain);

	/**
	 * Il costruttore prende in input un raggio, una posizione e un terreno.
	 *
	 * \param _ray il raggio dell'entità;
	 * \param _x la posizione \p x;
	 * \param _y la posizione \p y;
	 * \param _z la posizione \p z;
	 * \param _vx la componente \p x della vettore velocità (ignorato);
	 * \param _vy la componente \p y della vettore velocità (ignorato);
	 * \param _vz la componente \p z della vettore velocità (ignorato);
	 * \param _pTerrain il terreno del modello.
	 */
	Turret(float _ray, float _x, float _y, float _z, float _vx, float _vy, float _vz, Terrain* _pTerrain);

	/**
	 * Imposta l'alzo dell'armamento (Armament) collegato alla torretta.
	 *
	 * \param _sight l'alzo in gradi;
	 */
	void setSight(float _sight);

	/**
	 * Restituisce l'alzo dell'armamento (Armament) collegato alla torretta.
	 *
	 * \return l'alzo in gradi;
	 */
	float getSight();

	/**
	 * Imposta la rotazione dell'armamento (Armament) collegato alla torretta.
	 *
	 * \param _rotation la rotazione in gradi;
	 */
	void setRotation(float _rotation);

	/**
	 * Restituisce la rotazione dell'armamento (Armament)
	 * collegato alla torretta.
	 *
	 * \return la rotazione in gradi;
	 */
	float getRotation();

	/**
	 * Metodo che ricalcola la nuova posizione dell'entità.
	 *
	 * \param _dt l'intervallo di tempo trascorso dalla precedente chiamata.
	 */
	void calc(float _dt);

	/**
	 * Il Distruttore.
	 */
	~Turret();

    protected:
	/**
	 * L'alzo del cannone.
	 */
	float sight;

	/**
	 * La rotazione del cannone.
	 */
	float rotation;
};

#endif
