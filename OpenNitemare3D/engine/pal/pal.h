#ifndef __PAL_H__
#define __PAL_H__

#include <string>
#include <vector>

#include <stdint.h>
#include "../img/Color.h"

#define PAL_OK		0
#define PAL_NOK 	-1

/*
typedef struct 
{
	std::int8_t r;
	std::int8_t g;
	std::int8_t b;
}Palette;
*/
class PAL
{
private:
	std::vector<Color> mPalettes;

	size_t GetFileSize(FILE *pFile);

protected:

public:
	unsigned int ReadPal(std::string filename, uint32_t offset);
	size_t GetNumPalettes();
	Color operator[](size_t);

	PAL();
	~PAL();
};

#endif
