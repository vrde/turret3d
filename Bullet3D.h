#ifndef BULLET3D_H
#define BULLET3D_H

#include "Entity3D.h"
#include "Bullet.h"
/**
 * Nell'architettura MVC questa classe si posizione nella V, cioè
 * nella vista.
 */
class Bullet3D : public Entity3D {
    public:
	/**
	 * Il costruttore necessita di un puntatore all'oggetto (nel Modello)
	 * che deve rappresentare, in modo da poter prelevare i dati che
	 * servono.
	 *
	 * \param _pBullet il puntatore all'entità da visualizzare.
	 */
	Bullet3D(Bullet* _pBullet);

	/**
	 * Il metodo da richiamare quando si vuole disegnare una
	 * istanza di questa classe.
	 */
	void draw();

	/**
	 * Il Distruttore.
	 */
	~Bullet3D();
};

#endif
