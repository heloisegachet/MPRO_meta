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

int Solution::isSwapAdmissible(int v, Graphe graphe){
    if(solution[v] == 1)
        return -1; //le sommet est déjà dans la solution
    int nb_vertex_sol=0;
    int somme_vertex = 0;
    int vSuppr = -1;
    for(int v2=0;v2<lenSol;v2++){
        if(solution[v2]==1){
            somme_vertex += graphe.getEdge()[v][v2];
            if(v!=v2 && graphe.getEdge()[v][v2]==0){
                vSuppr = v2;
            }
            nb_vertex_sol++;
        }
    }
    if(somme_vertex == nb_vertex_sol-1)
        return vSuppr;
    return -1;
}

void printSolution(Solution s){
    //vertices from 1 to n
    cout<<"Solution : ";
    for(int ii=0; ii<s.getNbVertex();ii++){
        if(s.getSolution()[ii])
            cout<<" "<<ii;
    }
    cout<<endl;
}


