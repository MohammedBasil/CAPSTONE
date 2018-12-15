#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "universitymember.h"

class Professor : public UniversityMember
{
  public:
    Professor( const ID id, const char* password)
        : UniversityMember(id, password) { setRole(); }

    static Professor readFromFile(ifstream& file);
    static void writeToFile(ofstream& _file, const Professor& element);

  private:
    virtual void setRole() override { _role = Role::Professor; }

};
#endif // PROFESSOR_H
