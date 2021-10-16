#include<memory>
#include <cstdlib> // size_t

#include "cards.hh"

namespace coinche 
{
struct hand_t
{
  virtual void add(carte_t const & card) = 0;
  virtual void play(carte_t const & card) = 0; 
  virtual size_t size() const = 0;

  virtual ~hand_t() = default;
};

std::unique_ptr<hand_t> GetCoincheHand();

}
