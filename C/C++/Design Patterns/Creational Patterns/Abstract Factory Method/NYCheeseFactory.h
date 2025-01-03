#ifndef NYCHEESEFACTORY_H
#define NYCHEESEFACTORY_H
#include "AbstractCheeseFactory.h"

using namespace std;

class NYCheeseFactory: public AbstractCheeseFactory
{
	public:
		NYCheeseFactory()
		{
			cout << "This is a New York cheese factory!" << endl;
		}
		virtual Cheese* makeCheese(string name);
};

Cheese* NYCheeseFactory::makeCheese(string name)
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
	cheese->addLabel("New York");
	return cheese;
}
#endif