#include "filewriter.h"

FileWriter::FileWriter(const char* filename)
    : _file(filename, std::ios::out|std::ios::binary|std::ios::trunc) {}

FileWriter::~FileWriter()
{
    if(_file.is_open())
    {
        _file.flush();
        _file.close();
    }
}

void FileWriter::writeCode(const char* code)
{
    _file.write(code, 8);
}
