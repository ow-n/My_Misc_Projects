#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Base {
    Base *next; // 1. "next" pointer in the base class
  public:
    Base() {
        next = 0;
    }
    void setNext(Base *n) {
        next = n;
    }
    void add(Base *n) {
        if (next)
          next->add(n);
        else
          next = n;
    }
    // 2. The "chain" method in the base class always delegates to the next obj
    virtual void handle(int i) {
        next->handle(i);
    }
};

class Dollar100: public Base {
  public:
    void handle(int i) {
        int count = i / 100;
        int remain = i % 100;
        if(count > 0)
            cout << "Retrieve " << count << " $100-dollar bills." << endl;
        if (remain > 0)
            Base::handle(remain);
    }
};

class Dollar20: public Base {
  public:
    void handle(int i) {
        int count = i / 20;
        int remain = i % 20;
        if(count > 0)
            cout << "Retrieve " << count << " $20-dollar bills." << endl;
        if (remain > 0)
            Base::handle(remain);
    }
};

class Dollar10: public Base {
  public:
    void handle(int i)
    {
        int count = i / 10;
        int remain = i % 10;
        if(count > 0)
            cout << "Retrieve " << count << " $10-dollar bills." << endl;
        if (remain > 0)
            Base::handle(remain);
    }
};

class Dollar5: public Base {
  public:
    void handle(int i) {
        int count = i / 5;
        int remain = i % 5;
        if(count > 0)
            cout << "Retrieve " << count << " $5-dollar bills." << endl;
        if (remain > 0)
            Base::handle(remain);
    }
};

class Dollar1: public Base {
  public:
    void handle(int i)
    {
        int count = i;
        if(count > 0)
            cout << "Retrieve " << count << " $1-dollar bills." << endl;
    }
};

int main() {
  Dollar100 root;
  Dollar20 node2;
  Dollar10 node3;
  Dollar5 node4;
  Dollar1 node5;
  root.add(&node2);
  root.add(&node3);
  root.add(&node4);
  root.add(&node5);
  int cash;
  cout << "How much do you want? ";
  cin >> cash;
  cout << cash << endl;
  root.handle(cash);
}
