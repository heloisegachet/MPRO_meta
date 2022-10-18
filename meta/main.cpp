// C++ project
// Project:  Metaheuristique MPRO 2022/2023
// Author:   Camille RICHER et Héloïse GACHET
// Date:     2022/10/17

#include "heuristique.h"
string filename = "random-10.col";
//string filename = "random-40.col";
//string filename = "random-70.col";
//string filename = "random-100.col";
//string filename = "dsjc125.1.col";
//string filename = "brock200_2.col";
string filepath = "C:/Users/gache/Documents/ENPC/3A/Metaheuristic/git/Instances/"+filename;



int main(int argc, char *argv[])
{
    Graphe g(filepath);
    /*
    Solution sol(g.getNbVertex());
    sol.addVertex(0);
    sol.addVertex(3);
    clog<<"Taille Solution "<<sol.taille();
    clog<<"Admissible "<<sol.isAdmissible(g);
    Solution sol2(g.getNbVertex());
    sol2.addVertex(0);
    sol2.addVertex(1);
    clog<<"Taille Solution "<<sol2.taille();
    clog<<"Admissible "<<sol2.isAdmissible(g);*/
    Solution sol = heuristique_insertion(g);
    cout<<"Taille de la solution obtenue par heuristique par insertion : "<<sol.taille();
}
