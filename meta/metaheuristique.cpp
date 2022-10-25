#include <math.h>
#include <algorithm>
#include "solution.h"
#include "heuristique.h"
#include <ctime>
#include <queue>
using namespace std;
#include <chrono>       /* time_t, struct tm, difftime, time, mktime */
using namespace std::chrono;


Solution diversification(Graphe g, Solution oldSol, vector<bool> vertexTable){
    int n = g.getNbVertex();
    Solution sol = Solution(n);
    for(int i=0; i<n;i++){
        if(vertexTable[i]==1 && oldSol.getSolution()[i]==0){
            sol.addVertex(i);
        }
    }
    sol = heuristique_reparation(g, sol);
    return sol;
}


bool elagage(Graphe& g, int tailleSol, vector<bool> &vertexTable){
    bool elague = false;
    vector<int> vertexDegree = g.getVertexDegree();
    for(int i=0;i<vertexDegree.size();i++){
        if(vertexTable[i]>0 && vertexDegree[i] < tailleSol - 1){
            elague = true;
            vertexTable[i] = 0;
            for(int j=0;j<g.getNbVertex();j++){
                g.delEdge(i,j);
                g.delEdge(j,i);
            }
        }
    }
    return elague;
}

void boucleHeuristique(Graphe &g, Solution &bestSol, vector<bool> &vertexTable){
    Solution newSol = Solution(bestSol);
    bool elague;
    do{
        bestSol = Solution(newSol);
        elague = elagage(g, bestSol.taille(), vertexTable);
        newSol = heuristique_insertion_legal_strategy(g);
    }while(elague || newSol.taille() > bestSol.taille());
}

void writeSolutionToFile(int iterations, Solution s, string filename){
    ofstream myfile;
    myfile.open(filename, ios::app);
    myfile << "iterations "<<iterations<<" solution";
    for(int ii=0; ii<s.getNbVertex();ii++){
        if(s.getSolution()[ii])
            myfile<<" "<<ii+1;
    }
    myfile<<" taille "<<s.taille();
    myfile<<"\n";
    myfile.close();
}


void metaheuristique(string filepath, Graphe g, int time_max, int normal_tabou, int long_tabou, int nb_iter_sans_changement, int nb_iter_long_tabou, int nb_iter_diversification ,float percentSuppr, int seuil){

    vector<bool> vertexTable;
    int n = g.getNbVertex();

    vertexTable.assign(n, 1);

    time_t start = time(NULL);
    time_t time_end_loop = time(NULL);
    //initialisation de la première solution avec l'heuristique par insertion
    auto start_heuristique = high_resolution_clock::now();
    Solution sol = heuristique_insertion_legal_strategy(g);
    auto stop_heuristique = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop_heuristique - start_heuristique);
    cout<<"TIME heuristique : "<< duration.count()<<" micro secondes"<<endl;
    cout<<"Taille de la solution obtenue par heuristique par insertion : "<<sol.taille()<<endl;
    printSolution(sol);
    //garder en mémoire la meilleure solution
    Solution bestSol = Solution(sol);
    writeSolutionToFile(0, bestSol, filepath);

    //boucleHeuristique(g, bestSol, vertexTable);
    int iterations = 0;
    int iterationsTabou = 0;
    int iterationsGlobal = 0;
    int previousIterations = 0;
    //liste tabou gérée comme une queue
    int len_tabou = normal_tabou;
    queue<int> tabou_list = queue<int>();
    vector<bool> tabouIndex;
    tabouIndex.assign(n,0);
    while(time_max==-1 || time_end_loop - start < time_max){
        vector<int> vertexAmeliorantNonTabous;
        vector<int> vertexDegradantsNonTabous;
        for(int vertex=1;vertex<sol.getNbVertex();vertex++){
            if(tabouIndex[vertex]==0){
                if(sol.getSolution()[vertex]==1){
                    vertexDegradantsNonTabous.push_back(vertex);
                }
                else{
                    if(sol.isAjoutAdmissible(vertex, g)){
                        vertexAmeliorantNonTabous.push_back(vertex);
                    }
                }
            }
        }
        if(!vertexAmeliorantNonTabous.empty()){
            int random_index = rand()%vertexAmeliorantNonTabous.size();
            sol.addVertex(vertexAmeliorantNonTabous[random_index]);
            tabou_list.push(vertexAmeliorantNonTabous[random_index]);
            tabouIndex[vertexAmeliorantNonTabous[random_index]]=1;
            if(tabou_list.size() > len_tabou){
                int vertexFree = tabou_list.front();
                tabou_list.pop();
                tabouIndex[vertexFree] = 0;
            }
        }
        else{
            if(!vertexDegradantsNonTabous.empty()){
                int random_index = rand()%vertexDegradantsNonTabous.size();
                sol.delVertex(vertexDegradantsNonTabous[random_index]);
                tabou_list.push(vertexDegradantsNonTabous[random_index]);
                tabouIndex[vertexDegradantsNonTabous[random_index]]=1;
                if(tabou_list.size() > len_tabou){
                    int vertexFree = tabou_list.front();
                    tabou_list.pop();
                    tabouIndex[vertexFree] = 0;
                }
            }
            else{
                //cout<<"diversification"<<endl;
                tabouIndex.clear();
                tabou_list = queue<int>();
                sol = diversification(g, sol, vertexTable);
            }
        }
        iterations++;
        iterationsTabou++;
        iterationsGlobal++;
        if (sol.taille()>bestSol.taille()){
            bestSol = Solution(sol);
            //boucleHeuristique(g, bestSol, vertexTable);
            //mettre a jour tabou : ok pk pas
            //taille
            time_t stop = time(NULL);
            time_t duration = stop - start;
            int sommeVertex = 0;
            for(auto elem:vertexTable)
                sommeVertex+=elem;
            //cout<<"Nombre de sommets non elagues "<<sommeVertex<<endl;
            cout<<"Nouvelle meilleure solution trouvee en "<<duration<<" secondes et "<<iterationsGlobal<<" iterations"<<endl;
            cout<<iterations<<" iterations depuis la derniere bestSol"<<endl;
            cout<<"Valeur de la nouvelle solution : "<<bestSol.taille()<<endl;
            //printSolution(bestSol);
            writeSolutionToFile(iterations, bestSol, filepath);
            previousIterations = iterations;
            iterations = 0;
            iterationsTabou = 0;
            if(len_tabou == long_tabou){
                cout<<"Retour de la liste taboue a la normale"<<endl;
                len_tabou = normal_tabou;
            }
        }
        if(iterationsTabou==nb_iter_sans_changement+1){
            //cout<<"diversification"<<endl;
            tabouIndex.assign(g.getNbVertex(),0);
            tabou_list = queue<int>();
            sol = diversification(g, bestSol, vertexTable);
        }
        if(iterationsTabou==nb_iter_sans_changement+1+nb_iter_diversification){
            //cout<<"Allongement de la liste taboue"<<endl;
            len_tabou = long_tabou;
        }
        if(iterationsTabou==nb_iter_sans_changement+nb_iter_long_tabou+1+nb_iter_diversification){
            //cout<<"Retour de la liste taboue a la normale"<<endl;
            len_tabou = normal_tabou;
            iterationsTabou = 0;
        }
        
        /*else{
            //cout<<previousIterations<< " "<<iterations<<" "<<(previousIterations !=0)<<endl;
            if(seuil+g.getNbVertex()<iterationsGlobal && (iterationsSuppr > (iterationsGlobal - iterations))){//(3*previousIterations))){
                iterationsSuppr = 0;
                vector<int> vertexCandidat;
                for(int i=0;i<n;i++){
                    if(bestSol.inSolution(i))
                        vertexCandidat.push_back(i);
                }
                int nbSuppressions = ceil(bestSol.taille()*percentSuppr);
                cout<<"suppression de "<<nbSuppressions<<" sommets de la bestSol"<<endl;
                random_shuffle(vertexCandidat.begin(), vertexCandidat.end());
                sol = Solution(bestSol);
                for(int i=0;i<nbSuppressions;i++){
                    sol.delVertex(vertexCandidat[i]);
                }
            }      
        }*/
        time_end_loop = time(NULL);
    }
    cout<<"Arret de la metaheuristique"<<endl;
}
