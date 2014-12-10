#ifndef ENTITY_H
#define ENTITY_H

#include "Vector.h"
#include "Terrain.h"

/**
 * La classe rappresenta una generica entit� nella M (Modello) dell'architettura
 * MVC.
 * Ha una posizione nello spazio, un vettore velocit� che pu� essere nullo
 * (l'enti� � immobile in tal caso), un raggio che serve per calcolare
 * le collisioni e il terreno dove essa si muove.
 *
 * Altra cosa importante, l'entit� ha un flag chiamato \p exists che indica
 * se questa debba essere rimossa dal modello o meno.
 */
class Entity {
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
	Entity(float _ray, float _x, float _y, float _z, Terrain* _pTerrain);

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
	Entity(float _ray, float _x, float _y, float _z, float _vx, float _vy, float _vz, Terrain* _pTerrain);

	/**
	 * Restituisce la distanza da un'altra entit�.
	 *
	 * \param _pEntity l'altra entit�.
	 *
	 * \return la distanza.
	 */
	float distanceTo(Entity* _pEntity);

	/**
	 * Controlla se c'� una collisione con un'altra entit�.
	 *
	 * \param _pEntity l'altra entit�.
	 * \return \p true se le due entit� collidono, \p false altrimenti.
	 */
	bool isCollidingWith(Entity* _pEntity);

	/**
	 * Metodo che ricalcola la nuova posizione dell'entit�.
	 *
	 * \param _dt l'intervallo di tempo trascorso dalla precedente chiamata.
	 */
	virtual void calc(float _dt) = 0;

	/**
	 * Restituisce il raggio dell'entit�.
	 *
	 * \return il raggio.
	 */
	float getRay();

	/**
	 * Imposta il raggio dell'entit�.
	 *
	 * \param _ray il nuovo raggio.
	 */
	void setRay(float _ray);

	/**
	 * Restituisce la posizione \p x dell'entit�.
	 *
	 * \return la posizione \p x;
	 */
	float getX();

	/**
	 * Restituisce la posizione \p y dell'entit�.
	 *
	 * \return la posizione \p y;
	 */
	float getY();

	/**
	 * Restituisce la posizione \p z dell'entit�.
	 *
	 * \return la posizione \p z;
	 */
	float getZ();

	/**
	 * Restituisce lo stato di esistenza dell'entit�.
	 *
	 * \return lo stato.
	 */
	bool getExists();

	/**
	 * Imposta lo stato di esistenza dell'entit�.
	 *
	 * \param _value lo stato.
	 */
	void setExists(bool _value);

	/**
	 * Restituisce il puntatore al vettore posizione
	 * (modificabile se necessario).
	 *
	 * \return il vettore posizione.
	 */
	Vector* getPosition();

	/**
	 * Restituisce il puntatore al vettore velocit�
	 * (modificabile se necessario).
	 *
	 * \return il vettore velocit�.
	 */
	Vector* getVelocity();

	/**
	 * Restituisce il puntatore al terreno.
	 *
	 * \return il terreno.
	 */
	Terrain* getTerrain();

	/**
	 * Il Distruttore.
	 */
	virtual ~Entity();

    protected:
	/**
	 * Rappresenta lo stato dell'entit�. Se � a \p false l'entit�
	 * sar� rimossa il prima possibile.
	 */
	bool		exists;

	/**
	 * Il raggio dell'entit�.
	 */
	float		ray;

	/**
	 * Il puntatore al terreno.
	 */
	Terrain*	pTerrain;

	/**
	 * Il puntatore al vettore velocit�.
	 */
	Vector*		pVelocity;

	/**
	 * Il puntatore al vettore posizione.
	 */
	Vector*		pPosition;
};

#endif
