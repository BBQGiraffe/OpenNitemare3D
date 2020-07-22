#include <stdio.h>
#include <iostream>
#include "img.h"




Sprite* IMG::operator [](size_t index)
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
	//color buffer[MAX_SIZE * MAX_SIZE];
	std::vector<Color> buffer;
	uint8_t sizeX;
	uint8_t sizeY;
	uint8_t pixValue;

	if (fseek(pFile, offsets[0], SEEK_SET) != 0)
	{
		printf("Failed to seek to next file in list; malformed?\n");
		return IMG_NOK;
	}


	while (feof(pFile) == false)
	{
		int j = 0;
		fread(&sizeX, 1, 1, pFile);
		fread(&sizeY, 1, 1, pFile);
		fseek(pFile, 8, SEEK_CUR);
		for (int i = 0; i < sizeX * sizeY; i++)
		{
			fread(&pixValue, 1, 1, pFile);
			buffer.push_back(mPal[pixValue]);
		}
		Sprite* s = new Sprite(sizeX, sizeY, buffer);
		
		mSurfaces.push_back(s);
		buffer.clear();
	}
	

	return IMG_OK;
}
void IMG::GetFileOffsets(FILE* pFile, offsetVector& offsets)
{
	int retval;
	uint32_t offset;
	uint32_t lowestOffset = 0xFFFFFFFF;

	do
	{
		retval = fread(&offset, 4, 1, pFile);
		if (offset != 0)
		{
			offsets.push_back(offset);
			if (offset < lowestOffset)
			{
				lowestOffset = offset;
			}
		}
	} while (ftell(pFile) <= lowestOffset && retval > 0);
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
		printf("could not open IMG file\n");
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
	

	
}

IMG::IMG()
{

}

IMG::~IMG()
{
	Cleanup();
}

