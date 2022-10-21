#include "metaheuristique.h"


int getVertexChange(Solution sol1, Solution sol2){
    for(int i=0;i<sol1.getNbVertex(); i++){
        if(sol1.getSolution()[i] != sol2.getSolution()[i])
            return i;
    }
    printSolution(sol1);
    printSolution(sol2);
    return -1;
}

bool isTabou(Solution solCourante, Solution s, queue<int> tabouList){
    if(tabouList.empty())
        return false;
    bool isTabou = false;
    int vertexChanged = getVertexChange(solCourante, s);
    int lenTabou = tabouList.size();
    for(int i =0;i<lenTabou;i++){
        int vertex = tabouList.front();
        tabouList.pop();
        if(vertex == vertexChanged){
            isTabou = true;
        }
        tabouList.push(vertex);
    }
    return isTabou;
}

Solution diversification(Graphe g, Solution oldSol){
    Solution sol = Solution(oldSol.getNbVertex());
    for(int i=0; i<sol.getNbVertex();i++){
        if(oldSol.getSolution()[i]==0){
            sol.addVertex(i);
        }
    }
    sol = heuristique_reparation(g, sol);
    return sol;
}

void metaheuristique(Graphe g, int len_tabou_, int nb_iter_sans_changement_){
    time_t start = time(NULL);
    //initialisation de la première solution avec l'heuristique par insertion
    auto start_heuristique = high_resolution_clock::now();
    Solution sol = heuristique_insertion_legal_strategy(g);
    auto stop_heuristique = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop_heuristique - start_heuristique);
    cout<<"TIME heuristique : "<< duration.count()<<" micro secondes"<<endl;
    cout<<"Taille de la solution obtenue par heuristique par insertion : "<<sol.taille()<<endl;
    for(int i=0;i<sol.getNbVertex();i++){
        if(sol.getSolution()[i]==1)
            cout<<i<<" ";
    }
    cout<<endl;
    //garder en mémoire la meilleure solution
    Solution bestSol = Solution(sol);
    int iterations = 0;
    //liste tabou gérée comme une queue
    queue<int> tabou_list = queue<int>();
    int len_tabou = len_tabou_;
    int nb_iter_sans_changement = nb_iter_sans_changement_;
    while(true){
        vector<int> liste_choix_indice;
        vector<Solution> voisinsAjout = sol.voisinsAjout(g, true);
        vector<Solution> voisinsSuppr = sol.voisinsSuppr(g);
        for(int i=0;i<voisinsAjout.size();i++){
            if(!isTabou(sol, voisinsAjout[i], tabou_list)){
                liste_choix_indice.push_back(i);
            }
        }
        if(!liste_choix_indice.empty()){
            int random_index = rand()%liste_choix_indice.size();
            Solution nextSol = Solution(voisinsAjout[liste_choix_indice[random_index]]);
            tabou_list.push(getVertexChange(nextSol, sol));
            if(tabou_list.size() > len_tabou){
                tabou_list.pop();
            }
            sol = Solution(nextSol);
        }
        else{
            liste_choix_indice.clear();
            for(int i=0;i<voisinsSuppr.size();i++){
                if(!isTabou(sol, voisinsSuppr[i], tabou_list)){
                    liste_choix_indice.push_back(i);
                }
            }
            if(!liste_choix_indice.empty()){
                cout<<"no non tabou neighbor"<<endl;
                int random_index = rand()%liste_choix_indice.size();
                Solution nextSol = Solution(voisinsSuppr[liste_choix_indice[random_index]]);
                tabou_list.push(getVertexChange(nextSol, sol));
                if(tabou_list.size() > len_tabou){
                    tabou_list.pop();
                }
                sol = Solution(nextSol);
            }
            else{
                sol = diversification(g, sol);
            }
        }
        iterations++;
        if (sol.taille()>bestSol.taille()){
            bestSol = Solution(sol);
            //taille
            time_t stop = time(NULL);
            time_t duration = stop - start;
            iterations = 0;
            cout<<"Nouvelle meilleure solution trouvee en "<<duration<<" secondes et "<<iterations<<" iterations"<<endl;
            cout<<"Valeur de la nouvelle solution : "<<bestSol.taille()<<endl;
            cout<<"Solution : ";
            printSolution(bestSol);
            cout<<endl;
            start = time(NULL);
        }
       


    }

}
