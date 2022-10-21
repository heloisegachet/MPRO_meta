#include "heuristique.h"


Solution heuristique_insertion_legal_strategy(Graphe g){
    int n = g.getNbVertex();
    Solution sol = Solution(n);
    for(int i=0;i<n;i++){
        vector<Solution> voisinageAmeliorant = sol.voisinsAjout(g, true);
        vector<Solution> voisinage_echange = sol.voisinsEchange(g, true);
        for(vector<Solution>::iterator it=voisinage_echange.begin();it!=voisinage_echange.end();it++){
            voisinageAmeliorant.push_back(*it);
        }    
        if(voisinageAmeliorant.size()==0)
        {
            cout<<"Optimum local"<<endl;
            return sol;
        }
        //cout<<"taille du voisin selectionne : "<<voisinageAmeliorant[0].taille()<<"\n";
        sol = Solution(voisinageAmeliorant[0]);
    }
    return sol;
}


Graphe getSousGraphe(Graphe g, Solution s){
    int n = s.getNbVertex();
    Graphe sousGraphe(n);
    for(int i = 0; i<n;i++){
        for(int j = 0; j<n;j++){
            int edge = g.getEdge()[i][j];
            if(edge==1 && s.getSolution()[i] == 1 && s.getSolution()[j]==1){
                sousGraphe.addEdge(i,j);
                sousGraphe.addEdge(j,i);
            }
        }
    }
}

Solution heuristique_reparation(Graphe g, Solution s){
    Graphe sousGraphe = getSousGraphe(g, s);
    Solution sol = heuristique_insertion_legal_strategy(sousGraphe);
    return sol;
}


/*
Solution heuristique_insertion_increasing_edges(Graphe g){
    int n = g.getNbVertex();
    Solution sol = Solution(n);
    return sol;
}*/
