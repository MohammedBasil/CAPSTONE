#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <vector>
#include <fstream>

class FileWriter
{
public:
    FileWriter(const char* filename);
    ~FileWriter();

    template <class T>
    void write(T element);
    template <class T>
    void writeall(std::vector<T>& list);
    void writeCode(const char* code);

private:
    std::ofstream _file;
};


// Templates require that definitions are in .h file

template <class T>
void FileWriter::write(T element)
{
        T::writeToFile(_file, element);  //Calls a different function according to type T
}

template <class T>
void FileWriter::writeall(std::vector<T>& list)
{
    unsigned int listsize = list.size();
    _file.write(reinterpret_cast<char*>(&listsize), sizeof (unsigned int)); //Writes number of elements to facilitate reading
    for(size_t i=0; i<listsize; i++)
    {
        write<T>(list[i]);
    }
}



#endif // FILEWRITER_H
