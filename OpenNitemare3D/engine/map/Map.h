#ifndef _MAP_H
#define _MAP_H
#include <vector>
#include <string>
#include <fstream>
class Map {
private:
    char* mapbuff = new char[8192];
    
public:
    char* maptiles = new char[4096];
    Map(std::string file) {

    }
    void LoadMap(int index);


};
#endif // !_MAP_H
