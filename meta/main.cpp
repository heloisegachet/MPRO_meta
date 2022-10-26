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
//string filename = "p_hat1500-3.txt";
//string filename = "p_hat700-1.txt";
//string filename = "C500.9.txt";
//string filename = "C2000.5.txt";
string filename = "brock800_4.txt";
//string filename = "gen400_p0.9_75.txt";


int main(int argc, char *argv[])
   {  
   string filepath = (filesystem::current_path()).parent_path().string() + "/Instances/"+filename;
   //build graph
   Graphe g(filepath);

   string filepath_sol = filepath.substr(0, filepath.size()-4)+"_sol.txt";
   if (filesystem::remove(filepath_sol))
      std::cout << "file " << filepath_sol << " deleted.\n";
   else
      std::cout << "file " << filepath_sol << " not found.\n";
   int time_max = 5*60;//30;
   int normal_tabou = 2;
   int long_tabou = 15;
   int nb_iter_sans_changements = 1000; //2000   
   int nb_iter_long_tabou = 1000;    //2000
   int nb_iter_diversification = 1000; //5000
   //metaheuristique(filepath_sol, g, time_max, normal_tabou, long_tabou, nb_iter_diversification, nb_iter_long_tabou, nb_iter_diversification);  
   metaheuristique_bis(filepath_sol, g, time_max, normal_tabou, long_tabou, nb_iter_diversification, nb_iter_long_tabou, nb_iter_diversification);  
   
}