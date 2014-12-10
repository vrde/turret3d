#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Vector.h"

/**
 * La classe è astratta e rappresenta un generico oggetto visualizzabile
 * nello spazio, al contrario di Entity3D non è collegato con il Modello.
 * Come in Entity invece è presente il flag \p exists che indica
 * se questa entità debba essere rimossa dal gioco o meno.
 */
class Object3D {
    public:
	/**
	 * Il Costruttore richiede una posizione nello spazio.
	 *
	 * \param _x la posizione x;
	 * \param _y la posizione y;
	 * \param _z la posizione z;
	 */
	Object3D(float _x, float _y, float _z);
	
	/**
	 * Ogni sottoclasse concreta di Entity3D deve implementare il metodo
	 * per la visualizzazione, per questo il metodo è astratto.
	 */
	virtual void draw() = 0;

	/**
	 * Restituisce lo stato di esistenza dell'entità.
	 *
	 * \return lo stato.
	 */
	bool getExists();

	/**
	 * Il Distruttore.
	 */
        virtual ~Object3D();

    protected:

	/**
	 * Il puntatore al vettore posizione.
	 */
    	Vector* pPosition;

	/**
	 * Il tempo di creazione.
	 */
	float	creationTime;

	/**
	 * Rappresenta lo stato dell'entità. Se è a \p false l'entità
	 * sarà rimossa il prima possibile.
	 */
	bool	exists;
};

#endif
