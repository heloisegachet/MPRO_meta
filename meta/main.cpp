// C++ project
// Project:  Metaheuristique MPRO 2022/2023
// Author:   Camille RICHER et Héloïse GACHET
// Date:     2022/10/17

#include "graphe.h"

string filename = "random-10.col";
//string filename = "random-40.col";
//string filename = "random-70.col";
//string filename = "random-100.col";
//string filename = "dsjc125.1.col";
//string filename = "brock200_2.col";
string filepath = "C:/Users/gache/Documents/ENPC/3A/Metaheuristic/Instances/"+filename;



int main(int argc, char *argv[])
{
    Graphe g(filepath);
}
