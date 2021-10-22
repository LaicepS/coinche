#include <memory>

#include "game.hh"
#include "variant.hh"

namespace coinche
{
  struct coinche_game : coinche_game_t
  {
    coinche_game(player_t* p0, player_t* p1, player_t* p2, player_t* p3)
    {
      _players[0] = p0;
      _players[1] = p1;
      _players[2] = p2;
      _players[3] = p3;
    }

    void run_turn() override
    {
      int passes_in_a_row = 0;
      int player_idx = 0;
      while (passes_in_a_row < 4)
      {
        auto bid = _players[player_idx++ % 4]->bid();
        std::visit(overloaded{[&](pass_t const& bid) { passes_in_a_row++; },
                              [&](raise_t const& bid) { passes_in_a_row = 0; }},
                   bid);
      }
    }

    player_t* _players[4];
  };

  std::unique_ptr<coinche_game_t>
  make_coinche_game(player_t* p0, player_t* p1, player_t* p2, player_t* p3)
  {
    return std::make_unique<coinche_game>(p0, p1, p2, p3);
  }
} // namespace coinche
