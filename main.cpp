/**
 * \mainpage IGM ~ Alberto Granzotto
 *
 * \section autore Autore
 * Alberto Granzotto - 501363/SIN
 * \section intro Introduzione
 * Il progetto è stato sviluppato utilizzando unicamente le librerie
 * OpenGL e GLUT, risulta quindi portabile senza problemi su altre piattaforme
 * (è stato compilato con successo su una macchina Windows con cygwin e su
 * Mac Os X).
 * Il progetto segue l'architettura MVC e, per ogni componente, si è
 * descritto in modo accurato come rientra in questo pattern.
 * 
 * \section risol La Risoluzione
 * \subsection mvc L'architettura MVC
 * \subsubsection mvc-m Il Modello (Model)
 * Nel modello ricadono le classi:
 *  - Armament
 *  - Bullet
 *  - Entity
 *  - Terrain
 *  - Turret
 *  - Vehicle
 * 
 * \subsubsection mvc-v La Vista (View)
 * Nella vista ci sono le classi:
 *  - Bullet3D
 *  - Entity3D
 *  - Terrain3D
 *  - Turret3D
 *  - Vehicle3D
 * 
 * \subsubsection mvc-c Il Controllore (Contoller)
 * Il controllore è la classe Controller.
 * 
 * \subsection pannelli I Pannelli
 * Per controllare alcune particolari entità quali Luci, Nebbia
 * e Display List sono state create delle classi che implementano il
 * pattern Singleton:
 *  - LightPanel;
 *  - FogPanel;
 *  - DisplayListPanel;
 *  
 *  Le prime due possono essere viste come dei \e mixer per configurare
 *  più comodamente luci e nebbia.
 *
 * \section ottim Ottimizzazioni e Caratteristiche
 * \subsection ottim-dl Display List
 * Oltre alle ottimizzazioni molto efficaci introdotte a lezione, come
 * ad esempio \p GL_CULL_FACE (che incrementa di molto la velocità di
 * rendering dell'immagine), sono state usate le <em> Display List</em>
 * nelle classi Turret3D, Vehicle3D e Terrain3D.
 *
 * \subsection ottim-text Texture
 * Oltre a questo le texture sono caricate \b una volta per classe
 * in modo da minimizzare l'utilizzo della VRAM. Per migliorare la
 * visualizzazione sono create dinamicamente anche le \e mipmap.
 * Per dare l'effetto di lucentezza della canna della torretta
 * si utilizza lo <em>sphere mapping</em> con la generazione
 * automatica delle coordinate.
 * Le texture caricate sono immagini TarGA, decodificate da una
 * funzione creata appositamente (si veda il file \p tgautils.h).
 *
 * \subsectino ottim-luci Le Luci
 * Le luci controllate sono:
 *  - la luce Ambientale (che cerca di simulare la luce solare);
 *  - una luce posta sopra la torretta;
 *  - la luce che segue il proiettile.
 *
 * \subsection ottim-text Blending
 * Per le esplosioni (Explosion3D) si utilizza il blending, in questo
 * modo la sfera sembra dissolversi nell'aria. Purtroppo utilizzare
 * il blending comporta a qualche errore grafico che per questo
 * progetto non è stato risolto.
 *
 * \subsection ottim-territorio Il Terreno
 * Il terreno è leggermente montuoso e le entità che si muovono
 * su di esso seguono i dislivelli. Oltre a questo la classe
 * Terrain3D calcola anche le normali di riflessione della luce
 * \b non per faccia ma per \b vertice.
 * 
 * \subsection ottim-skybox Lo Skybox
 * Per aggiungere del realismo è stato creato uno \e skybox con l'immagine
 * di montagne e del cielo. Purtroppo non è stato possibile togliere le linee
 * di congiunzione tra le varie facce della \e scatola.
 *
 * \subsection ottim-nebbia La Nebbia
 * Avanzando nel tempo il controllore diminuisce la luce ambientale
 * e fa sopraggiungere la notte. Con la notte arriva anche la nebbia.
 *
 * \section gioco Il Gioco
 * Alla torretta, posta al centro, si avvicinano pericolosamente dei veicoli
 * nemici. La torretta deve sparare per cercare di eliminare la minaccia
 * nemica, cosa impossibile però.
 * Con l'avanzare del tempo sopraggiunge la notte.
 *
 * \subsection controlli I Controlli
 * Movimento:
 *  - la rotazione e l'alzo della torretta sono regolati dal mouse;
 *  - il tasto \b w avvicina l'osservatore alla torretta;
 *  - il tasto \b s allontana l'osservatore dalla torretta;
 * 
 * Fuoco:
 *  - il fuoco è controllato dal tasto sinistro del mouse
 *  (attenzione, il tempo di ricarica tra un colpo e l'altro
 *  è di 1 secondo)
 * 
 * Altri controlli:
 *  - \b ESC per uscire dall'applicazione;
 *  - \b m per scollegare o collegare il mouse alla finestra.
 */


#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Controller.h"

using namespace std;

#define ESCAPE 27

int window;
Controller* pController;

void init_GL(int width, int height) {
	glClearColor(5.0f, 5.0f, 5.0f, 1.0f);
	glClearDepth(1.0);
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LESS);	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
}

float angle = 45.0f;
float near = 0.1f;
float far = 600.0f;

void resize_GL_scene(int width, int height) {
	if (height==0) height=1;
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle, (GLfloat)width/(GLfloat)height,near,far);
	glMatrixMode(GL_MODELVIEW);

	pController->setWindowWidth(width);
	pController->setWindowHeight(height);
}

void processPassiveMotion(int x, int y) {
	pController->mouseEvent(x, y);
}

void processMouse(int button, int state, int x, int y) {
	pController->processMouse(button, state, x, y);
}

void draw_GL_scene() {
	pController->idleFunction();
}

void keyPressed(unsigned char key, int x, int y) {
    usleep(100);

    if (key == ESCAPE) { 
  	delete pController;
	glutDestroyWindow(window); 
	
	exit(0);                   
    }
    pController->keyPressed(key, x, y);
}

int main(int argc, char **argv) {  
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(20, 20);
	window = glutCreateWindow("Progetto Informatica Grafica - Alberto Granzotto");

	srand ( time(NULL) );
	pController = new Controller(640, 480);

	glutDisplayFunc(&draw_GL_scene);
	glutIdleFunc(&draw_GL_scene);
	glutReshapeFunc(&resize_GL_scene);
  
	glutPassiveMotionFunc(processPassiveMotion); 
	glutMouseFunc(processMouse);
	glutKeyboardFunc(&keyPressed);


	glutSetCursor(GLUT_CURSOR_NONE);

	init_GL(640, 480);
	glutMainLoop();  

return 1;
}

