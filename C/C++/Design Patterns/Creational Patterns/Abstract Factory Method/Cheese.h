#ifndef CHEESE_H
#define CHEESE_H
#include <iostream>
#include <string>

using namespace std;

class Cheese
{
	public:
		Cheese()
		{
			label = "";
			cout << "Create Cheese." << endl;
		}
		void addLabel(string l)
		{
			label = l;
		}
		virtual void taste() = 0;
	protected:
		string name;
		string label;
};
#endif