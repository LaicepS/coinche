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
      std::optional<raise_t> last_raise;

      while (passes_in_a_row < 4)
      {
        auto bid = _players[player_idx]->bid(lowest_higher_raise(last_raise));

        notify_other_players(bid, player_idx);

        std::visit(overloaded{[&](pass_t const&) { passes_in_a_row++; },
                              [&](raise_t const& raise) {
                                last_raise = raise;
                                passes_in_a_row = 0;
                              }},
                   bid);

        player_idx = (player_idx + 1) % 4;
      }
    }

    void notify_other_players(bid_t const& bid, int player_idx)
    {
      for (int i = 0; i < 4; i++)
        if (i != player_idx)
          _players[i]->on_other_bid(bid);
    }

    std::optional<raise_t> lowest_higher_raise(std::optional<raise_t> raise)
    {
      if (!raise)
        return std::optional<raise_t>{};

      return raise_t((*raise / 4 + 1) * 4);
    }

    player_t* _players[4];
  };

  std::unique_ptr<coinche_game_t>
  make_coinche_game(player_t* p0, player_t* p1, player_t* p2, player_t* p3)
  {
    return std::make_unique<coinche_game>(p0, p1, p2, p3);
  }
} // namespace coinche
