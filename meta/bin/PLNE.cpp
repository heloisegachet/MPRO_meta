// must define the IL_STD marco for current standard c++ version rather than older one. 
#include "PLNE.h"

#include <ilcplex/ilocplex.h>
ILOSTLBEGIN


void populate_variables(IloModel model, IloNumVarArray x, Graphe g){
    IloEnv env = model.getEnv();
    for(int i = 0; i < g.getNbVertex();i++){
        x.add(IloNumVar(env, 0.0,1.0, ILOINT));
    }  
}

void populate_contraintes(IloModel model, IloRangeArray c, IloNumVarArray x, Graphe g){
    for(int i = 0; i < g.getNbVertex();i++){
        for(int j = 0; j < g.getNbVertex();j++){
            if(g.getEdge()[i][j]){
                c.add(x[i]+x[j] <= 1);
            }
            model.add(c);
        }
    }
}

void populate_objectif(IloModel model, IloNumVarArray x, Graphe g){
    IloEnv env = model.getEnv();
    IloNumExpr expr;
    for(int i = 0; i < g.getNbVertex();i++){
        expr += x[i];
    }
    model.add(IloMaximize(env, expr));
}

void build_solve_PLNE(Graphe g){
    IloEnv env;
    try {
        IloModel model(env);

        IloNumVarArray var(env);
        IloRangeArray con(env);
        populate_variables(model, var, g);
        populate_contraintes(model, con, var, g);
        populate_objectif(model, var, g);
        IloCplex cplex(model);
        cplex.solve();

        env.out() << "Solution status = " << cplex.getStatus() << endl;
        env.out() << "Solution value  = " << cplex.getObjValue() << endl;

        IloNumArray vals(env);
        cplex.getValues(vals, var);
        env.out() << "Values        = " << vals << endl;
        cplex.getSlacks(vals, con);
        env.out() << "Slacks        = " << vals << endl;

    }
    catch (IloException& e) {
        cerr << "Concert exception caught: " << e << endl;
    }
    catch (...) {
        cerr << "Unknown exception caught" << endl;
    }
    env.end();
}

