#ifndef ENTITY_H
#define ENTITY_H

#include "Vector.h"
#include "Terrain.h"

/**
 * La classe rappresenta una generica entità nella M (Modello) dell'architettura
 * MVC.
 * Ha una posizione nello spazio, un vettore velocità che può essere nullo
 * (l'entià è immobile in tal caso), un raggio che serve per calcolare
 * le collisioni e il terreno dove essa si muove.
 *
 * Altra cosa importante, l'entità ha un flag chiamato \p exists che indica
 * se questa debba essere rimossa dal modello o meno.
 */
class Entity {
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
	Entity(float _ray, float _x, float _y, float _z, Terrain* _pTerrain);

	/**
	 * Il costruttore prende in input un raggio, una posizione e un terreno.
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
	Entity(float _ray, float _x, float _y, float _z, float _vx, float _vy, float _vz, Terrain* _pTerrain);

	/**
	 * Restituisce la distanza da un'altra entità.
	 *
	 * \param _pEntity l'altra entità.
	 *
	 * \return la distanza.
	 */
	float distanceTo(Entity* _pEntity);

	/**
	 * Controlla se c'è una collisione con un'altra entità.
	 *
	 * \param _pEntity l'altra entità.
	 * \return \p true se le due entità collidono, \p false altrimenti.
	 */
	bool isCollidingWith(Entity* _pEntity);

	/**
	 * Metodo che ricalcola la nuova posizione dell'entità.
	 *
	 * \param _dt l'intervallo di tempo trascorso dalla precedente chiamata.
	 */
	virtual void calc(float _dt) = 0;

	/**
	 * Restituisce il raggio dell'entità.
	 *
	 * \return il raggio.
	 */
	float getRay();

	/**
	 * Imposta il raggio dell'entità.
	 *
	 * \param _ray il nuovo raggio.
	 */
	void setRay(float _ray);

	/**
	 * Restituisce la posizione \p x dell'entità.
	 *
	 * \return la posizione \p x;
	 */
	float getX();

	/**
	 * Restituisce la posizione \p y dell'entità.
	 *
	 * \return la posizione \p y;
	 */
	float getY();

	/**
	 * Restituisce la posizione \p z dell'entità.
	 *
	 * \return la posizione \p z;
	 */
	float getZ();

	/**
	 * Restituisce lo stato di esistenza dell'entità.
	 *
	 * \return lo stato.
	 */
	bool getExists();

	/**
	 * Imposta lo stato di esistenza dell'entità.
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
	 * Restituisce il puntatore al vettore velocità
	 * (modificabile se necessario).
	 *
	 * \return il vettore velocità.
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
	 * Rappresenta lo stato dell'entità. Se è a \p false l'entità
	 * sarà rimossa il prima possibile.
	 */
	bool		exists;

	/**
	 * Il raggio dell'entità.
	 */
	float		ray;

	/**
	 * Il puntatore al terreno.
	 */
	Terrain*	pTerrain;

	/**
	 * Il puntatore al vettore velocità.
	 */
	Vector*		pVelocity;

	/**
	 * Il puntatore al vettore posizione.
	 */
	Vector*		pPosition;
};

#endif
