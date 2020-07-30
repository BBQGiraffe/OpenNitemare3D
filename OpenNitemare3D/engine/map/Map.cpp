#include "Map.h"

void Map::LoadMap(int index)
{
    std::ifstream is;

    is.open("MAP.3", std::ios::binary);


    is.seekg(514 + (8192 * index));
    is.read(mapbuff, 8192);
}
