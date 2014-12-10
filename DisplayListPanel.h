#ifndef DISPLAY_LIST_PANEL_H
#define DISPLAY_LIST_PANEL_H

/**
 * La classe permette di ottenere un \p GLuint unico da utilizzarsi con
 * la creazione di <em>Display List</em>, come documenta questo breve codice:
 * \code
displayList = DisplayListPanel::getInstance()->getUniqueInt();
glNewList(displayList, GL_COMPILE);
\endcode
 * La classe realizza il pattern Singleton.
 */
class DisplayListPanel {
    public:
	/**
	 * Metodo per ottenere l'istanza del singleton.
	 *
	 * \return l'istanza.
	 */
	static DisplayListPanel* getInstance();

	/**
	 * Restituisce un intero unico partendo da \p 1.
	 *
	 * \return l'intero unico.
	 */
	unsigned int getUniqueInt();

    protected:
	/**
	 * Il costruttore è protetto per rispettare il pattern.
	 * Il suo compito è quello di inizializzare il contatore.
	 */
	DisplayListPanel();

	/**
	 * Il contatore.
	 */
	unsigned int counter;

    private:
	/**
	 * L'istanza del singleton.
	 */
	static DisplayListPanel* instance;
};

#endif
