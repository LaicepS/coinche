#include "cards.h"
#include <cstddef> // size_t
#include <memory>

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

std::unique_ptr<Deck> NewDeckCoinche();
 }
