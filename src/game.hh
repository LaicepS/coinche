#pragma once

#include <memory>

#include "player.hh"

namespace coinche 
{

  struct coinche_game_t {
    virtual void run_turn() = 0;

    virtual ~coinche_game_t() = default;
  };

  std::unique_ptr<coinche_game_t> 
    make_coinche_game(
      player_t*, 
      player_t*, 
      player_t*, 
      player_t*);
}
