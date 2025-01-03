#ifndef FRUIT_H
#define FRUIT_H
#include <iostream>
#include <string>

using namespace std;

class Fruit
{
	public:
		Fruit()
		{
			label = "";
			cout << "Make Fruit." << endl;
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