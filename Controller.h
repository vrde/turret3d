#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <list>

#include "Entity.h"
#include "Terrain.h"
#include "Turret.h"
#include "Bullet.h"

#include "LightPanel.h"
#include "FogPanel.h"
#include "Entity3D.h"
#include "Terrain3D.h"
#include "Turret3D.h"
#include "Vehicle3D.h"
#include "Bullet3D.h"
#include "Object3D.h"

/**
 * Questa classe incapsula tutte le operazioni che deve effettuare la "C"
 * (ovvero il Controllore) di MVC.
 * È il ponte di connessione tra gli oggetti della Vista (le classi con il
 * suffisso \p 3D) e gli oggetti nel Modello e gestisce gli eventi
 * generati dall'utente.
 * Ad esempio, quando l'utente preme il pulsante di fuoco, l'evento gestito
 * dal Controller si occupa di richiedere all'armamento (Armament) della
 * torretta (Turret) di creare un nuovo proiettile (Bullet); una volta
 * ottenuto il proiettile il Controller si occupa di creare un nuovo
 * elemento nella vista che rappresenti il proiettile appena creato.
 */
class Controller {
    public:
	/**
	 * Il costruttore.
	 */
	Controller(int width, int height);

	/**
	 * Metodo che gestisce gli eventi passivi del mouse, vale a dire
	 * i movimenti del mouse senza alcun tasto premuto.
	 * Si occupa di muovere la vista in modo da assecondare i movimenti
	 * del mouse.
	 *
	 * \param x la nuova \p x del mouse;
	 * \param y la nuova \p y del mouse;
	 */
	void mouseEvent(int x, int y);

	/**
	 * Metodo che gestisce gli eventi attivi del mouse, cioè quelli
	 * scatenati dai pulsanti del mouse.
	 * Si occupa di gestire principalmente il fuoco dalla torretta.
	 *
	 * \param button il bottone premuto;
	 * \param state lo stato, se ci sono quindi modificatori attivi;
	 * \param x la \p x del mouse;
	 * \param y la \p y del mouse;
	 *
	 * \sa Turret
	 */
	void processMouse(int button, int state, int x, int y);

	/**
	 * Metodo che gestisce gli eventi della tastiera.
	 *
	 * \param key il tasto premuto;
	 * \param x la \p x del mouse;
	 * \param y la \p y del mouse;
	 */
	void keyPressed(unsigned char key, int x, int y);

	/**
	 * Metodo che ricalcola le nuove posizioni degli elementi
	 * (Entity) del modello, controlla se ci sono collisioni e, in
	 * caso affermativo, elimina gli oggetti che collidono. Richiama
	 * inoltre il metodo draw per ogni elemento nella vista.
	 */
	void idleFunction();

	/**
	 * Imposta la larghezza della finestra dove agisce il controller.
	 *
	 * \param width la larghezza.
	 */
	void setWindowWidth(int width);

	/**
	 * Imposta l'altezza della finestra dove agisce il controller.
	 *
	 * \param height l'altezza.
	 */
	void setWindowHeight(int height);

	/**
	 * Distuttore, elimina tutte le liste allocate e tutti gli oggetti
	 * da esse dipendenti.
	 */
	~Controller();

    protected:
    	/**
	 * Metodo che si occupa della creazione di un nuovo veicolo.
	 * Lo crea scegliendo casualmente la posizione di partenza
	 * e il vettore velocità.
	 *
	 * \sa Vehicle
	 */
    	void createVehicle();

	/**
	 * Metodo per la visualizzazione di informazioni,
	 * utilizzato principalmente per il debug dell'applicazione.
	 */
	void printInfo();

	/**
	 * Metodo per la visualizzazione di una stringa.
	 * 
	 * \param str un puntatore ad una sequenza di char;
	 * \param x la posizione \p x della scritta;
	 * \param y la posizione \p y della scritta;
	 */
	void printString(char *str, float x, float y);

	/**
	 * La posizione \p x della telecamera.
	 */
	float povX; //0
	/**
	 * La posizione \p y della telecamera.
	 */
	float povY; //10

	/**
	 * La posizione \p z della telecamera.
	 */
	float povZ; //30

	/**
	 * La rotazione della telecamera.
	 */
	float povRotX; //10

	/**
	 * L'ultima posizione \p x del mouse.
	 */
	int mouseLastX;
	
	/**
	 * L'ultima posizione \p y del mouse.
	 */
	int mouseLastY;

	/**
	 * La rotazione della torretta rispetto all'asse \p y.
	 */
	float turretRotation;

	/**
	 * La rotazione della torretta rispetto all'asse \p x.
	 */
	float turretSight;

	/**
	 * L'ultimo tempo registrato.
	 */
	float lastTime;

	/**
	 * L'ultimo intervallo di tempo registrato.
	 */
	float dt;

	/**
	 * Registra il valore del tempo della ultima creazione di un
	 * veicolo.
	 */
	float lastCreation;

	/**
	 * Rappresenta l'intervallo di tempo tra una creazione e l'altra
	 * (il valore non è costante, è decrementato nel corso della partita
	 * per aumentare la difficoltà del gioco.
	 */
	float creationDelay;

	/**
	 * Lista che contiene i proiettili nel modello.
	 */
	list<Bullet*>*		pBullets;

	/**
	 * Lista che contiene le entità nel modello.
	 */
	list<Entity*>*		pEntities;

	/**
	 * Puntatore al terreno utilizzato.
	 */
	Terrain*		pTerrain;

	/**
	 * Puntatore alla torretta controllata dal giocatore.
	 */
	Turret*			pTurret;

	/**
	 * Lista contenente le entità nella vista.
	 */
	list<Entity3D*>*	pEntities3D;

	/**
	 * Puntatore alla vista del terreno.
	 */
	Terrain3D*		pTerrain3D;

	/**
	 * Puntatore alla vista della torretta.
	 */
	Turret3D*		pTurret3D;

	/**
	 * Lista contenente le entità della vista non collegate
	 * con il modello (ad esempio le esplosioni).
	 *
	 * \sa Explosion
	 */
	list<Object3D*>*	pObjects3D;

	/**
	 * Puntatore al pannello delle luci.
	 */
	LightPanel*		lightPanel;

	/**
	 * Puntatore al pannello della nebbia.
	 */
	FogPanel*		fogPanel;
	
	/**
	 * Variabile di controllo per la simulazione
	 * dell'esplosione di un nemico.
	 */
	float			shakeDelay;
	
	/**
	 * Enumerazione degli stati, usato per comodità.
	 */
	enum state { PLAYING, LOST };

	/**
	 * Mantiene lo stato corrente.
	 */
	state			currentState;

	/**
	 * \p true se il mouse è catturato nella finestra, false altrimenti
	 */
	bool			captureMouse;

	/**
	 * Larghezza della finestra.
	 */
	int			windowWidth;

	/**
	 * Altezza della finestra.
	 */
	int			windowHeight;
};

#endif
