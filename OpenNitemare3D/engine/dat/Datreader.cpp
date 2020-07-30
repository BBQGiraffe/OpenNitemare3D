#include "Datreader.h"

void Datreader::LoadOffsets()
{
    int retval;
    DATOffset offset;
    uint16_t lowestOffset = 0xFFFFFFFF;

    do
    {   
        retval = fread(&offset.length, 2, 1, pFile);
        retval = fread(&offset.position, 4, 1, pFile);
        offsets.push_back(offset);
        if (offset.length != 0)
        {

            if (offset.length < lowestOffset)
            {
                lowestOffset = offset.length;
            }
        }
    } while (ftell(pFile) <= lowestOffset && retval > 0);
}

void Datreader::GetFiles(std::string filename)
{
    std::ifstream dat;
    dat.open(filename, std::ios::binary);
    
    for (int i = 0; i < offsets.size(); i++) {
        DATOffset offset = offsets[i];
        char* buff = new char[offset.length];
        
        dat.seekg(offset.position);
        dat.read(buff, offset.length);
        
        data.push_back(DatConent(buff, offset.length));
    }
 
}

Datreader::Datreader(std::string filename)
{
    pFile = fopen(filename.c_str(), "rb");
    LoadOffsets();
    GetFiles(filename);
}

DatConent Datreader::operator[](int index)
{
	return data[index];
}
