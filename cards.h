#include <utility>
#include <string>

namespace coinche
{
	enum Figure
	{
		As 
			, Sept
			, Huit 
			, Neuf
			, Dix
			, Valet
			, Dame
			, Roi
			, LastFigure
	};

	enum Couleur
	{
		Coeur
			, Pique
			, Carreaux
			, Trefle
			, LastCouleur
	};

	enum
	{
		FIGURE = 0
			, COULEUR = 1
	};

	typedef std::pair<Figure, Couleur> Carte;

	std::string toString(Figure);
	std::string toString(Couleur);
}
