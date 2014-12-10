#ifndef VECTOR_H
#define VECTOR_H
/**
 * Definisce un vettore a tre dimensioni.
 */
class Vector {
    public:
	/**
	 * Le tre coordinate sono pubbliche per comodità.
	 */
    	float coords[3];

	/**
	 * Costruttore che inizializza un vettore nullo [0, 0, 0].
	 */
	Vector();

	/**
	 * Costruttore che inizializza un vettore.
	 *
	 * \param _x il valore della coordinata \p x;
	 * \param _y il valore della coordinata \p y;
	 * \param _z il valore della coordinata \p z;
	 */
	Vector(float _x, float _y, float _z);

	/**
	 * Costruttore di copia.
	 */
	Vector(const Vector& v);

	/**
	 * Calcola la distanza tra due vettori.
	 *
	 * \param _pv un puntatore ad un altro vettore.
	 * \return la distanza.
	 */
	float distanceTo(const Vector* _pv) const;

	/**
	 * Calcola il prodotto tra due vettori.
	 *
	 * \param v1 il primo vettore;
	 * \param v2 il secondo vettore;
	 * \return il vettore risultante da v1 x v2.
	 */
	static Vector crossProd(const Vector& v1, const Vector& v2);

	/**
	 * Normalizza il vettore.
	 */
	void normalize();

	/**
	 * Il distruttore.
	 */
	~Vector();
};

#endif
