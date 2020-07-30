#include "Tiles.h"

void Tiles::RegisterTile(int id, int texture)
{
	Tile tile(texture);
	
	

	tiles.insert(std::pair<int, Tile>(id, tile));
}

Tile Tiles::GetTile(int id)
{
	if (tiles.find(id) == tiles.end()) {
		std::cout << "Invalid Tile ID: " << id << std::endl;
	}
	return tiles[id];
}



Tiles::Tiles()
{
}
