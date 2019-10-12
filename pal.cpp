#include <stdio.h>
#include <tinyfiledialogs/tinyfiledialogs.h>
#include "pal.h"
#include <string.h>

#define RED		0
#define GREEN	1
#define BLUE	2

size_t PAL::GetFileSize(FILE *pFile)
{
	size_t fileLen;
	
	fseek(pFile, 0, SEEK_END);
	fileLen = ftell(pFile);
	rewind(pFile);
	
	return fileLen;
}

unsigned int PAL::ReadPal(std::string filename, uint32_t offset)
{
	uint8_t buffer[3];
	Palette curPal; 
	size_t fileLen;
	const char* error;
	mPalettes.clear();
	
	FILE *pFile = fopen(filename.c_str(), "rb");
	if (pFile == NULL)
	{
		error = "Could not open pallette file!";
		tinyfd_messageBox(error, error, "ok", "error", 1);
		return PAL_NOK;
	}
	
	fileLen = GetFileSize(pFile);
	
	if (offset > fileLen)
	{
		error = "Offset greater than file size!";
		tinyfd_messageBox(error, error, "ok", "error", 1);
		return PAL_NOK;
	}
	
	fseek(pFile, offset, SEEK_SET);
	
	for (int i = offset; i + 3 < fileLen; i+=3)
	{
		fread(buffer, 1, 3, pFile);
		curPal.r = buffer[RED];
		curPal.g = buffer[GREEN];
		curPal.b = buffer[BLUE];
		
		mPalettes.push_back(curPal);
	}
	
	return PAL_OK;
}

size_t PAL::GetNumPalettes()
{
	return mPalettes.size();
}

Palette PAL::operator [](size_t index)
{
	return mPalettes[index];
}

PAL::PAL()
{
	
}

PAL::~PAL()
{
	
}
