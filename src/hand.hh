#include <cstdlib> // size_t

#include "cards.hh"

template<class Card>
struct IHand
{
  virtual void add(Card const & card) = 0;
  virtual void play(Card const & card) = 0; 
  virtual size_t size() const = 0;

  virtual ~IHand(){}
};

IHand<coinche::Carte> * GetCoincheHand();

