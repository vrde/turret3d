#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Entity.h"
/**
 * La classe astratta \p Entity3D si colloca, nell'architettura MVC, nella Vista.
 * Rappresenta una generica entit� della vista cui � collegata una istanza del
 * modello.
 *
 * \sa Entity
 */
class Entity3D {
    public:
	/**
	 * Il costruttore ha bisogno di un puntatore ad una istanza del modello
	 * da cui prendere i dati necessari per visualizzare l'elemento della
	 * vista.
	 *
	 * \param _pEntity un puntatore ad un oggetto del Modello.
	 */
	Entity3D(Entity* _pEntity);
	
	/**
	 * Ogni sottoclasse concreta di Entity3D deve implementare il metodo
	 * per la visualizzazione, per questo il metodo � astratto.
	 */
	virtual void draw() = 0;

	/**
	 * Metodo che permette di prelevare l'entit� del modello a cui �
	 * collegata l'istanza della vista.
	 */
	Entity* getEntity();

	/**
	 * Distruttore
	 */
	virtual ~Entity3D();

    protected:
	/**
	 * Il puntatore all'entit� nel modello.
	 */
	Entity* pEntity; 
};

#endif
