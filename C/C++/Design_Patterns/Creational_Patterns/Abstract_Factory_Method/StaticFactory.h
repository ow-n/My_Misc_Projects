#ifndef STATICFACTORY_H
#define STATICFACTORY_H
#include "CheddarCheese.h"
#include "FetaCheese.h"
#include "SwissCheese.h"

using namespace std;

class StaticFactory
{
	public:
		static Cheese* makeCheese(string name)
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
			cheese->addLabel("static");
			return cheese;
		}
};
#endif