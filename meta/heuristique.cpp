#include "heuristique.h"


Solution heuristique_insertion_legal_strategy(Graphe g){
    int n = g.getNbVertex();
    Solution sol = Solution(n);
    for(int i=0;i<n;i++){
        vector<Solution> voisinage_echange = sol.voisinsEchange(g, true);
        vector<Solution> voisinageAmeliorant = sol.voisinsAjout(g, true);
        for(vector<Solution>::iterator it=voisinage_echange.begin();it!=voisinage_echange.end();it++){
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

/*
Solution heuristique_insertion_increasing_edges(Graphe g){
    int n = g.getNbVertex();
    Solution sol = Solution(n);
    return sol;
}*/
