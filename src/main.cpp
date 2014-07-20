#include "../inc/deck.h"
#include <memory>

int main()
{
	std::unique_ptr<IDeck<coinche::Carte>> deck(NewDeckCoinche());
	return 0;
}
