#pragma once

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

	struct Carte
	{
	  Figure figure;
	  Couleur color;
	};

	std::string toString(Figure);
	std::string toString(Couleur);
}
