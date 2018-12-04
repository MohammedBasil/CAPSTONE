#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "universitymember.h"


class Professor : public UniversityMember
{
  public:
    Professor( const ID id, const char* password)
        : UniversityMember(id, password) { setRole(); }
    //virtual ~Professor() override { UniversityMember::~UniversityMember(); }

    static Professor readFromFile(ifstream& file);
    static void writeToFile(ofstream& _file, Professor element);

  private:
    virtual void setRole() override { _role = Role::Professor; }

};
#endif // PROFESSOR_H
