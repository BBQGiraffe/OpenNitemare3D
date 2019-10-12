#ifndef __PAL_H__
#define __PAL_H__

#include <string>
#include <vector>

#include <stdint.h>

#define PAL_OK		0
#define PAL_NOK 	-1

typedef struct 
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
}Palette;

class PAL
{
private:
	std::vector<Palette> mPalettes;

	size_t GetFileSize(FILE *pFile);

protected:

public:
	unsigned int ReadPal(std::string filename, uint32_t offset);
	size_t GetNumPalettes();
	Palette operator[](size_t);

	PAL();
	~PAL();
};

#endif
