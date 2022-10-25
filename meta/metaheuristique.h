#include <math.h>
#include <algorithm>
#include "solution.h"
#include "heuristique.h"
#include <ctime>
#include <queue>
using namespace std;
#include <chrono>       /* time_t, struct tm, difftime, time, mktime */
using namespace std::chrono;

void metaheuristique(string filepath, Graphe g, int time_max, int normal_tabou, int long_tabou, int nb_iter_sans_changement, 
                    int nb_iter_long_tabou, int nb_iter_diversification,float percentSuppr, int seuil);

void metaheuristique_bis(string filepath, Graphe g, int time_max, int normal_tabou, int long_tabou, int nb_iter_sans_changement, 
                    int nb_iter_long_tabou, int nb_iter_diversification);