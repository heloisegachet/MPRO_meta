#include "heuristique.h"


Solution heuristique_insertion(Graphe g){
    int n = g.getNbVertex();
    Solution sol = Solution(n);
    for(int i=0;i<n;i++){
        cout<<"i "<<i<<"\n";
        vector<Solution> voisinage = sol.voisinsSolution(g);
        cout<<"taille du voisin selectionne : "<<voisinage[0].taille()<<"\n";
        sol = Solution(voisinage[0]);
        if(voisinage.size()==0)
        {
            cout<<"Optimum local";
            return sol;
        }
    }
    return sol;
}
