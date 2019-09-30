#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include <iostream>
#include <vertex.h>
#include <list>
#include <vector>
using namespace std;

class Vertex;
class MatrixGraph
{
private:
    int maxVertex; //Numero maximo de vertices
    int numVertex; //Numero de vertices actuales
    Vertex *vertices;//arreglo de vertices
    int **adjMatrix;//matriz de adjacencia
public:
    MatrixGraph(int maxVertex);
    int **getAdjMatrix();//devuelve la matriz de adyacencia
    void initializeMatrix();
    void printMatrix();
    int getMaxVertex();
    int getNumVertex();
    int exist(string name);
    void insertVertex(string name);
    void insertArc(string nameA,string nameB);
    void insertArc(int a,int b);
    void insertValueArc(string nameA,string nameB, int value);
    void insertValueArc(int a,int b, int value);
    bool isAdjacent(string nameA,string nameB);
    bool isAdjacent(int a,int b);
    int getValue(string nameA,string nameB);//Retornar el valor almacenado en la matriz de adyacencia para los vértices que recibe como parámetro
    int getValue(int a,int b);
    int degree(string name);
    int degree(int a);
    int entryDegree(string name);
    int exitDegree(string name);
    int entryDegree(int a);
    int exitDegree(int b);
    Vertex *getVertex(string name);

    //Recorridos
    void breadthFirstSearch(string name);//busqueda en profundidad
    void depthFirstSearch(string name);//busqueda en anchura
    bool visited(int *v, int number);
    bool allMarked(int *v);

    //Grafo no dirigido conexo
    void connectedGraph(string name,int *marks);//mostrar componentes conexas de grafo no dirigido o decir si es conexo

    //Grafo dirigido fuertemente conexo
    static vector<string> getVertexConjunct(MatrixGraph *g, string name);
    static void reverseGraph(MatrixGraph *g);//invierte los arcos de un grafo
    static vector<string> commonVertices(vector<string> a, vector<string> b);//vertices comunes de los conjuntos ascendientes y descendientes
    void stronglyConnectedGraph(string name,int *marks, MatrixGraph *reverse);//mostrar componentes conexas de grafo dirigido o decir si es fuertemente conexo

    //NOTA: ALGUNOS ALGORITMO QUE SE LISTAN A CONTINUACION MODIFICAN LA MATRIZ DE ADYACENCIA ORIGINAL

    //Matriz de n caminos
    static void matrixProduct(int **A,int **B,int **C,int size);//producto matricial
    static void evaluateMatrixProduct(int **M,vector<string> vertices);//obtiene el inicio y final de un camino de longitud k dependiendo de los productos matriciales que se hicieron
    vector<string> getAllNameOfVertices();//obtiene el nombre de todos los vertices

    //Ordenación topológica
    void deleteArc(int a, int b);
    bool containsArcs();//verifica si el grafo contiene algún arco
    vector<string> topologicalSort();// llamarlo desde una copia del grafo original, porque se eliminan todas las aristas

    //Matriz de caminos - Algoritmo de Warshall
    static int **warshall(int **matrix,int nVertices);

    //Matriz de caminos minimos - Floyd
    static int **floyd(int **matrix,int **trace, int nVertices);//trace para ver la secuencia de vertices entre los pares de nodos
    void recovery(string A,string B, int **trace);//llama a way recovery para ver decodificar la secuencia de vertices
    void pathRecovery(int a,int b,int **trace);

    //Busca todos los caminos entre un par de vertices sin importar si el grafo es valorado o no
    void searchAllPath(int a,int b, vector<int> marks, vector<string> path);
    bool visited(vector<int> v,int number);

    //Busca el camino minimo en un grafo sin importar si el grafo es valorado o no
    void searchMinimalPath(int a, int b,int sizePath, vector<int> marks, vector<string> path, vector<string> *minimalPath,int *sizeMinimalPath);

    //Busca los ciclos de un vertice
    void findCycle(int a,int b,vector<int> marks,vector<string> path);


};

#endif // MATRIXGRAPH_H
