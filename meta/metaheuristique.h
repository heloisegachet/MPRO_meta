#include "solution.h"
#include "heuristique.h"
#include <ctime>
#include <queue>
using namespace std;
#include <chrono>       /* time_t, struct tm, difftime, time, mktime */
using namespace std::chrono;

void metaheuristique(Graphe g, int len_tabou, int nb_iter_sans_changement);