#include "StaticFactory.h"

using namespace std;

int main()
{
	Cheese *cheese[3];
	cheese[0] = StaticFactory::makeCheese("cheddar");
	cheese[1] = StaticFactory::makeCheese("feta");
	cheese[2] = StaticFactory::makeCheese("swiss");

	cheese[0]->taste();
	cheese[1]->taste();
	cheese[2]->taste();
	return 0;
}