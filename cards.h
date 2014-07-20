#include <utility>

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
}
