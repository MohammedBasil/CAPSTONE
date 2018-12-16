#include "filereader.h"

FileReader::FileReader(const char* filename)
    : _file(filename, std::ios::in|std::ios::binary) {}

FileReader::~FileReader()
{
    if(_file.is_open())
    {
        _file.close();
    }
}

void FileReader::readCode(char* code)
{
    _file.read(code, 8);
}

