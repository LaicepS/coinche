#include "cards.h"
#include <cstddef> // size_t

namespace coinche
{
struct Deck
{
	virtual void shuffle() = 0;
	virtual void cut() = 0;
	virtual Carte draw() = 0;
	virtual size_t size() = 0;

	virtual ~Deck() {}
};

Deck* NewDeckCoinche();
 }
