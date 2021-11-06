#pragma once

#include <memory>
#include <optional>

#include "bid.hh"

namespace coinche {
  struct player_t {

    virtual bid_t bid(raise_t min_raise) = 0;
    virtual bool coinche(raise_t const & last_raise) = 0;
    virtual bool surcoinche() = 0;

    virtual void on_bid(bid_t const & bid) = 0;
    virtual void on_coinche(raise_t const &, int player_idx) = 0;
    virtual void on_surcoinche(int player_idx) = 0;

    virtual ~player_t() = default;
  };

  std::unique_ptr<player_t> make_player();
}
