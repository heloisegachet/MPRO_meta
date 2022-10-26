#include <math.h>
#include <random>
#include <algorithm>
#include "solution.h"
#include "heuristique.h"
#include <ctime>
#include <queue>
using namespace std;
#include <chrono>       /* time_t, struct tm, difftime, time, mktime */
using namespace std::chrono;

template <class D, class W, class URBG>
void weighted_shuffle
    ( D first, D last
    , W first_weight, W last_weight
    , URBG&& gen)
{
    while (first != last and first_weight != last_weight)
    {
        std::discrete_distribution dd(first_weight, last_weight);
        auto i = dd(gen);
        if ( i )
        {
            std::iter_swap(first, std::next(first, i));
            std::iter_swap(first_weight, std::next(first_weight, i));
        }
        ++first;
        ++first_weight;
    }
}

Solution restart_from_another_clique(Graphe g, vector<bool> vertexTable, vector<int> frequency){
    // generate a solution by successively adding the vertices that are rare (not often taken in the best solutions found so far)
    int n = g.getNbVertex();
    Solution sol = Solution(n);
    vector<int> vertex_shuffle;
    for(int i = 0; i<n;i++){
        vertex_shuffle.push_back(i);
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());

    vector<float> weights;
    for(auto elem :frequency)
        // weight : invert of the frequency
        weights.push_back(1/(elem+1));
    weighted_shuffle(vertex_shuffle.begin(), vertex_shuffle.end(), weights.begin(), weights.end(), gen);
    for(int i=0;i<n;i++){
        if(vertexTable[vertex_shuffle[i]]==1 && sol.isAjoutAdmissible(vertex_shuffle[i], g)){
            sol.addVertex(vertex_shuffle[i]);
        }
    }
    return sol;
}

Solution diversification(Graphe g, Solution oldSol){
    int n = g.getNbVertex();
    Solution sol = Solution(n);
    for(int i=0; i<n;i++){
        if(oldSol.getSolution()[i]==0){
            sol.addVertex(i);
        }
    }
    sol = heuristique_reparation(g, sol);
    return sol;
}

void writeSolutionToFile(int iterations, int time, Solution s, string filename){
    //write solution on a file with time, iterations, solution and its value
    ofstream myfile;
    myfile.open(filename, ios::app);
    myfile << "iterations "<<iterations<<" time "<<time<<" solution";
    for(int ii=0; ii<s.getNbVertex();ii++){
        if(s.getSolution()[ii])
            myfile<<" "<<ii+1;
    }
    myfile<<" taille "<<s.taille();
    myfile<<"\n";
    myfile.close();
}

void metaheuristique_bis(string filepath, Graphe g, int time_max, int normal_tabou, int long_tabou, int small_tabou, int nb_iter_sans_changement, int nb_iter_long_tabou, int nb_iter_diversification, int nb_iter_small_tabou){
    vector<bool> vertexTable;
    int n = g.getNbVertex();
    vertexTable.assign(n, 1);
    time_t start = time(NULL);
    time_t time_end_loop = time(NULL);
    //initialize the initial clique with the insertion heuristique
    auto start_heuristique = high_resolution_clock::now();
    Solution sol = heuristique_insertion_legal_strategy(g);
    auto stop_heuristique = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop_heuristique - start_heuristique);
    cout<<"TIME heuristique : "<< duration.count()<<" micro secondes"<<endl;
    cout<<"Taille de la solution obtenue par heuristique par insertion : "<<sol.taille()<<endl;
    printSolution(sol);
    //keep in a variable the best solution so far and write it down
    Solution bestSol = Solution(sol);
    writeSolutionToFile(0, 1e-6*duration.count(), bestSol, filepath);

    int iterations = 0;
    int iterationsTabou = 0;
    int iterationsGlobal = 0;
    int previousIterations = 0;
    //tabou list being a queue of length len_tabou which is variable
    //tabouIndex is keeping track for each vertex if it is tabou or not
    int len_tabou = normal_tabou;
    queue<int> tabou_list = queue<int>();
    vector<bool> tabouIndex;
    tabouIndex.assign(n,0);
    //frequency of each vertex in the best solutions found
    vector<int> frequency(n);
    for(int i=0;i<n;i++){
        frequency[i] = bestSol.getSolution()[i];
    }
    while(time_max==-1 || time_end_loop - start < time_max){
        vector<int> vertexAmeliorantNonTabous;
        vector<pair<int,int>> vertexNeutresNonTabous;
        vector<int> vertexDegradantsNonTabous;
        for(int vertex=1;vertex<sol.getNbVertex();vertex++){
            if(tabouIndex[vertex]==0){
                if(sol.getSolution()[vertex]==1){
                    //build the neighborhood from deletion transform
                    vertexDegradantsNonTabous.push_back(vertex);
                }
                else if(sol.isAjoutAdmissible(vertex, g)){
                    //build the neighborhood from addition transform
                    vertexAmeliorantNonTabous.push_back(vertex);
                }
                else if(sol.getSolution()[vertex]==0){
                    //build the neighborhood from swapping transform
                    int vertex_Suppr = sol.isSwapAdmissible(vertex,g);
                    if(vertex_Suppr!=-1){
                        vertexNeutresNonTabous.push_back(pair(vertex, vertex_Suppr));
                    }
                }
            }
        }
        if(vertexAmeliorantNonTabous.empty()){
            //aspiration criterion
            if(sol.taille()==bestSol.taille()){
                for(int vertex=1;vertex<sol.getNbVertex();vertex++){
                    if(sol.isAjoutAdmissible(vertex, g)){
                        vertexAmeliorantNonTabous.push_back(vertex);
                    }
                }
                if(!vertexAmeliorantNonTabous.empty())
                {
                    cout<<"CRITERE D'ASPIRATION"<<endl;
                }
            }
        }
        if(!vertexAmeliorantNonTabous.empty()){
            // take a random neighbor that increases the solution value
            int random_index = rand()%vertexAmeliorantNonTabous.size();
            sol.addVertex(vertexAmeliorantNonTabous[random_index]);
            // update tabu list
            tabou_list.push(vertexAmeliorantNonTabous[random_index]);
            tabouIndex[vertexAmeliorantNonTabous[random_index]]=1;
            if(tabou_list.size() > len_tabou){
                int vertexFree = tabou_list.front();
                tabou_list.pop();
                tabouIndex[vertexFree] = 0;
            }
        }
        else if(!vertexNeutresNonTabous.empty()){
            // take a random neighbor that is neutral to the solution value
            int random_index = rand()%vertexNeutresNonTabous.size();
            sol.addVertex(vertexNeutresNonTabous[random_index].first);
            sol.delVertex(vertexNeutresNonTabous[random_index].second);
            // update tabu list with deleted vertex
            tabou_list.push(vertexNeutresNonTabous[random_index].second);
            tabouIndex[vertexNeutresNonTabous[random_index].second]=1;
            if(tabou_list.size() > len_tabou){
                int vertexFree = tabou_list.front();
                tabou_list.pop();
                tabouIndex[vertexFree] = 0;
            }
        }
        else if(!vertexDegradantsNonTabous.empty()){
            // take a random neighbor that is neutral to the solution value
            int random_index = rand()%vertexDegradantsNonTabous.size();
            sol.delVertex(vertexDegradantsNonTabous[random_index]);
            // update tabu list
            tabou_list.push(vertexDegradantsNonTabous[random_index]);
            tabouIndex[vertexDegradantsNonTabous[random_index]]=1;
            if(tabou_list.size() > len_tabou){
                int vertexFree = tabou_list.front();
                tabou_list.pop();
                tabouIndex[vertexFree] = 0;
            }
        }
        else{
            // diversify if all the neighbors are tabu
            tabouIndex.assign(g.getNbVertex(),0);
            tabou_list = queue<int>();
            sol = diversification(g, sol);
        }
        if(iterationsTabou==nb_iter_sans_changement+1){
            // restart from another clique after nb_iter_sans_changement+1 iterations without changes on the bestSol
            //tabouIndex.assign(g.getNbVertex(),0);
            //tabou_list = queue<int>();
            cout<<"diversify"<<endl;
            sol = restart_from_another_clique(g, vertexTable, frequency);
        }
        if(iterationsTabou==nb_iter_sans_changement+1+nb_iter_diversification){
            // extend the tabou list nb_iter_sans_changement + nb_iter_diversification+1 iterations without changes on the bestSol
            cout<<"extend tabou"<<endl;
            len_tabou = long_tabou;
        }
        if(iterationsTabou==nb_iter_sans_changement+nb_iter_long_tabou+1+nb_iter_diversification){
            // go back to the normal tabu length after nb_iter_sans_changement + nb_iter_diversification
            // +nb_iter_lon_tabou+1 iterations without changes on the bestSol
            cout<<"shorten tabou"<<endl;
            len_tabou = small_tabou;
            sol = Solution(bestSol);
        }
        if(iterationsTabou==nb_iter_sans_changement+nb_iter_long_tabou+1+nb_iter_diversification+nb_iter_small_tabou){
            // go back to the normal tabu length after nb_iter_sans_changement + nb_iter_diversification
            // +nb_iter_lon_tabou+1 iterations without changes on the bestSol
            cout<<"normal tabou"<<endl;
            len_tabou = normal_tabou;
            iterationsTabou = 0;
        }
        iterations++;
        iterationsTabou++;
        iterationsGlobal++;
        if (sol.taille()>bestSol.taille()){
            bestSol = Solution(sol);
            for(int i=0;i<n;i++){
                frequency[i] = bestSol.getSolution()[i];
            }
            time_t stop = time(NULL);
            time_t duration = stop - start;
            int sommeVertex = 0;
            for(auto elem:vertexTable)
                sommeVertex+=elem;
            //cout<<"Nombre de sommets non elagues "<<sommeVertex<<endl;
            std::cout<<"Nouvelle meilleure solution trouvee en "<<duration<<" secondes et "<<iterationsGlobal<<" iterations"<<endl;
            std::cout<<iterations<<" iterations depuis la derniere bestSol"<<endl;
            std::cout<<"Valeur de la nouvelle solution : "<<bestSol.taille()<<endl;
            //printSolution(bestSol);
            writeSolutionToFile(iterationsGlobal, duration, bestSol, filepath);
            previousIterations = iterations;
            iterations = 0;
            iterationsTabou = 0;
            if(len_tabou != normal_tabou){
                std::cout<<"Retour de la liste taboue a la normale"<<endl;
                len_tabou = normal_tabou;
            }
        }
        time_end_loop = time(NULL);
    }
    std::cout<<"Arret de la metaheuristique"<<endl;
}
