#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "universitymember.h"


class Professor : public UniversityMember
{
  public:
    Professor( const ID id, const char* password)
        : UniversityMember(id, password) { setRole(); }
    //virtual ~Professor() override { UniversityMember::~UniversityMember(); }

  private:
    virtual void setRole() override { _role = Role::Professor; }

};
#endif // PROFESSOR_H
