// C++ project
// Project:  Metaheuristique MPRO 2022/2023
// Author:   Camille RICHER et Héloïse GACHET
// Date:     2022/10/17


#include "tests.h"

//string filename = "random-10.col";
//string filename = "random-40.col";
//string filename = "random-70.col";
//string filename = "random-100.col";
//string filename = "dsjc125.1.col";
//string filename = "brock200_2.col";
//string filename = "dsjc125.1.col";
//string filename = "dsjc250.5.col";
//string filename = "dsjc500.1.col";
//string filename = "dsjc500.5.col";
//string filename = "dsjc500.9.col";
//string filename = "dsjc1000.1.col";
//string filename = "dsjc1000.5.col";
//string filename = "dsjc1000.9.col";
string filename = "p_hat1500-3.txt";
//string filename = "p_hat700-1.txt";
//string filename = "C500.9.txt";
//string filename = "C2000.5.txt";
//string filename = "brock800_4.txt";


//string filepath = "C:/Users/gache/Documents/ENPC/3A/Metaheuristic/git/Instances/"+filename;


// include as argument : ../Instances/<instance_name>

int main(int argc, char *argv[])
{  /*
    string filepath = (filesystem::current_path()).parent_path().parent_path().string() + "/Instances/"+filename;
    Graphe g(filepath);
    
    string filepath_sol = filepath.substr(0, filepath.size()-4)+"_sol.txt";
    if (filesystem::remove(filepath_sol))
       std::cout << "file " << filepath_sol << " deleted.\n";
    else
       std::cout << "file " << filepath_sol << " not found.\n";
    //metaheuristique(filepath_sol, g,1,10,2000,2000,0.05,500);
   int time_max = 60*5;
   int normal_tabou = 1;
   int long_tabou = 100;
   int nb_iter_sans_changements = 4000;    
   int nb_iter_long_tabou = 2000;    
   int nb_iter_diversification = 5000;
   float percentSuppr = 0.05;
   float seuil = 0.05;
   metaheuristique(filepath_sol, g, time_max, normal_tabou, long_tabou, nb_iter_diversification, nb_iter_long_tabou, nb_iter_diversification,
                  percentSuppr,seuil);  
   */
   launchTest(60*5);
}