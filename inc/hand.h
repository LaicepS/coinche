#include <cstdlib> // size_t
#include "cards.h"

template<class Card>
struct IHand
{
	virtual void add(Card card) = 0;
	virtual Card play() = 0; 
	virtual size_t size() const = 0;

	virtual ~IHand(){}
};

IHand<coinche::Carte> * GetCoincheHand();

