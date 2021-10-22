#include "player.hh"

namespace coinche {
  struct player : player_t
  {
    bid_t bid() override
    {
      return {};
    }
  };

  std::unique_ptr<player_t> make_player()
  {
    return std::make_unique<player>();
  }
}
