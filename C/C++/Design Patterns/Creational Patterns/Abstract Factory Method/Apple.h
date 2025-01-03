#ifndef APPLE_H
#define APPLE_H
#include "Fruit.h"

using namespace std;

class Apple: public Fruit
{
	public:
		Apple()
		{
			cout << "Make Apple." << endl;
			name = "Apple";
		}
		virtual void taste();
};

void Apple::taste()
{
	cout << "It tastes like a " + label + " apple." << endl;
}
#endif