#ifndef _TILES_H
#define _TILES_H
#include "../map/Tile.h"
#include <map>
#include <iostream>
class Tiles {
private:
	std::map<int, Tile> tiles;
	
public:
	void RegisterTile(int id, int texture);
	Tile GetTile(int id);
	Tiles();
};
#endif