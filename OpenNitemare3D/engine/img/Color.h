#ifndef _COLOR_H
#define _COLOR_H
//because SDL_Color took up too many bytes

struct Color {

	
	std::int8_t r, g, b;
	Color(std::int8_t r, std::int8_t g, std::int8_t b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	Color() {

	}

	friend bool operator!=(const Color& a, const Color& b) {
		if (a.r != b.r && a.b != b.b && a.g != b.g) {
			return true;
		}
		return false;
	}
};


#endif // !_COLOR_H
