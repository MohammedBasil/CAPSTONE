#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "universitymember.h"

class Administrator : public UniversityMember
{
  public:
    Administrator( const ID id, const char* password)
        : UniversityMember(id, password) { setRole(); }

    static Administrator readFromFile(ifstream& file);
    static void writeToFile(ofstream& _file, const Administrator& element);

  private:
    virtual void setRole() override { _role = Role::Administrator; }
};


#endif // ADMINISTRATOR_H
