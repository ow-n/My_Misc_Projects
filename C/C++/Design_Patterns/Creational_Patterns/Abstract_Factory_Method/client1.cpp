#include "CheddarCheese.h"
#include "FetaCheese.h"
#include "SwissCheese.h"

using namespace std;

int main()
{
	Cheese *cheese[3];
	cheese[0] = new CheddarCheese();
	cheese[1] = new FetaCheese();
	cheese[2] = new SwissCheese();

	cheese[0]->addLabel("$1");
	cheese[0]->taste();

	cheese[1]->addLabel("$1");
	cheese[1]->taste();

	cheese[2]->addLabel("$1");
	cheese[2]->taste();
	return 0;
}