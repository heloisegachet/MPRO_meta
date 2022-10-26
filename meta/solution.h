#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <stdexcept>
#include "graphe.h"
#include <iterator>
#include <numeric>      // std::iota
#include <algorithm>    // std::sort, std::stable_sort
using namespace std;


class Solution{
    vector<bool> solution; // [1,0,1,0,1,0,1,0]    point tete;
    int lenSol;
public:
    Solution(int n);
    Solution(Solution const &newSol);
    Solution() {};
    vector<bool> getSolution(){return solution;};
    int getNbVertex(){return lenSol;};
    void addVertex(int i);
    void delVertex(int i);
    int taille();
    bool isAjoutAdmissible(int v, Graphe graphe);
    int isSwapAdmissible(int v, Graphe graphe);
};

void printSolution(Solution s);

#endif // SOLUTION_H
