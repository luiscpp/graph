#include <iostream>
#include <matrixgraph.h>
#include <vector>

using namespace std;

int main()
{
    MatrixGraph *g = new MatrixGraph(5);
    g->initializeMatrix();
    g->insertVertex("A");
    g->insertVertex("B");
    g->insertVertex("C");
    g->insertVertex("D");
    g->insertVertex("E");

    g->insertValueArc("A","A",1);
    g->insertValueArc("A","B",1);
    g->insertValueArc("A","E",1);

    g->insertValueArc("B","A",1);

    g->insertValueArc("C","B",1);

    g->insertValueArc("D","C",1);
    g->insertValueArc("D","A",1);

    g->insertValueArc("E","D",1);
    g->insertValueArc("E","C",1);


    g->printMatrix();
    vector<string> ruta;
    vector<int> marks;

    for(int i=0;i<g->getNumVertex();i++){
        g->findCycle(i,i,marks,ruta);
    }

    cout<<endl;

    return 0;
}
