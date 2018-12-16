#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>
#include "virtualcampus.h"
#include "course.h"
#include "fdp.h"
#include "seminar.h"

using namespace std;

class UniversityMember;
class Student;

class ResourceManager
{
    public:
        ResourceManager(VirtualCampus& campus);
        ~ResourceManager();

        // Resource creation methods
        void createResource();
        void createDegree();
        void createCourse();
        void createFDP();
        void createSeminar();

        // Resource edition methods
        void editResource(const UniversityMember* user);
		void editMarks(const UniversityMember* user);
        void editDegree(const ResCode& code);
        void editCourse(const ResCode& code);
        void editFDP(const ResCode& code);
        void editSeminar(const ResCode& code);

        void deleteResource();

        // Resource listing methods
        void showResources(const UniversityMember* user);
        void showCourses(const UniversityMember* user);
        void showFDPs(const UniversityMember* user);
        void showSeminars(const UniversityMember* user);

        // General getters
		Degree* getDegree(const ResCode& code);
		Course* getCourse(const ResCode& code);
		FDP* getFDP(const ResCode& code);
		Seminar* getSeminar(const ResCode& code);

        // Getters based on user
		vector<Course*> getEnrolledCourses(const UniversityMember* user);
		vector<FDP*> getEnrolledFDPs(const UniversityMember* user);
		vector<Seminar*> getEnrolledSeminars(const UniversityMember* user);

        // Student methods
		void enrollCourse(const Student* student);
		void disenrollCourse(const Student* student);

		void enrollFDP(const Student* student);
		void disenrollFDP(const Student* student);

		void enrollSeminar(const Student* student);
		void disenrollSeminar(const Student* student);

        // Methods to check input exists
		bool userExists(const ID& id, Role role);
        ID getExistingUserFromConsole(Role role, bool optional=false);
		ResCode getExistingDegreeFromConsole();

        // Write to file methods
        void saveCourses();
        void saveFDPs();
        void saveSeminars();

        ResCode createResCode();

    private:
        VirtualCampus&      _campus;
        ResCode             _RCgenerator;

        vector<Degree>      _degreeList;
        vector<Course>      _courselist;
        vector<FDP>         _FDPlist;
        vector<Seminar>     _seminarlist;
};

#endif // RESOURCEMANAGER_H
