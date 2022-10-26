#include "solution.h"
#include <utility>

Solution heuristique_insertion_legal_strategy(Graphe g){
    int n = g.getNbVertex();
    Solution sol = Solution(n); //create an empty solution of size n
    //Sort the vertices by descending order
    vector<int> degree_table = g.getVertexDegree();
    vector<pair<int, int>> Vertices(n);
    for(int i = 0; i<n;i++){
        Vertices[i] = pair(i, degree_table[i]); //in the vector, we keep pairs of (vertex index, vertex degree)
    }
    stable_sort( Vertices.begin(),Vertices.end(), [&](pair<int,int> p1,pair<int,int> p2){return p1.second>p2.second;} ); //sorting by degree

    //add the vertices if they ensure the admissibility
    int tailleSol = 0;
    for(int i=0;i<n;i++){
        // if the degree of the vertex is strictly smaller than the size of the solution currently built, 
        // there is no need in checking its admissibility
        // Add the vertex only if the solution with the addition is still a clique
        if(Vertices[i].second>=tailleSol && sol.isAjoutAdmissible(Vertices[i].first, g)){
            sol.addVertex(Vertices[i].first);
            tailleSol++;
        }
    }
    return sol;
}

Graphe getSousGraphe(Graphe g, Solution s){
    // build the subgraph without the vertices from the solution
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
    // build the subgraph with only the vertices that are not in the solution s
    Graphe sousGraphe = getSousGraphe(g, s);
    int n = sousGraphe.getNbVertex();
    // apply the heuristique in the subgraph
    Solution sol = heuristique_insertion_legal_strategy(sousGraphe);
    return sol;
}