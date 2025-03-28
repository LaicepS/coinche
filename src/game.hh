#pragma once

#include <memory>

#include "deck.hh"
#include "player.hh"

namespace coinche
{

  struct coinche_game_t
  {
    /* Turn = deal + bid + play.  */
    virtual void run_turn() = 0;

    virtual ~coinche_game_t() = default;
  };

  std::unique_ptr<coinche_game_t>
    make_coinche_game(
	deck_t& deck,
      player_t*,
      player_t*,
      player_t*,
      player_t*);
}
