#ifndef TURRET3D_H
#define TURRET3D_H

#include "Entity3D.h"
#include "Turret.h"

/**
 * Classe che rappresenta nella Vista il Modello di torretta (Turret).
 */
class Turret3D : public Entity3D {
    public:
	/**
	 * Il costruttore richiede il puntatore alla torretta
	 * del Modello.
	 *
	 * \param _pTurret il puntatore alla torretta.
	 */
	Turret3D(Turret* _pTurret);

	/**
	 * Metodo per disegnare la torretta.
	 */
	void draw();

	/**
	 * Il distruttore.
	 */
	~Turret3D();

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
	static GLuint texture[3];

	/**
	 * Contiene gli indici delle display list
	 */
	static GLuint displayList[2];
	
	/**
	 * Enumerazione delle parti della torretta utilizzata
	 * per le display list.
	 */
	enum display { BASE = 0, CANNON };
};

#endif
