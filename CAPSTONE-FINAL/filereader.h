#ifndef FILEREADER_H
#define FILEREADER_H

#include <vector>
#include <fstream>

class FileReader
{
    public:
        FileReader(const char* filename);
        ~FileReader();

        template <class T>
        T read();
        template <class T>
        void readall(std::vector<T>& list);
        void readCode(char* code);

    private:
        std::ifstream _file;

};

// Templates require that definitions are in .h file

template <class T>
T FileReader::read()
{
    return T::readFromFile(_file); //Calls a different function depending on type T
}

template <class T>
void FileReader::readall(std::vector<T>& list)
{
    if (_file.good())
    {
        list.clear();

        unsigned int listsize;
        _file.read((char*)(&listsize), sizeof (unsigned int)); //Read number of elements to read
        for (unsigned int i =0; i<listsize; i++)
        {
            T element = read<T>();
            if (_file.eof() || _file.fail()) {break;}
            list.push_back(element);
        }
    }
}



#endif // FILEREADER_H
