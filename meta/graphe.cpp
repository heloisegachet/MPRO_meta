#include "graphe.h"

Graphe::Graphe(int n_){
    m = 0;
    n = n_;
    edge = new int*[n];
    for(int ii=0;ii<n;ii++){
        edge[ii]=new int[n];
       for(int jj=0;jj<n;jj++){
            edge[ii][jj]=0;
       }
    }
}

Graphe::Graphe(string filepath){
    ifstream graphStream;
    graphStream.open(filepath);
    if ( graphStream.fail() ){
          cerr << " Error opening " << filepath << endl;
          exit(0);
    }
    char token[100];
    graphStream >> token;
    if (graphStream.eof()){
          cerr << " Found EOF while reading in the beginning " << filepath << endl;
          exit(0);
    }
    int x1, x2;
    int mCount=0;
    while ( ! graphStream.eof() ) {
       if (!strcmp(token, "p" )) {
           char dummyWord[50];
           graphStream >> dummyWord >> n >> m;
           clog << "Vertices = " << n << ",";
           clog << "Edges = " << m << "\n";
           edge=new int*[n];                  //:: indicates it's a global variable
           for(int ii=0;ii<n;ii++){
               edge[ii]=new int[n];
               for(int jj=0;jj<n;jj++){
                   edge[ii][jj]=0;
               }
           }
       }
       if (!strcmp(token, "e")){
           graphStream >> x1 >> x2;
           x1--; x2--;
           if ( x1<0 || x2<0 || x1>=n || x2 >=n ){
                 cerr << "Error reading ::edges x1=" << x1 << ", x2=" << x2 << endl;
           }
           edge[x1][x2]=1;
           edge[x2][x1]=1;
           mCount++;
       }
       graphStream >> token;
    }
    //if ( (::m != mCount)) cerr<<"Warning reading graph. Announced m size=" << ::m << ", found=" << mCount  << endl;
    m = mCount;
    graphStream.close();
}

/*
Graphe::~Graphe(){
	for(int ii=0;ii<n;ii++){
		delete[] edge[ii];	   
	}
	delete[] edge;
}*/

vector<int> Graphe::getVertexDegree(){
    vector<int> table;
    table.assign(n,0);
    for(int v=0;v<n;v++){
        for(int v2=0;v2<n;v2++){
            table[v] += edge[v][v2];
        }
    }
    return table;
}

void Graphe::addEdge(int i, int j){
    edge[i][j] = 1;
    m++;
}
void Graphe::delEdge(int i, int j){
    edge[i][j] = 0;
    m--;
}

void Graphe::printGraphe(){
    for(int v=0;v<n;v++){
        for(int v2=0;v2<n;v2++){
            cout<<edge[v][v2]<<" ";
        }
        cout<<endl;
    }
}