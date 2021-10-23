#pragma once

#include <memory>
#include <optional>

#include "bid.hh"

namespace coinche {
  struct player_t {

    virtual bid_t bid(std::optional<raise_t> min_raise) = 0;

    virtual ~player_t() = default;
  };

  std::unique_ptr<player_t> make_player();
}
