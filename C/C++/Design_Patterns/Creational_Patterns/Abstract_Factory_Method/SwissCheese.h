#ifndef SWISSCHEESE_H
#define SWISSCHEESE_H
#include "Cheese.h"

using namespace std;

class SwissCheese: public Cheese
{
	public:
		SwissCheese()
		{
			cout << "Create SwissCheese." << endl;
			name = "SwissCheese";
		}
		virtual void taste();
};

void SwissCheese::taste()
{
	cout << "It tastes like a " + label + " Swiss Cheese." << endl;
}
#endif