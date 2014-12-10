#ifndef TERRAIN_H
#define TERRAIN_H
#include "Vector.h"

#define MAX_X 20
#define MAX_Z 20
/**
 * La classe appartiene alla M dell'acronimo MVC.
 * Tutte le entità (Entity) sono in relazione con il territorio, i carriarmati
 * (Vehicle) si muovono su di esso e i proiettili (Bullet) ci si schiantano.
 * La torretta (Turret) inoltre è posta sopra e al centro di esso.
 *
 * Il terreno è generato casualmente cercando di simulare un territorio
 * leggermente montuoso, è stato seguito l'algoritmo \a Fault:
 * http://www.lighthouse3d.com/opengl/terrain/index.php3?fault
 */
class Terrain {
    public:
	/**
	 * Il costruttore richiede la larghezza e la lunghezza del terreno.
	 *
	 * \param _width la larghezza;
	 * \param _length la lunghezza.
	 */
	Terrain(float _width, float _length);

	/**
	 * Restitisce l'altezza di un punto di coordinate \p x e \p z
	 * del territorio.
	 * Il metodo funziona in questo modo:
	 *  - calcola le coordinate dei tre vertici che costituiscono il
	 *  triangolo la cui proiezione sul piano \p xz include \p x e \p z;
	 *  - calcola, grazie a questi tre punti, la normale del piano che li
	 *  include, la normale ha forma:
	 *  \f$n = [a, b, c]^T\f$
	 *  - dalla normale ricava l'equazione del piano;
	 *  - dall'equazione calcola la \p y utilizzando la formula:
	 *  \f$y=\frac{ax_0 + by_0 + cz_0 - ax -cz}{b}\f$
	 *
	 * \param _x la posizione \p x;
	 * \param _z la posizione \p z.
	 * \return l'altezza del territorio in quel punto.
	 */
	float getHeightOf(float _x, float _z);

	/**
	 * Restituisce la larghezza del territorio.
	 *
	 * \return la larghezza.
	 */
	float getWidth();

	/**
	 * Restituisce l'altezza del territorio.
	 *
	 * \return l'altezza.
	 */
	float getLength();

	/**
	 * Restituisce il numero di colonne che compongono la matrice
	 * del territorio.
	 *
	 * \return il numero di colonne;
	 */
	int getRows();

	/**
	 * Restituisce il numero di righe che compongono la matrice
	 * del territorio.
	 *
	 * \return il numero di righe;
	 */
	int getCols();

	/**
	 * Il Distruttore.
	 */
	virtual ~Terrain();

	/**
	 * La matrice delle altezze (è pubblica per comodità).
	 */
	float values[MAX_X][MAX_Z];

	/**
	 * La larghezza.
	 */
	float width;

	/**
	 * La lunghezza.
	 */
	float length;
};

#endif
