#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Component {
  public:
    virtual void traverse() = 0;
};

class File: public Component {
    string filename;
  public:
    File(string val)
    {
        filename = val;
    }
    void traverse()
    {
        cout << filename << " ";
    }
};

class Composite: public Component {
    vector < Component * > children;
    string value;
  public:
    Composite(string val) {
        value = val;
    }
    void add(Component *c) {
        children.push_back(c);
    }
    void traverse() {
        cout << value << endl;
        for (int i = 0; i < children.size(); i++) {
          cout << "-- ";
          children[i]->traverse();
          cout << endl;
        }
    }
};

class Folder: public Composite {
  public:
    // Two different kinds of "con-
    Folder(string val): Composite(val){}
    // tainer" classes.  Most of the
    void traverse() {
        // "meat" is in the Composite
        cout << "Folder: "; // base class.
        Composite::traverse();
    }
};

int main() {
  Folder folder1("root");         
  Folder folder2("hw1");          
  Folder folder3("hw2");                 
  File file1("stack.cpp");               
  File file2("queue.cpp");               
  File file3("client.cpp");              
  File file4("lecture1.ppt");              
  File file5("lecture2.ppt");                
  folder2.add(&file1);
  folder3.add(&file2);
  folder3.add(&file3);
  folder1.add(&folder2);              
  folder1.add(&folder3);         
  folder1.add(&file4);       
  folder1.add(&file5);        
  folder1.traverse();
  cout << "----------------" << endl;
  folder2.traverse();
  cout << "----------------" << endl;
  folder3.traverse();
}
