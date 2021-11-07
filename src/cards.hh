#pragma once

#include <string>
#include <tuple>

namespace coinche
{
enum Figure { As, Sept, Huit, Neuf, Dix, Valet, Dame, Roi, LastFigure };

enum Couleur { Coeur, Pique, Carreaux, Trefle, LastCouleur };

enum { FIGURE = 0, COULEUR = 1 };

struct card_t {
  Figure figure;
  Couleur color;
};

inline bool operator==(card_t const & lhs, card_t const & rhs) {
  return std::tie(lhs.figure, lhs.color) == std::tie(rhs.figure, rhs.color);
}

std::string toString(Figure);
std::string toString(Couleur);
std::string toString(card_t);
}
