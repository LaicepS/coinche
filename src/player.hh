#pragma once

#include <memory>

#include "bid.hh"

namespace coinche {
  struct player_t {

    virtual bid_t bid() = 0;

    virtual ~player_t() = default;
  };

  std::unique_ptr<player_t> make_player();
}
