#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Cook
{
  string name;
  public:
    Cook(string s)
    {
        name = s;
    }
    void cookFish(string s)
    {
        cout << "This is a fish dish from " << name << endl;
    }
    void cookBurger(string s)
    {
        cout << "This is a burger from " << name << endl;
    }
    void cookSteak(string s)
    {
        cout << "This is a " << s << " Rib-Eye steak from " << name << endl;
    }
};

class Command
{
  public:
    virtual void execute(string s) = 0;
};

class SimpleCommand: public Command
{
    typedef void(Cook::*Action)(string s);
    Cook *receiver;
    Action action;
  public:
    SimpleCommand(Cook *rec, Action act)
    {
        receiver = rec;
        action = act;
    }
     /*virtual*/void execute(string s)
    {
        (receiver->*action)(s);
    }
};

class MacroCommand: public Command
{
    vector < Command * > list;
  public:
    void add(Command *cmd)
    {
        list.push_back(cmd);
    }
     /*virtual*/void execute(string s)
    {
        for (int i = 0; i < list.size(); i++)
          list[i]->execute(s);
    }
};

int main()
{
    Cook cook1("Sam");
    Cook cook2("Sara");
    SimpleCommand order1(&cook1, &Cook::cookFish);
    //order1.execute("well");
    SimpleCommand order2(&cook2, &Cook::cookSteak);
    //order2.execute("median well");
    MacroCommand order3;
    order3.add(&order1);
    order3.add(&order2);
    order3.execute("well");
}
