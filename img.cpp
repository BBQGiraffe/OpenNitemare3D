#include <stdio.h>
#include <tinyfiledialogs/tinyfiledialogs.h>
#include "img.h"

#define APPARENT_OFFSET 1156
#define MAX_SIZE		255
#define PIXEL_SIZE		4

SDL_Surface * IMG::operator [](size_t index)
{
	if (index > mSurfaces.size())
	{
		return NULL;
	}

	return mSurfaces[index];
}

size_t IMG::GetNumImages()
{
	return mSurfaces.size();
}

int IMG::ReadFiles(FILE* pFile, offsetVector& offsets)
{
	uint8_t buffer[MAX_SIZE * MAX_SIZE * PIXEL_SIZE];
	uint8_t sizeX;
	uint8_t sizeY;
	uint8_t pixValue;
	SDL_Surface* pSurface;

	for (size_t offset : offsets)
	{
		if (fseek(pFile, offset, SEEK_SET) != 0)
		{
			tinyfd_messageBox("Failed to seek to next file in list; malformed?", "Failed to seek to next file in list; malformed?", "ok", "error", 1);
			return IMG_NOK;
		}
		fread(&sizeX, 1, 1, pFile);
		fread(&sizeY, 1, 1, pFile);
		fseek(pFile, 8, SEEK_CUR);
		for (int i = 0; i < sizeX * sizeY; i++)
		{
			fread(&pixValue, 1, 1, pFile);
			if (pixValue != 0xFF)
			{
				buffer[i * PIXEL_SIZE] = mPal[pixValue].r;
				buffer[i * PIXEL_SIZE + 1] = mPal[pixValue].g;
				buffer[i * PIXEL_SIZE + 2] = mPal[pixValue].b;
				buffer[i * PIXEL_SIZE + 3] = 0xFF;
			}
			else
			{
				buffer[i * PIXEL_SIZE] = 0xFF;
				buffer[i * PIXEL_SIZE + 1] = 0xFF;
				buffer[i * PIXEL_SIZE + 2] = 0xFF;
				buffer[i * PIXEL_SIZE + 3] = 0x00;
			}
		}

		pSurface = SDL_CreateRGBSurfaceWithFormat(0, sizeY, sizeX,
			32, SDL_PIXELFORMAT_RGBA32);
		SDL_LockSurface(pSurface);
		memcpy(pSurface->pixels, buffer, sizeX * sizeY * PIXEL_SIZE);
		SDL_UnlockSurface(pSurface);
		mSurfaces.push_back(pSurface);

		memset(buffer, 0, sizeof(buffer));
	}

	return IMG_OK;
}

void IMG::GetFileOffsets(FILE* pFile, offsetVector& offsets)
{
	int retval;
	uint32_t offset;
	uint32_t firstOffset = 0;

	do
	{
		retval = fread(&offset, 4, 1, pFile);
		if (offset != 0)
		{
			offsets.push_back(offset);
		}
		if (firstOffset == 0) { firstOffset = offset; printf("First offset: %x\n", firstOffset); }
	} while (ftell(pFile) < firstOffset && retval > 0);
}

int IMG::LoadImgFile(std::string imgFile)
{
	FILE* pFile;
	offsetVector fileOffsets;
	uint32_t temp;

	fileOffsets.clear();

	pFile = fopen(imgFile.c_str(), "rb");
	if (pFile == NULL)
	{
		tinyfd_messageBox("could not open IMG file", "could not open IMG file", "ok", "error", 1);
		return IMG_NOK;
	}

	fseek(pFile, 4, SEEK_SET);

	GetFileOffsets(pFile, fileOffsets);
	if (ReadFiles(pFile, fileOffsets) == IMG_NOK)
	{
		
		return IMG_NOK;
	}

	return IMG_OK;
}

int IMG::Init(std::string palFile, std::string imgFile)
{
	if (mPal.ReadPal(palFile, APPARENT_OFFSET) != PAL_OK)
	{
		return IMG_NOK;
	}

	if (LoadImgFile(imgFile) != IMG_OK)
	{
		return IMG_NOK;
	}

	return IMG_OK;
}

void IMG::Cleanup()
{
	for (SDL_Surface* pSurface : mSurfaces)
	{
		SDL_FreeSurface(pSurface);
	}

	mSurfaces.clear();
}

IMG::IMG()
{

}

IMG::~IMG()
{
	Cleanup();
}
