#ifndef NYMEALFACTORY_H
#define NYMEALFACTORY_H
#include "AbstractMealFactory.h"

using namespace std;

class NYMealFactory: public AbstractMealFactory
{
	public:
		NYMealFactory()
		{
			cout << "This is a New York restaurant!" << endl;
		}
		virtual Cheese* makeCheese(string name);
		virtual Fruit* makeFruit(string name);
};

Cheese* NYMealFactory::makeCheese(string name)
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
	cheese->addLabel("New York");
	return cheese;
}

Fruit* NYMealFactory::makeFruit(string name)
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
	fruit->addLabel("New York");
	return fruit;
}
#endif