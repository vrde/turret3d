#ifndef TERRAIN3D_H
#define TERRAIN3D_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Terrain.h"
#include "Vector.h"
#include "DisplayListPanel.h"
#include "FogPanel.h"
#include "LightPanel.h"

/**
 * Rappresentazione, nella Vista, del Modello Terrain.
 * Oltre a visualizzare il terreno specificato dal puntatore
 * \p _pTerrain, la classe calcola la matrice di normali di riflessione
 * della luce, inoltre aggiunge uno \a skybox per rendere più gradevole
 * il paesaggio.
 */
class Terrain3D {
    public:
	/**
	 * Il costruttore richiede un puntatore ad un terreno
	 * generato precedentemente.
	 *
	 * \param _pTerrain il puntatore al terreno.
	 */
	Terrain3D(Terrain* _pTerrain);

	/**
	 * Il metodo disegna il terreno.
	 */
	void draw();

	/**
	 * Imposta l'ambiente alla notte.
	 *
	 * \param _p un numero tra 0 e 1 che rappresenta la percentuale
	 * di notte.
	 */
	void night(float _p);

	/**
	 * Distruttore.
	 */
	~Terrain3D();

    protected:
	/**
	 * Metodo per caricare le texture per il terreno e per
	 * lo skybox.
	 */
	static void loadTex();

	/**
	 * Crea la display list contenente il terreno e lo skybox.
	 */
	void createDisplayList();

	/**
	 * Puntatore al modello del terreno.
	 */
	Terrain* pTerrain;

	/**
	 * Matrice delle normali calcolata nel costruttore.
	 */
	Vector normals[MAX_X][MAX_Z];

	/**
	 * Fattore di moltiplicazione per le x.
	 */
	float xMul;

	/**
	 * Fattore di moltiplicazione per le z.
	 */
	float zMul;

	/**
	 * Indica se è giorno o no.
	 */
	bool daylight;

	/**
	 * Contenitore dell'indice di texture per il terreno.
	 */
	static GLuint texture[1];

	/**
	 * Contenitore dell'indice di texture per lo skybox.
	 */
	static GLuint texSkybox[6];

	/**
	 * Contenitore dell'indice della display list.
	 */
	static GLuint displayList[2];

	/**
	 * Aiuto mnemonico per gestire le texture dello
	 * skybox.
	 */
	enum sky { BACK = 0, LEFT, FRONT, RIGHT, UP, BOTTOM };

	/**
	 * Aiuto mnemonico per gestire le display list.
	 */
	enum list { TERRAIN = 0, SKYBOX };
};

#endif
