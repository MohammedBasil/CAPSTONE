#include "student.h"
#include "course.h"

Student Student::readFromFile(ifstream& file)
{
    ID id;
    char password[32];
    ResCode degree;

    id = ID::getFromFile(file);             // Read ID
    file.read(password,32);                 // Read password
    degree = ResCode::getFromFile(file);    // Read degree

    Student student = Student(id, password, degree);

    return student;
}

void Student::writeToFile(ofstream& _file, const Student& element)
{
    _file.write(element._id.id, sizeof(ID));                    // Write ID
    _file.write(element._password, sizeof(element._password));  // Write password
    _file.write(element._degree.code, sizeof(ResCode));         // Write degree
}




