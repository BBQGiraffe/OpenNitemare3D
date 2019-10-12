#include "fileNames.h"

#include <string>

/*this function makes  it so you don't have to remember sprite indexes.

  Note: not yet complete, incorrectly labled



I unfortunatly have to go through each sprite and label it
*/
int FileNames::getSprite(std::string index) {
	if (index == "RED_WALL_DOUBLE_PLAIN") { 
		return 0;
	}
	else if (index == "RED_WALL_SINGLE_PAINTING") {
		return 1;

	}
	else if (index == "RED_WALL_DOUBLE_CANDLE_FR1") {
		return 2;
	}
	else if (index == "RED_WALL_DOUBLE_CANDLE_FR2") {
		return 3;
	}
	
}