#ifndef VEHICLE3D_H
#define VEHICLE3D_H

#include "Entity3D.h"
#include "Vehicle.h"
#include "DisplayListPanel.h"

/**
 * Questa classe rappresenta nella Vista ciò che nel Modello è un veicolo
 * (Vehicle).
 */
class Vehicle3D : public Entity3D {
    public:
	/**
	 * Il costruttore necessita di un puntatore al veicolo
	 * del modello.
	 *
	 * \param _pVehicle il puntatore al veicolo.
	 */
	Vehicle3D(Vehicle* _pVehicle);

	/**
	 * Metodo per disegnare la torretta.
	 */
	void draw();

	/**
	 * Il distruttore.
	 */
	~Vehicle3D();

    protected:
	/**
	 * Richiamato dal costruttore, carica le texture necessarie
	 * alla torretta.
	 */
	static void loadTex();

	/**
	 * Richiamato dal costruttore, crea le display list necessarie
	 * alla torretta.
	 */
	void createDisplayList();

	/**
	 * Contiene gli indici delle texture.
	 */
	static GLuint texture[2];

	/**
	 * Contiene gli indici delle display list
	 */
	static GLuint displayList[2];
	
	/**
	 * Enumerazione delle parti della torretta utilizzata
	 * per le display list.
	 */
	enum display { CATERPILLAR = 0, BODY };
};

#endif
