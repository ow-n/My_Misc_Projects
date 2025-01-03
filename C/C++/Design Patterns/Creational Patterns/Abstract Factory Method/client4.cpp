#include "FactoryProducer.h"

using namespace std;

int main()
{
	AbstractMealFactory* factory[2];
	factory[0] = FactoryProducer::getFactory("ca");
	factory[1] = FactoryProducer::getFactory("ny");
	
	Cheese* cheese[2];
	Fruit* fruit[2];
	cheese[0] = factory[0]->makeCheese("swiss");
	fruit[0] = factory[0]->makeFruit("banana");
	cheese[1] = factory[1]->makeCheese("cheddar");
	fruit[1] = factory[1]->makeFruit("apple");

	cheese[0]->taste();
	fruit[0]->taste();
	cheese[1]->taste();
	fruit[1]->taste();
	return 0;
}