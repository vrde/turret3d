#ifndef FOG_PANEL_H
#define FOG_PANEL_H

/**
 * Questa classe pu� essere vista come un vero e proprio pannello per
 * configurare la nebbia del gioco.
 * La classe realizza il pattern Singleton.
 */
class FogPanel {
    public:
	/**
	 * Metodo per ottenere l'istanza del singleton.
	 *
	 * \return l'istanza.
	 */
	static FogPanel* getInstance();

	/**
	 * Abilita la nebbia.
	 */
	void enable();

	/**
	 * Disabilita la nebbia.
	 */
	void disable();
	
	/**
	 * Imposta il colore della nebbia.
	 *
	 * \param _r la quantit� di rosso;
	 * \param _g la quantit� di verde;
	 * \param _b la quantit� di blu;
	 * \param _a il componente alfa.
	 */
	void setColor(float _r, float _g, float _b, float _a);

	/**
	 * La densit� della nebbia (solo per nebbia EXP o EXP2).
	 * La nebbia implementata da questo pannello � unicamente
	 * lineare.
	 *
	 * \param _density la densit� della nebbia.
	 */
	void setDensity(float _density);

	/**
	 * Imposta la distanza minima della nebbia.
	 */
	void setStart(float _start);

	/**
	 * Imposta la distanza massima della nebbia.
	 */
	void setEnd(float _end);

    protected:
	/**
	 * Il costruttore � protetto per rispettare il pattern.
	 * Il suo compito � quello di inizializzare il contatore.
	 */
	FogPanel();

	/**
	 * Il contatore.
	 */
	float array[4];
    private:
	/**
	 * L'istanza del singleton.
	 */
	static FogPanel* instance;
};

#endif
