#ifndef ARMAMENT_H
#define ARMAMENT_H

#include <list>
#include "Bullet.h"
#include "Entity.h"

using namespace std;
/**
 * La classe rappresenta un armamento, ad esempio un cannone.
 */
class Armament {
    public:
    	/**
	 * Il costruttore necessita di un puntatore all'entità cui è collegato.
	 *
	 * \param _pEntity l'entità;
	 */
	Armament(Entity* _pEntity);
	
	/**
	 * Metodo di get per l'alzo del cannone.
	 *
	 * \return l'alzo in gradi.
	 */
	float getSight();

	/**
	 * Metodo di set per l'alzo del cannone.
	 *
	 * \param _sight l'alzo in gradi.
	 */
	void setSight(float _sight);

	/**
	 * Metodo di get per la rotazione dell'armamento.
	 *
	 * \return la rotazione in gradi.
	 */
	float getRotation();

	/**
	 * Metodo di set per la rotazione dell'armamento.
	 *
	 * \param _rotation la rotazione in gradi.
	 */
	void setRotation(float _rotation);
	
	/**
	 * Il metodo fa sparare l'armamento. Tra uno sparo e l'altro
	 * deve passare del tempo affinché il cannone venga ricaricato.
	 *
	 * \return il Bullet sparato.
	 */
	Bullet* fire();

	/**
	 * Distruttore.
	 */
	virtual ~Armament();

    protected:
    	/**
	 * Il puntatore all'entità cui il cannone è collegato.
	 */
	Entity* pEntity;

	/**
	 * L'alzo dell'armamento.
	 */
	float sight;

	/**
	 * La rotazione dell'armamento.
	 */
	float rotation;
	
	/**
	 * Mantiene il tempo dell'ultimo sparo.
	 */
	float lastFire;

	/**
	 * Inizializzato nel costruttore, indica il tempo minimo che deve
	 * passare tra uno sparo e l'altro.
	 */
	float fireDelta;
};

#endif
