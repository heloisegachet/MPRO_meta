#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H


#include "solution.h"

Solution heuristique_insertion_legal_strategy(Graphe g);
Solution heuristique_reparation(Graphe g, Solution s);

//Solution heuristique_insertion_increasing_edges(Graphe g);

#endif // HEURISTIQUE_H
