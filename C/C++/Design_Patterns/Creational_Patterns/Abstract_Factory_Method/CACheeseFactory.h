#ifndef CACHEESEFACTORY_H
#define CACHEESEFACTORY_H
#include "AbstractCheeseFactory.h"

using namespace std;

class CACheeseFactory: public AbstractCheeseFactory
{
	public:
		CACheeseFactory()
		{
			cout << "This is a California cheese factory!" << endl;
		}
		virtual Cheese* makeCheese(string name);
};

Cheese* CACheeseFactory::makeCheese(string name)
{
	Cheese* cheese;
	if(name == "cheddar") {				
		cheese = new CheddarCheese();
	} else if(name == "feta") {
		cheese = new FetaCheese();
	} else if(name == "swiss") {
		cheese = new SwissCheese();
	} else {
		cout << "We do not have this kind of cheese." << endl;
		cheese = NULL;
	}
	cheese->addLabel("California");
	return cheese;
}
#endif