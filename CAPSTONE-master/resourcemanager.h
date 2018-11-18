#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "course.h"
#include "fdp.h"
#include "seminar.h"
#include <vector>

using namespace std;

class ResourceManager
{
    public:
        ResourceManager(){}
        void createResource();
        void createCourse();
        void createFDP();
        void createSeminar();

        void editResource();
        void editCourse(const ResCode &code);
        void editFDP(const ResCode &code);
        void editSeminar(const ResCode &code);

        void deleteResource();

        ResCode createResCode();

    private:
        vector<Course> _courselist;
        vector<FDP> _FDPlist;
        vector<Seminar> _seminarlist;
};

#endif // RESOURCEMANAGER_H
