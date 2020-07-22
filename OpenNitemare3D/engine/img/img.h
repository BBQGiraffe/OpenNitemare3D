#ifndef _IMG_H
#define _IMG_H

#include <vector>
#include "../pal/pal.h"
#include "Sprite.h"
#undef main

#define APPARENT_OFFSET 1156
#define MAX_SIZE		255

#define IMG_OK 	0
#define IMG_NOK	-1




class IMG
{
private:
	typedef std::vector<Sprite*> surfaceVector;
	typedef std::vector<size_t> offsetVector;
	std::vector<Sprite*> sprites;
	
	surfaceVector mSurfaces;
	
	int ReadFiles(FILE *pFile, offsetVector &offsets);
	int LoadImgFile(std::string imgFile);
	void GetFileOffsets(FILE *pFile, offsetVector &offsets);

protected:

public:

	


	PAL mPal;
	int Init(std::string palFile, std::string imgFile);
	void Cleanup();
	
	size_t GetNumImages();
	Sprite* operator [](size_t index);

	IMG();
	~IMG();
};

#endif
