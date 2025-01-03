#include <iostream>
#include <string>
using namespace std;

// 1. Add an accept(Visitor) method to the "element" hierarchy
class Element {
  public:
    virtual void accept(class Visitor &v) = 0;
};

class This: public Element {
  public:
    string thiss() { return "This"; }
    /*virtual*/
    void accept(Visitor &v);
};

class That: public Element {
  public:
    string that() { return "That"; }
    /*virtual*/
    void accept(Visitor &v);
};

class TheOther: public Element {
  public:
    string theOther() { return "TheOther"; }
    /*virtual*/
    void accept(Visitor &v);
};

// 2. Create a "visitor" base class w/ a visit() method for every "element" type
class Visitor {
  public:
    virtual void visit(This *e) = 0;
    virtual void visit(That *e) = 0;
    virtual void visit(TheOther *e) = 0;
};


// Implementation of Accept Method for each Element

void This::accept(Visitor &v) { v.visit(this); }

void That::accept(Visitor &v) { v.visit(this); }

void TheOther::accept(Visitor &v) { v.visit(this); }


// 3. Create a "visitor" derived class for each "operation" to do on "elements"
class UpVisitor: public Visitor {
  /*virtual*/void visit(This *e) { cout << "do Up on " + e->thiss() << '\n'; }
  /*virtual*/void visit(That *e) { cout << "do Up on " + e->that() << '\n'; }
  /*virtual*/void visit(TheOther *e) { cout << "do Up on " + e->theOther() << '\n'; }
};

class DownVisitor: public Visitor {
  /*virtual*/void visit(This *e) { cout << "do Down on " + e->thiss() << '\n'; }
  /*virtual*/void visit(That *e) { cout << "do Down on " + e->that() << '\n'; }
  /*virtual*/void visit(TheOther *e) { cout << "do Down on " + e->theOther() << '\n'; }
};

int main() {
  Element *list[] = { new This(), new That(), new TheOther() };
  UpVisitor up; // 4. Client creates
  DownVisitor down; //    "visitor" objects
  for (int i = 0; i < 3; i++)
    list[i]->accept(up);        // and passes each
  for (int i = 0; i < 3; i++)   //  to accept() calls
    list[i]->accept(down);
}
