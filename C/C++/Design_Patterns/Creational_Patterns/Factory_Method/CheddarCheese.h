#ifndef CHEDDARCHEESE_H
#define CHEDDARCHEESE_H
#include "Cheese.h"

using namespace std;

class CheddarCheese: public Cheese
{
	public:
		CheddarCheese()
		{
			cout << "Create CheddarCheese." << endl;
			name = "CheddarCheese";
		}
		virtual void taste();
};

void CheddarCheese::taste()
{
	cout << "It tastes like a " + label + " Cheddar Cheese." << endl;
}
#endif