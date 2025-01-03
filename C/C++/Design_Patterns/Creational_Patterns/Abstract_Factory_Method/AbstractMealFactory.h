#ifndef ABSTRACTMEALFACTORY_H
#define ABSTRACTMEALFACTORY_H
#include "CheddarCheese.h"
#include "FetaCheese.h"
#include "SwissCheese.h"
#include "Apple.h"
#include "Banana.h"

using namespace std;

class AbstractMealFactory
{
	public:
		AbstractMealFactory()
		{
			cout << "Welcome to a restaurant!" << endl;
		}
		virtual Cheese* makeCheese(string name) = 0;
		virtual Fruit* makeFruit(string name) = 0;
};
#endif