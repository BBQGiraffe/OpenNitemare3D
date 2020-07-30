#ifndef _DATREADER_H
#define _DATREADER_H
#include <fstream>
#include "Datoffset.h"
#include <iostream>

struct DatConent {
public:
	char* data;
	uint16_t length;
	DatConent(char* data, uint16_t length) {
		this->data = data;
		this->length = length;
	}
};

class Datreader {
private:
	FILE* pFile;
	std::vector<DATOffset> offsets;
	std::vector<DatConent> data;

public:
	void LoadOffsets();
	void GetFiles(std::string filename);
	Datreader(std::string filename);

	DatConent operator [](int index);

};


#endif