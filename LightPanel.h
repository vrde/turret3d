#ifndef LIGHT_PANEL_H
#define LIGHT_PANEL_H

/**
 * Questa classe può essere vista come un vero e proprio pannello per
 * configurare le luci del gioco.
 * La classe realizza il pattern Singleton.
 */
class LightPanel {
    public:
	/**
	 * Metodo per ottenere l'istanza del singleton.
	 *
	 * \return l'istanza.
	 */
	static LightPanel* getInstance();
	
	/**
	 * Abilita la luce specificata.
	 *
	 * \param _light la luce (ad esempio \p GL_LIGHT0, \p GL_LIGHT1 ecc.).
	 */
	void enable(int _light);

	/**
	 * Disabilita la luce specificata.
	 *
	 * \param _light la luce (ad esempio \p GL_LIGHT0, \p GL_LIGHT1 ecc.).
	 */
	void disable(int _light);

	/**
	 * Imposta la posizione per la luce specificata.
	 *
	 * \param _light la luce (ad esempio \p GL_LIGHT0, \p GL_LIGHT1 ecc.).
	 * \param _x la posizione \p x;
	 * \param _y la posizione \p y;
	 * \param _z la posizione \p z;
	 */
	void setPosition(int _light, float _x, float _y, float _z);

	/**
	 * Imposta la componente ambientale per la luce specificata.
	 *
	 * \param _light la luce (ad esempio \p GL_LIGHT0, \p GL_LIGHT1 ecc.).
	 * \param _r la quantità di rosso;
	 * \param _g la quantità di verde;
	 * \param _b la quantità di blu;
	 * \param _a il componente alfa.
	 */
	void setAmbient(int _light, float _r, float _g, float _b, float _a);

	/**
	 * Imposta la componente di diffusione per la luce specificata.
	 *
	 * \param _light la luce (ad esempio \p GL_LIGHT0, \p GL_LIGHT1 ecc.).
	 * \param _r la quantità di rosso;
	 * \param _g la quantità di verde;
	 * \param _b la quantità di blu;
	 * \param _a il componente alfa.
	 */
	void setDiffuse(int _light, float _r, float _g, float _b, float _a);

	/**
	 * Imposta la componente speculare per la luce specificata.
	 *
	 * \param _light la luce (ad esempio \p GL_LIGHT0, \p GL_LIGHT1 ecc.).
	 * \param _r la quantità di rosso;
	 * \param _g la quantità di verde;
	 * \param _b la quantità di blu;
	 * \param _a il componente alfa.
	 */
	void setSpecular(int _light, float _r, float _g, float _b, float _a);


	/**
	 * Imposta la componente di illuminazione ambientale globale.
	 *
	 * \param _r la quantità di rosso;
	 * \param _g la quantità di verde;
	 * \param _b la quantità di blu;
	 * \param _a il componente alfa.
	 */
	void setGlobalAmbient(float _r, float _g, float _b, float _a);

    protected:
	/**
	 * Il costruttore è protetto per rispettare il pattern.
	 * Il suo compito è quello di inizializzare il contatore.
	 */
	LightPanel();

	/**
	 * L'array è utilizzato per i valori temporanei.
	 */
	float array[4];
    private:
	/**
	 * L'istanza del singleton.
	 */
	static LightPanel* instance;
};

#endif
