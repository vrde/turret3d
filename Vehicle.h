#ifndef VEHICLE_H
#define VEHICLE_H

#include "Entity.h"
#include "Armament.h"
#include "Terrain.h"

/**
 * La classe rappresenta un veicolo che si muove sul terreno (Terrain).
 * Un veicolo � caratterizzato da un armamento (che avrei voluto aggiungere
 * ma che non ho messo causa tempo).
 */
class Vehicle : public Entity {
    public:

	/**
	 * Il costruttore richiede raggio, posizione e un puntatore al
	 * territorio.
	 *
	 * \param _ray il raggio dell'entit�;
	 * \param _x la posizione x;
	 * \param _y la posizione y;
	 * \param _z la posizione z;
	 * \param _pTerrain il terreno del modello.
	 */
	Vehicle(float _ray, float _x, float _y, float _z, Terrain* _pTerrain);

	/**
	 * Il costruttore prende in input un raggio, una posizione e un terreno.
	 *
	 * \param _ray il raggio dell'entit�;
	 * \param _x la posizione \p x;
	 * \param _y la posizione \p y;
	 * \param _z la posizione \p z;
	 * \param _vx la componente \p x della vettore velocit�;
	 * \param _vy la componente \p y della vettore velocit�;
	 * \param _vz la componente \p z della vettore velocit�;
	 * \param _pTerrain il terreno del modello.
	 */
	Vehicle(float _ray, float _x, float _y, float _z, float _vx, float _vy, float _vz, Terrain* _pTerrain);

	/**
	 * Metodo che ricalcola la nuova posizione dell'entit�.
	 *
	 * \param _dt l'intervallo di tempo trascorso dalla precedente chiamata.
	 */
	void calc(float _dt);
	
	/**
	 * Restituisce il puntatore all'armamento del veicolo.
	 *
	 * \return l'armamento.
	 */
	Armament* getArmament();

	/**
	 * Il Distruttore;
	 */
	~Vehicle();

    protected:
	/**
	 * Il puntatore all'armamento.
	 */
	Armament* pArmament;
};

#endif
