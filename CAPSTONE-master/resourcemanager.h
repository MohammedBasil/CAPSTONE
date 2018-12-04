#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "course.h"
#include "fdp.h"
#include "seminar.h"
#include <vector>

using namespace std;

class ResourceManager
{
    friend class UserManager;
    public:
        ResourceManager();
        ~ResourceManager();

        void createResource();
        void createDegree();
        void createCourse();
        void createFDP();
        void createSeminar();

        void editResource();
        void editDegree(const ResCode &code);
        void editCourse(const ResCode &code);
        void editFDP(const ResCode &code);
        void editSeminar(const ResCode &code);

        void deleteResource();

        void showResources();
        void showCourses();
        void showFDPs();
        void showSeminars();

        vector<Course>& getCourselist(){return _courselist;}  //NUEVO

        ResCode createResCode();

    private:
        ResCode _RCgenerator;

        vector<Degree> _degreeList;
        vector<Course> _courselist;
        vector<FDP> _FDPlist;
        vector<Seminar> _seminarlist;
};

#endif // RESOURCEMANAGER_H
