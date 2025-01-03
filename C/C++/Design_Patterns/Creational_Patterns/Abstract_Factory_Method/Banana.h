#ifndef BANANA_H
#define BANANA_H
#include "Fruit.h"

using namespace std;

class Banana: public Fruit
{
	public:
		Banana()
		{
			cout << "Make Banana." << endl;
			name = "Banana";
		}
		virtual void taste();
};

void Banana::taste()
{
	cout << "It tastes like a " + label + " banana." << endl;
}
#endif