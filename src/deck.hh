#pragma once

#include "cards.hh"
#include <cstddef> // size_t
#include <memory>

namespace coinche
{
  struct coinche_deck_t
  {
    virtual void shuffle() = 0;
    virtual card_t draw() = 0;
    virtual size_t size() = 0;

    virtual ~coinche_deck_t() = default;
  };

  std::unique_ptr<coinche_deck_t> make_coinche_deck();
}
