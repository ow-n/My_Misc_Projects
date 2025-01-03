#ifndef CAMEALFACTORY_H
#define CAMEALFACTORY_H
#include "AbstractMealFactory.h"

using namespace std;

class CAMealFactory: public AbstractMealFactory
{
	public:
		CAMealFactory()
		{
			cout << "This is a California restaurant!" << endl;
		}
		virtual Cheese* makeCheese(string name);
		virtual Fruit* makeFruit(string name);
};

Cheese* CAMealFactory::makeCheese(string name)
{
	Cheese* cheese;
	if(name == "cheddar") {				
		cheese = new CheddarCheese();
	} else if(name == "feta") {
		cheese = new FetaCheese();
	} else if(name == "swiss") {
		cheese = new SwissCheese();
	} else {
		cout << "We do not have this kind of cheese" << endl;
		cheese = NULL;
	}
	cheese->addLabel("California");
	return cheese;
}

Fruit* CAMealFactory::makeFruit(string name)
{
	Fruit* fruit;
	if(name == "apple") {				
		fruit = new Apple();
	} else if(name == "banana") {
		fruit = new Banana();
	} else {
		cout << "We do not have this kind of fruit." << endl;
		fruit = NULL;
	}
	fruit->addLabel("California");
	return fruit;
}
#endif