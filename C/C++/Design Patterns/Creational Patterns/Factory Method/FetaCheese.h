#ifndef FETACHEESE_H
#define FETACHEESE_H
#include "Cheese.h"

using namespace std;

class FetaCheese: public Cheese
{
	public:
		FetaCheese()
		{
			cout << "Create FetaCheese." << endl;
			name = "FetaCheese";
		}
		virtual void taste();
};

void FetaCheese::taste()
{
	cout << "It tastes like a " + label + " Feta Cheese." << endl;
}
#endif