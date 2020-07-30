#ifndef _TILE_H
#define _TILE_H
//boring old flat tile
class Tile {
public:
	bool flipped;
	enum Type {
		WALL,
		REVWALL,
		SPECIAL1,
		WALL_EX1,
		ONE_SHOT,
		WARP_S1,
		WARP_L4,
		WARP_L2,
		DOORVC,
		DOORHC,
		DOORV,
		DOORH,
		JAMB,
		DOORVL,
		DOORHL
	};
	Type type;
	int texture;
	Tile(int texture) {
		this->texture = texture;
	}
	Tile() {
		this->texture = 0;
	}
	
};
#endif // !_TILE_H
