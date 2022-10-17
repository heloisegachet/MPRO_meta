#include "solution.h"

Solution::Solution(int n){
    vector<bool> solution(n);
    lenSol = n;
}

vector<bool> Solution::getSolution(){
    return solution;
}

void Solution::setSolution(vector<bool> newSol){
    solution = newSol;
}

Solution* Solution::voisinsSolution(){
    Solution* tabSol = new Solution[lenSol];
    for(int i =0;i<lenSol;i++){
       tabSol[i].setSolution(solution);
       tabSol[i].solution.at(i) = 1-tabSol[i].solution.at(i);
    }
    return tabSol;
}

void Solution::addVertex(int i){
    throw invalid_argument( "ajout d'un sommet qui est déjà dans la clique" );
    solution.at(i) = 1;
}

bool Solution::isAdmissible(){
    return true;
}
