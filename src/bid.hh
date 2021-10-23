#pragma once

#include <variant>

#include "cards.hh"

namespace coinche {
  struct pass_t{};

  struct raise_t{
    int value;
    Couleur couleur;
  };

  enum raise_idx {
    R80_COEUR,
    R80_PIQUE,
    R80_CARREAUX,
    R80_TREFLE,
    R90_COEUR,
    R90_PIQUE,
    R90_CARREAUX,
    R90_TREFLE,
    R100_COEUR,
    R100_PIQUE,
    R100_CARREAUX,
    R100_TREFLE,
    R110_COEUR,
    R110_PIQUE,
    R110_CARREAUX,
    R110_TREFLE,
    R120_COEUR,
    R120_PIQUE,
    R120_CARREAUX,
    R120_TREFLE,
    R130_COEUR,
    R130_PIQUE,
    R130_CARREAUX,
    R130_TREFLE,
    R140_COEUR,
    R140_PIQUE,
    R140_CARREAUX,
    R140_TREFLE,
    R150_COEUR,
    R150_PIQUE,
    R150_CARREAUX,
    R150_TREFLE,
    R160_COEUR,
    R160_PIQUE,
    R160_CARREAUX,
    R160_TREFLE,
    R170_COEUR,
    R170_PIQUE,
    R170_CARREAUX,
    R170_TREFLE,
    R180_COEUR,
    R180_PIQUE,
    R180_CARREAUX,
    R180_TREFLE,
    R250_COEUR,
    R250_PIQUE,
    R250_CARREAUX,
    R250_TREFLE,
  };

  extern raise_t all_raises[48];

  using bid_t = std::variant<pass_t, raise_t>;
}
