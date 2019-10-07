#ifndef __IMG_H__
#define __IMG_H__

#include <vector>

#include "pal.h"

#include "SDL.h"

#define IMG_OK 	0
#define IMG_NOK	-1

class IMG
{
private:
	typedef std::vector<SDL_Surface*> surfaceVector;
	typedef std::vector<size_t> offsetVector;
	
	PAL mPal;
	surfaceVector mSurfaces;
	
	int ReadFiles(FILE *pFile, offsetVector &offsets);
	int LoadImgFile(std::string imgFile);
	void GetFileOffsets(FILE *pFile, offsetVector &offsets);

protected:

public:
	int Init(std::string palFile, std::string imgFile);
	void Cleanup();
	
	size_t GetNumImages();
	SDL_Surface * operator [](size_t index);

	IMG();
	~IMG();
};

#endif
