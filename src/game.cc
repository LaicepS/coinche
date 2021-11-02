#include <iostream>
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
      int current_player = 0;
      raise_t min_raise = R80_COEUR;
      bool coinche = false;

      while (!coinche && passes_in_a_row < 4 && min_raise < R250_COEUR)
      {
        auto bid = _players[current_player]->bid(min_raise);

        notify_other_players(bid, current_player);

        auto next_player = get_next_player(current_player);
        std::visit(overloaded{[&](pass_t const&) { passes_in_a_row++; },
                              [&](raise_t const& raise) {
                                min_raise = lowest_higher_raise(raise);
                                passes_in_a_row = 0;

                                coinche = _players[next_player]->coinche(raise);

                                if (coinche)
                                {
                                  notify_coinche(raise, next_player);
                                  return;
                                }

                                coinche =
                                  _players[teammate(next_player)]->coinche(
                                    raise);

                                if (coinche)
                                  notify_coinche(raise, teammate(next_player));
                              }},
                   bid);

        current_player = next_player;
      }

      if (coinche)
      {
        _players[get_next_player(current_player)]->surcoinche();
        _players[teammate(get_next_player(current_player))]->surcoinche();
      }
    }

    void notify_other_players(bid_t const& bid, int player_idx)
    {
      for (int i = 0; i < 4; i++)
        if (i != player_idx)
          _players[i]->on_other_bid(bid);
    }

    void notify_coinche(raise_t const& raise, int player_idx)
    {
      for (int i = 0; i < 4; i++)
        if (i != player_idx)
          _players[i]->on_coinche(raise, player_idx);
    }

    raise_t lowest_higher_raise(raise_t raise)
    {
      return raise_t((raise / 4 + 1) * 4);
    }

    int get_next_player(int player_idx)
    {
      return (player_idx + 1) % 4;
    }

    int teammate(int player_idx)
    {
      switch (player_idx)
      {
      case 0:
        return 2;
      case 1:
        return 3;
      case 2:
        return 0;
      case 3:
        return 1;
      default:
        abort();
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
