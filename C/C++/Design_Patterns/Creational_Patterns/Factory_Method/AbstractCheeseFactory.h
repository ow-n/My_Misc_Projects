#ifndef ABSTRACTCHEESEFACTORY_H
#define ABSTRACTCHEESEFACTORY_H
#include "CheddarCheese.h"
#include "FetaCheese.h"
#include "SwissCheese.h"

using namespace std;

class AbstractCheeseFactory {
	public:
		AbstractCheeseFactory() 		{
			cout << "Welcome to the cheese factory!" << endl;
		}
		virtual Cheese* makeCheese(string name) = 0;
};
#endif