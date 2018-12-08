#include "student.h"
#include "course.h"

Course Course::readFromFile(ifstream& file)
{
    ResCode code;
    Status status;
    ResCode degree;
    ID professor1ID;
    ID professor2ID;
    unsigned int credits;

    code = getRCFromFile(file);
    file.read((char*)(&status), sizeof(Status));

    unsigned int stringsize = 0;
    file.read((char*)(&stringsize), sizeof(unsigned int));
    string name(stringsize, '\0');
    file.read(&name[0], stringsize);

    degree = getRCFromFile(file);
    professor1ID = ID::getFromFile(file);
    professor2ID = ID::getFromFile(file);
    file.read((char*)(&credits), sizeof (unsigned int));

    Course course = Course(code, name, degree, professor1ID, professor2ID, credits, status);

    unsigned int numStudents;
    file.read((char*)(&numStudents), sizeof (unsigned int));
    vector<Mark> marks;

    for (unsigned int i=0; i<numStudents; i++)
    {
        marks.push_back(Mark::getFromFile(file));
    }

    course.setMarks(marks);

    return course;
}

void Course::writeToFile(ofstream& _file, Course element)
{
    _file.write(element._code.full, sizeof(ResCode));
    _file.write(reinterpret_cast<char*>(&element._status), sizeof(Status));

    unsigned int stringsize = element._name.size();
    _file.write(reinterpret_cast<char*>(&stringsize), sizeof(unsigned int));
    _file.write(element._name.c_str(), stringsize);

    _file.write(element._degree.full, sizeof(ResCode));
    _file.write(element._professor1ID.id, sizeof(ID));
    _file.write(element._professor2ID.id, sizeof(ID));
    _file.write(reinterpret_cast<char*>(&element._credits), sizeof(unsigned int));

    //We write the number of students in the list
    unsigned int numStudents = element._listofmarks.size();
    _file.write(reinterpret_cast<char*>(&numStudents), sizeof(unsigned int));

    for (size_t i=0; i<numStudents; i++)
    {
        _file.write(element._listofmarks[i].studentID.id, sizeof(ID));
        _file.write(reinterpret_cast<char*>(&element._listofmarks[i].grade), sizeof(float));
    }

}
