#pragma once

#include <memory>
#include <optional>

#include "bid.hh"

namespace coinche {
  struct player_t {

    virtual bid_t bid(std::optional<raise_t> min_raise) = 0;
    virtual void on_other_bid(bid_t const & bid) = 0;
    virtual bool coinche(raise_t const & last_raise) = 0;

    virtual ~player_t() = default;
  };

  std::unique_ptr<player_t> make_player();
}
