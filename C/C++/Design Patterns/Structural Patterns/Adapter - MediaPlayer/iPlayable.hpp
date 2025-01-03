#ifndef IPLAYABLE_H
#define IPLAYABLE_H
#include <string>

using namespace std;

class iPlayable {
  public:
    virtual void play(string type, string name) = 0;
};

#endif