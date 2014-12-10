#include "DisplayListPanel.h"

DisplayListPanel* DisplayListPanel::instance = 0;

DisplayListPanel* DisplayListPanel::getInstance() {
	if(instance == 0) {
		instance = new DisplayListPanel();
	}
	return instance;
}

DisplayListPanel::DisplayListPanel() {
	counter = 0;
}

unsigned int DisplayListPanel::getUniqueInt() {
	return ++counter;
}
