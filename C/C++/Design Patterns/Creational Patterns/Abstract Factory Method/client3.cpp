#include "CACheeseFactory.h"
#include "NYCheeseFactory.h"

using namespace std;

int main()
{
	CACheeseFactory factory1;
	NYCheeseFactory factory2;
	Cheese *cheese[3];
	cheese[0] = factory1.makeCheese("cheddar");
	cheese[1] = factory1.makeCheese("feta");
	cheese[2] = factory2.makeCheese("swiss");

	cheese[0]->taste();
	cheese[1]->taste();
	cheese[2]->taste();
	return 0;
}