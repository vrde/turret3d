#ifndef TGAUTILS_H
#define TGAUTILS_H

/**
 * Autore: Alberto Granzotto - agranzot@studenti.math.unipd.it
 * Licenza: public domain
 * Versione: 0.2
 * Ultima modifica: 2 gennaio 2007
 */
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/**
 * Carica nello heap l'immagine TarGA specificata da \p filename.
 *
 * \param filename il nome del file TGA;
 * \param width un alias dove è caricata la larghezza dell'immagine;
 * \param height un alias dove è caricata la altezza dell'immagine.
 */
char* import_tga(char* filename, int& width, int& height);

/**
 * Carica una immagine TarGA nella macchina di OpenGL e restituisce il
 * \p GLuint che la rappresenta nella memoria.
 *
 * \param name il nome del file TGA che contiene la texture;
 * \param mipmap se \p true calcola anche le mipmap.
 */
GLuint load_tex(char* name, bool mipmap = false);

#endif
