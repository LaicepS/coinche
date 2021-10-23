#pragma once

#include <variant>

#include "cards.hh"

namespace coinche {
  struct pass_t{};

  struct raise_t{
    int value;
    Couleur couleur;
  };

  extern raise_t all_raises[44];

  using bid_t = std::variant<pass_t, raise_t>;
}
