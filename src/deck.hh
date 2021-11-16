#pragma once

#include "cards.hh"
#include <cstddef> // size_t
#include <memory>

namespace coinche
{
  struct deck_t
  {
    virtual std::array<card_t, 8> draw() = 0;

    virtual ~deck_t() = default;
  };

  std::unique_ptr<deck_t> make_coinche_deck();
}
