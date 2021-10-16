#include <stdexcept>

#include "cards.hh"

namespace coinche
{
  std::string toString(Figure figure)
  {
    switch (figure)
    {
    case As:
      return "As";
    case Sept:
      return "Sept";
    case Huit:
      return "Huit";
    case Neuf:
      return "Neuf";
    case Dix:
      return "Dix";
    case Valet:
      return "Valet";
    case Dame:
      return "Dame";
    case Roi:
      return "Roi";
    default:
      throw std::runtime_error("Unknown figure");
    }
  }

  std::string toString(Couleur couleur)
  {
    switch (couleur)
    {
    case Coeur:
      return "Coeur";
    case Pique:
      return "Pique";
    case Trefle:
      return "Trefle";
    case Carreaux:
      return "Carreaux";
    default:
      throw std::runtime_error("Unknown couleur");
    }
  }

  std::string toString(carte_t c)
  {
    return toString(c.figure) + " de " + toString(c.color);
  }
}
