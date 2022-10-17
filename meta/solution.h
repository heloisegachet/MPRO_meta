#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <stdexcept>
using namespace std;


class Solution{
    vector<bool> solution; // [1,0,1,0,1,0,1,0]    point tete;
    int lenSol;
public:
    Solution(int n);
    Solution() {};
    vector<bool> getSolution();
    void setSolution(vector<bool> newSol);
    Solution* voisinsSolution();
    void addVertex(int i);
    bool isAdmissible();
};

#endif // SOLUTION_H
