#include "heuristique.h"


Solution heuristique_insertion(Graphe g){
    int n = g.getNbVertex();
    Solution sol = Solution(n);
    for(int i=0;i<n;i++){
        cout<<"i "<<i<<"\n";
        vector<Solution> voisinage = sol.voisinsSolution(g);
        vector<Solution> voisinageAmeliorant;
        for(vector<Solution>::iterator it=voisinage.begin();it!=voisinage.end();it++){
            if(it->taille()>=sol.taille()){
                voisinageAmeliorant.push_back(*it);
            }
        }
        
        if(voisinageAmeliorant.size()==0)
        {
            cout<<"Optimum local"<<endl;
            return sol;
        }
        cout<<"taille du voisin selectionne : "<<voisinageAmeliorant[0].taille()<<"\n";
        sol = Solution(voisinageAmeliorant[0]);
    }
    return sol;
}
