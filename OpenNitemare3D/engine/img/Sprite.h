#ifndef _SPRITE_H
#define _SPRITE_H
#include "Color.h"
#include <vector>

struct Sprite {
public:
	std::int8_t width, height;
	std::vector<Color> buffer;
	Sprite(std::int8_t width, std::int8_t height, std::vector<Color> buffer) {
		this->width = width;
		this->height = height;
		this->buffer = buffer;
	}
	Sprite() {

	}


};

#endif