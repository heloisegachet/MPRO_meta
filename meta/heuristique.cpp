#include "solution.h"
#include <utility>

Solution heuristique_insertion_legal_strategy(Graphe g){
    int n = g.getNbVertex();
    Solution sol = Solution(n);
    vector<Solution> tabSol;
    //Trier les sommets par degrés décroissants
    vector<int> degree_table = g.getVertexDegree();
    vector<pair<int, int>> Vertices(n);
    for(int i = 0; i<n;i++){
        Vertices[i] = pair(i, degree_table[i]);
    }
    stable_sort( Vertices.begin(),Vertices.end(), [&](pair<int,int> p1,pair<int,int> p2){return p1.second>p2.second;} );
    int tailleSol = 0;
    for(int i=0;i<n;i++){
        if(Vertices[i].second>=tailleSol && sol.isAjoutAdmissible(Vertices[i].first, g)){
            sol.addVertex(Vertices[i].first);
            tailleSol++;
        }
    }
    return sol;
}

Graphe getSousGraphe(Graphe g, Solution s){
    int n = s.getNbVertex();
    Graphe sousGraphe(n);
    for(int i = 0; i<n;i++){
        for(int j = 0; j<n;j++){
            int edge = g.getEdge(i,j);
            if(i!=j && edge==1 && s.getSolution()[i]==1 && s.getSolution()[j]==1){
                sousGraphe.addEdge(i,j);
                sousGraphe.addEdge(j,i);
            }
        }
    }
    return sousGraphe;
}

Solution heuristique_reparation(Graphe g, Solution s){
    Graphe sousGraphe = getSousGraphe(g, s);
    int n = sousGraphe.getNbVertex();
    Solution sol = heuristique_insertion_legal_strategy(sousGraphe);
    return sol;
}