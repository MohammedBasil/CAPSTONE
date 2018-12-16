#include "student.h"
#include "course.h"

void Course::modifyMark(const ID& id, float grade)
{
	for (auto it = _listofmarks.begin(); it != _listofmarks.end(); it++)
	{
		if (it->studentID.Equals(id))
		{
			it->grade = grade;
		}
	}
}

void Course::deleteMark(const ID& id)
{
	for (auto it = _listofmarks.begin(); it != _listofmarks.end(); it++)
	{
		if (it->studentID.Equals(id))
		{
			_listofmarks.erase(it);
			break;
		}
	}
}

bool Course::isEnrolled(const ID& id)
{
	if (_professor1ID.Equals(id) || _professor2ID.Equals(id))
	{
		return true;
	}

	for (auto it = _listofmarks.begin(); it != _listofmarks.end(); it++)
	{
		if (it->studentID.Equals(id))
		{
			return true;
		}
	}
	return false;
}

Course Course::readFromFile(ifstream& file)
{
    ResCode code;
    Status status;
    ResCode degree;
    ID professor1ID;
    ID professor2ID;
    unsigned int credits;

    code = ResCode::getFromFile(file);                          // Read code
    file.read((char*)(&status), sizeof(Status));                // Read status

    unsigned int stringsize = 0;                                // Read size of name
    file.read((char*)(&stringsize), sizeof(unsigned int));
    string name(stringsize, '\0');                              // Create string of zeros with given size
    file.read(&name[0], stringsize);                            // Read name

    degree = ResCode::getFromFile(file);                        // Read degree
    professor1ID = ID::getFromFile(file);                       // Read professor 1
    professor2ID = ID::getFromFile(file);                       // Read professor 2
    file.read((char*)(&credits), sizeof (unsigned int));        // Read number of credits

    Course course = Course(code, name, degree, professor1ID, professor2ID, credits, status);

    unsigned int numStudents;                                   // Read number of students
    file.read((char*)(&numStudents), sizeof (unsigned int));
    vector<Mark> marks;

    for (unsigned int i=0; i<numStudents; i++)
    {
        marks.push_back(Mark::getFromFile(file));               // Read ID and grade for each student
    }

    course.setMarks(marks);

    return course;
}

void Course::writeToFile(ofstream& _file, Course element)
{
    _file.write(element._code.code, sizeof(ResCode));                                   // Write code
    _file.write(reinterpret_cast<char*>(&element._status), sizeof(Status));             // Write status

    unsigned int stringsize = element._name.size();                                     // Write size of name
    _file.write(reinterpret_cast<char*>(&stringsize), sizeof(unsigned int));
    _file.write(element._name.c_str(), stringsize);                                     // Write name

    _file.write(element._degree.code, sizeof(ResCode));                                 // Write degree
    _file.write(element._professor1ID.id, sizeof(ID));                                  // Write professor 1
    _file.write(element._professor2ID.id, sizeof(ID));                                  // Write professor 2
    _file.write(reinterpret_cast<char*>(&element._credits), sizeof(unsigned int));      // Write number of credits

    unsigned int numStudents = element._listofmarks.size();                             // Write number of students
    _file.write(reinterpret_cast<char*>(&numStudents), sizeof(unsigned int));

    for (size_t i=0; i<numStudents; i++)
    {
        _file.write(element._listofmarks[i].studentID.id, sizeof(ID));                          // Write ID of each student
        _file.write(reinterpret_cast<char*>(&element._listofmarks[i].grade), sizeof(float));    // Write mark of each student
    }

}
