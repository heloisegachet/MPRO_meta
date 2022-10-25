#include "solution.h"

Solution::Solution(int n){
    solution.assign(n, 0);
    lenSol = n;
}

Solution::Solution(Solution const &newSol){
    lenSol = newSol.lenSol;
    solution.assign(lenSol,0);
    for(int i=0;i<lenSol;i++){
        solution[i] = newSol.solution[i];
    }
}

vector<Solution> Solution::voisins(Graphe graphe, bool admissibleOnly){
    //AJOUT + SUPPRESSION
    vector<Solution> voisinage = voisinsAjout(graphe, true);
    vector<Solution> voisinage_suppr = voisinsSuppr(graphe);
    for(vector<Solution>::iterator it=voisinage_suppr.begin();it!=voisinage_suppr.end();it++){
        voisinage.push_back(*it);
    }
    return voisinage;    
}

vector<Solution> Solution::voisinsAjout(Graphe graphe, bool admissibleOnly){
    vector<Solution> tabSol;
    vector<int> degree_table = graphe.getVertexDegree();

    //Trier les sommets par degrés décroissants
    vector<int> Vertices(lenSol);

    iota(Vertices.begin(),Vertices.end(),0); //Initializing
    stable_sort( Vertices.begin(),Vertices.end(), [&](int i,int j){return degree_table[i]>degree_table[j];} );


    //Ajouter les sommets à la solution courante si on conserve l'admissibilité
    for(vector<int>::iterator it =Vertices.begin(); it !=Vertices.end(); ++it){
        //AJOUT D'UN SOMMET (bit 0 -> 1): VERIFICATION D'ADMISSIBILITE DE LA SOLUTION VOISINE
        if(!admissibleOnly || isAjoutAdmissible(*it, graphe)){
            Solution voisin = Solution(*this);
            voisin.addVertex(*it);
            tabSol.push_back(voisin);
        }
    }
    return tabSol;
}

vector<Solution> Solution::voisinsSuppr(Graphe graphe){
    vector<Solution> tabSol;
    vector<int> degree_table = graphe.getVertexDegree();

     //Trier les sommets par degrés décroissants
    vector<int> Vertices(lenSol);

    iota(Vertices.begin(),Vertices.end(),0); //Initializing
    stable_sort( Vertices.begin(),Vertices.end(), [&](int i,int j){return degree_table[i]<degree_table[j];} );

    //Ajouter les sommets à la solution courante si on conserve l'admissibilité
    for(int i=0; i<lenSol; i++){
        //SUPPRESSION D'UN SOMMET (bit 1 -> 0): SOLUTION ADMISSIBLE
        if(solution[i]==1){
              Solution voisin = Solution(*this);
              voisin.delVertex(i);
              tabSol.push_back(voisin);
         }
    }
    return tabSol;
}

vector<Solution> Solution::voisinsEchange(Graphe graphe, bool admissibleOnly){
    vector<Solution> tabSol;

    //Ajouter les sommets à la solution courante si on conserve l'admissibilité
    for(int i=0; i<lenSol; i++){
        //SUPPRESSION D'UN SOMMET (bit 1 -> 0): SOLUTION ADMISSIBLE
        if(solution[i]==1){
            //AJOUT D'UN SOMMET (bit 0 -> 1) : VERIFICATION ADMISSIBILITÉ
            for(int ii=0; ii<lenSol;ii++){
                if(!admissibleOnly || isAjoutAdmissible(ii, graphe)){
                Solution voisin = Solution(*this);
                voisin.addVertex(ii);
                voisin.delVertex(i);
                tabSol.push_back(voisin);
                }
            }
        }          
    }
    return tabSol;
}

void Solution::addVertex(int i){
    if(solution[i]==1)
        throw invalid_argument( "ajout d'un sommet qui est deja dans la clique" );
    solution[i] = 1;
}

void Solution::delVertex(int i){
    if(solution[i]==0)
        throw invalid_argument( "suppression d'un sommet qui n'est pas dans la clique" );
    solution[i] = 0;
}

int Solution::taille(){
    int t=0;
    for(int v =0;v<lenSol;v++){
        t += solution[v];
    }
    return t;
}

bool Solution::isAdmissible(Graphe graphe){
    for(int vertex=0;vertex<lenSol;vertex++){
        if(solution[vertex]==1){
            int nb_vertex_sol=0;
            int somme_vertex = 0;
            for(int v2=0;v2<lenSol;v2++){
                if(solution[v2]==1){
                    somme_vertex += graphe.getEdge()[vertex][v2];
                    nb_vertex_sol++;
                }
            }
            if(somme_vertex != nb_vertex_sol-1)
                return false;
        }
    }
    return true;
}

bool Solution::isAjoutAdmissible(int v, Graphe graphe){
    if(solution[v] == 1)
        return false; //le sommet est déjà dans la solution
    int nb_vertex_sol=0;
    int somme_vertex = 0;
    for(int v2=0;v2<lenSol;v2++){
        if(solution[v2]==1){
            somme_vertex += graphe.getEdge()[v][v2];
            nb_vertex_sol++;
        }
    }
    return somme_vertex == nb_vertex_sol;
}

void printSolution(Solution s){
    /*for(int ii=0; ii<s.getNbVertex();ii++){
        cout<<" "<<s.getSolution()[ii];
    }*/
    cout<<"Solution : ";
    for(int ii=0; ii<s.getNbVertex();ii++){
        if(s.getSolution()[ii])
            cout<<" "<<ii;
    }
    cout<<endl;
}


