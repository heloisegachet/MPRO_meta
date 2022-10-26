#include "tests.h"

void launchTest(int time_max){
    vector<string> filesTest;
    filesTest.push_back("random-10.col");
    filesTest.push_back("random-40.col");
    filesTest.push_back("random-70.col");
    filesTest.push_back("random-100.col");
    filesTest.push_back("brock200_2.col");

    filesTest.push_back("dsjc125.1.col");
    //filesTest.push_back("dsjc250.5.col");
    //filesTest.push_back("dsjc500.1.col");
    //filesTest.push_back("dsjc500.5.col");
    //filesTest.push_back("dsjc500.9.col");
    //filesTest.push_back("dsjc1000.1.col");
    //filesTest.push_back("dsjc1000.5.col");
    //filesTest.push_back("dsjc1000.9.col");

    //filesTest.push_back("p_hat1500-3.txt");
    //filesTest.push_back("p_hat700-1.txt");
    //filesTest.push_back("C500.9.txt");
    //filesTest.push_back("C2000.5.txt");
    //filesTest.push_back("brock800_4.txt");
    //filesTest.push_back("gen400_p0.9_75.txt");
    

    for(auto filename:filesTest){
        string filepath = (filesystem::current_path()).parent_path().string() + "/Instances/"+filename;
        Graphe g(filepath);    
        string filepath_sol = filepath.substr(0, filepath.size()-4)+"_sol.txt";
        filesystem::remove(filepath_sol);

        int normal_tabou = 2;
        int long_tabou = 15;
        int nb_iter_sans_changements = 1000; //2000   
        int nb_iter_long_tabou = 1000;    //2000
        int nb_iter_diversification = 1000; //5000
        //for(int i=0;i<5;i++)
        metaheuristique_bis(filepath_sol, g, time_max, normal_tabou, long_tabou, nb_iter_diversification, nb_iter_long_tabou, nb_iter_diversification); 
    }
}
