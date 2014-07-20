#include <utility>

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
};

enum Couleur
{
	Coeur
		, Pique
		, Carreaux
		, Trefle
};

typedef std::pair<Figure, Couleur> Carte;
