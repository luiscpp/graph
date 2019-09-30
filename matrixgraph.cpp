#include "matrixgraph.h"
#include <vertex.h>
#include <queue>
#include <stack>
#include <vector>

MatrixGraph::MatrixGraph(int maxVertex)
{
    this->maxVertex = maxVertex;
    numVertex = 0;
    //deben ser corchetes o se rompe el programa
    vertices = new Vertex[maxVertex];//Reservando vertices
    adjMatrix = new int*[maxVertex]; //Reservando filas

    for(int i=0 ;i<maxVertex ;i++){
        adjMatrix[i] = new int[maxVertex];//reservando columnas
    }
}

int **MatrixGraph::getAdjMatrix()
{
    return adjMatrix;
}

void MatrixGraph::initializeMatrix()
{
    for(int i=0; i<maxVertex; i++){
        for(int j=0; j<maxVertex; j++){
            adjMatrix[i][j] = 0;
        }
    }
}

void MatrixGraph::printMatrix()
{
    cout<<"\n";
    for(int i=0; i<maxVertex;i++){
        for(int j=0; j<maxVertex;j++){
            cout<<"["<<adjMatrix[i][j]<<"]";
        }
        cout<<"\n";
    }
}

int MatrixGraph::getMaxVertex()
{
    return maxVertex;
}

int MatrixGraph::getNumVertex()
{
    return numVertex;
}

int MatrixGraph::exist(string name)
{
    for(int i=0; i<numVertex;i++){
        if(vertices[i].getName() == name){
            return i;
        }
    }
    return -1;
}


void MatrixGraph::insertVertex(string name)
{
    if(exist(name) == -1 && numVertex < maxVertex){
        Vertex v = Vertex(name, numVertex);//Porque ya se reservaron los new
        vertices[numVertex] = v;
        numVertex++;
    }else{
        cout<<"No se pudo insertar el Vertice!";
    }
}

void MatrixGraph::insertArc(string nameA, string nameB)
{
    int a = exist(nameA), b = exist(nameB);
    if(a >= 0 && b >= 0){
        if(adjMatrix[a][b] == 0){
            adjMatrix[a][b] = 1;
            adjMatrix[b][a] = 1;
        }else{
            cout<<"\nEl arco ya existe!";
        }
    }else{
        cout<<"Uno o ambos vertices no existen!";
    }
}

void MatrixGraph::insertArc(int a, int b)
{
    if(a<0 || b<0 || a>numVertex || b>numVertex){
        cout<<"Uno o ambos vertices no existen!";
    }else{
        if(adjMatrix[a][b] == 0){
            adjMatrix[a][b] = 1;
            adjMatrix[b][a] = 1;
        }else{
            cout<<"\nEl arco ya existe!";
        }
    }
}

void MatrixGraph::insertValueArc(string nameA, string nameB, int value)
{
    int a = exist(nameA), b = exist(nameB);
    if(a >= 0 && b >= 0){
        if(adjMatrix[a][b] == 0){
            adjMatrix[a][b] = value;
        }else{
            cout<<"\nEl arco ya existe!";
        }
    }else{
        cout<<"Uno o ambos vertices no existen!";
    }
}

void MatrixGraph::insertValueArc(int a, int b, int value)
{
    if(a<0 || b<0 || a>numVertex || b>numVertex){
        cout<<"Uno o ambos vertices no existen!";
    }else{
        if(adjMatrix[a][b] == 0){
            adjMatrix[a][b] = value;
        }else{
            cout<<"\nEl arco ya existe!";
        }
    }
}

bool MatrixGraph::isAdjacent(string nameA, string nameB)
{
    int a = exist(nameA), b = exist(nameB);
    if(a >= 0 && b >= 0){
        if(adjMatrix[a][b] != 0){
            return true;
        }
    }
    return false;
}

bool MatrixGraph::isAdjacent(int a, int b)
{
    if(a<0 || b<0 || a>numVertex || b>numVertex){
        return false;
    }else{
        if(adjMatrix[a][b] != 0){
            return true;
        }else{
            return false;
        }
    }
}

int MatrixGraph::getValue(string nameA, string nameB)
{
    int a = exist(nameA), b = exist(nameB);
    if(a >= 0 && b >= 0){
        return adjMatrix[a][b];
    }else{
        cout<<"Uno o ambos vertices no existen!";
        return -1;
    }
}

int MatrixGraph::getValue(int a, int b)
{
    if(a<0 || b<0 || a>numVertex || b>numVertex){
        return -1;
    }else{
        return adjMatrix[a][b];
    }
}

int MatrixGraph::degree(string name)
{
    int counter = 0;
    for(int i =0;i< numVertex;i++){
        if(isAdjacent(name,vertices[i].getName())){
            counter++;
        }
    }
    return counter;
}

int MatrixGraph::degree(int a)
{
    int counter = 0;
    for(int i =0;i< numVertex;i++){
        if(isAdjacent(a,i)){
            counter++;
        }
    }
    return counter;
}

int MatrixGraph::entryDegree(string name)
{
    int counter = 0;
    for(int i =0;i< numVertex;i++){
        if(isAdjacent(vertices[i].getName(),name)){
            counter++;
        }
    }
    return counter;
}

int MatrixGraph::exitDegree(string name)
{
    int counter = 0;
    for(int i =0;i< numVertex;i++){
        if(isAdjacent(name,vertices[i].getName())){
            counter++;
        }
    }
    return counter;
}

int MatrixGraph::entryDegree(int a)
{
    int counter = 0;
    for(int i =0;i< numVertex;i++){
        if(isAdjacent(i,a)){
            counter++;
        }
    }
    return counter;
}

int MatrixGraph::exitDegree(int a)
{
    int counter = 0;
    for(int i =0;i< numVertex;i++){
        if(isAdjacent(a,i)){
            counter++;
        }
    }
    return counter;
}


Vertex *MatrixGraph::getVertex(string name)
{
    for(int i=0; i<numVertex; i++){
        if(name == vertices[i].getName()){
            return &vertices[i];
        }
    }
}

bool MatrixGraph::visited(int *v, int number)
{
    if(v[number] != 0){
        return true;
    }

    return false;
}

void MatrixGraph::breadthFirstSearch(string name)
{
    queue<string> queue;
    int *marks = new int[numVertex];//vector de marcas
    for(int i=0;i< numVertex; i++){
        marks[i] = 0;
    }
    Vertex *v = getVertex(name);
    marks[v->getNumber()] = 1;//marcado
    queue.push(name);

    while(!queue.empty()){
        name = queue.front();
        queue.pop();
        cout<<name<<"\n";
        for(int j =0; j<numVertex;j++){
            if(isAdjacent(name,vertices[j].getName()) && !visited(marks,vertices[j].getNumber())){
                queue.push(vertices[j].getName());
                marks[vertices[j].getNumber()] = 1;//marcado
            }
        }
    }
}

void MatrixGraph::depthFirstSearch(string name)
{
    stack<string> stack;
    int *marks = new int[numVertex];//vector de marcas
    for(int i=0;i< numVertex; i++){
        marks[i] = 0;
    }
    Vertex *v = getVertex(name);
    marks[v->getNumber()] = 1;//marcado
    stack.push(name);

    while(!stack.empty()){
        name = stack.top();
        stack.pop();
        cout<<name<<"\n";
        for(int j =0; j<numVertex;j++){
            if(isAdjacent(name,vertices[j].getName()) && !visited(marks,vertices[j].getNumber())){
                stack.push(vertices[j].getName());
                marks[vertices[j].getNumber()] = 1;//marcado
            }
        }
    }
}

bool MatrixGraph::allMarked(int *v)
{
    for(int i=0;i<numVertex;i++){
        if(v[i] != 1){
            return false;
        }
    }
    return true;
}

void MatrixGraph::connectedGraph(string name, int *marks)
{
    int *temporaryMarks = new int[numVertex]; //deben ser corchetes o se rompe el programa

    for(int i=0;i<numVertex;i++){
        temporaryMarks[i] = 0;
    }
    stack<string> stack;

    Vertex *v = getVertex(name);
    marks[v->getNumber()] = 1;//marcado
    temporaryMarks[v->getNumber()] = 1;
    stack.push(name);

    while(!stack.empty()){
        name = stack.top();
        stack.pop();
        for(int j =0; j<numVertex;j++){
            if(isAdjacent(name,vertices[j].getName()) && !visited(temporaryMarks,vertices[j].getNumber())){
                stack.push(vertices[j].getName());
                marks[vertices[j].getNumber()] = 1;//marcado y visible para todos los recorridos
                temporaryMarks[vertices[j].getNumber()] = 1;//marcado y visible solo para este recorrido
            }
        }
    }
    if(allMarked(temporaryMarks)){
        cout<<"El grafo es conexo!\n";
    }else{
        for(int i=0; i<numVertex;i++){
            if(temporaryMarks[i] != 0){//está marcado y forma parte de una componente conexa
                cout<<vertices[i].getName()<<"-";
            }
        }
        cout<<"\n";
        if(!allMarked(marks)){
            for(int i=0;i<numVertex;i++){
                if(marks[i] == 0){
                    connectedGraph(vertices[i].getName(),marks);//llamado recursivo
                }
            }
        }
    }
}

vector<string> MatrixGraph::getVertexConjunct(MatrixGraph *g, string name)
{
    stack<string> stack;
    vector<string> conjunct;
    int *marks = new int[g->getNumVertex()];//vector de marcas
    for(int i=0;i< g->getNumVertex(); i++){
        marks[i] = 0;
    }
    Vertex *v = g->getVertex(name);
    marks[v->getNumber()] = 1;//marcado
    stack.push(name);

    while(!stack.empty()){
        name = stack.top();
        conjunct.push_back(name);
        stack.pop();
        for(int j =0; j<g->getNumVertex();j++){
            if(g->isAdjacent(name,g->vertices[j].getName()) && !g->visited(marks,g->vertices[j].getNumber())){
                stack.push(g->vertices[j].getName());
                marks[g->vertices[j].getNumber()] = 1;//marcado
            }
        }
    }
    return conjunct;
}

void MatrixGraph::reverseGraph(MatrixGraph *g)
{
    int reverse[g->maxVertex][g->maxVertex];
    for(int i=0;i<g->getMaxVertex();i++){
        for(int j=0;j<g->getMaxVertex();j++){
            reverse[j][i] = g->adjMatrix[i][j];
        }
    }

    for(int i=0;i<g->getMaxVertex();i++){
        for(int j=0;j<g->getMaxVertex();j++){
            g->adjMatrix[i][j] = reverse[i][j];
        }
    }
}


vector<string> MatrixGraph::commonVertices(vector<string> a, vector<string> b)
{
    vector<string> common;
    for(int i=0;i<a.size();i++){
        for(int j=0;j<b.size();j++){
            if(a.at(i) == b.at(j)){
                common.push_back(a.at(i));
            }
        }
    }
    return common;
}

void MatrixGraph::stronglyConnectedGraph(string name,int *marks, MatrixGraph *reverse)//reverse es el grafo con los arcos invertidos
{
     vector<string> decendents = MatrixGraph::getVertexConjunct(this,name);
     vector<string> ascendents = MatrixGraph::getVertexConjunct(reverse,name);
     vector<string> common = MatrixGraph::commonVertices(decendents,ascendents);

     if(common.size() == numVertex){//es fuertemente conexo
        cout<<"Es fuertemente conexo!\n";
     }else{
         cout<<"Componente conexa\n";//componente conexa

         for(int i=0; i<common.size();i++){
            Vertex *v = getVertex(common.at(i));
            marks[v->getNumber()] = 1;//marca las componentes conexas
            cout<<common.at(i)<<"-";
         }
         cout<<"\n";
         if(!allMarked(marks)){
             for(int i=0;i<numVertex;i++){
                 if(marks[i] == 0){
                    stronglyConnectedGraph(vertices[i].getName(),marks,reverse);
                 }
             }
         }
     }
}

void MatrixGraph::matrixProduct(int **A, int **B, int **C, int size)
{
    for(int i=0; i<size;i++){
        for(int j = 0; j<size; j++){
            for(int z=0; z<size; z++){
                C[i][j] += A[i][z] * B[z][j];
            }
        }
    }
}

vector<string> MatrixGraph::getAllNameOfVertices()
{
    vector<string> names;
    for(int i=0;i<numVertex;i++){
        names.push_back(vertices[i].getName());
    }

    return names;
}

void MatrixGraph::evaluateMatrixProduct(int **M, vector<string> vertices)
{
    for(int i=0;i<vertices.size();i++){
        for(int j=0; j<vertices.size();j++){
            if(M[i][j] != 0){
                cout<<vertices[i]<<" - "<<vertices[j]<<"\n";
            }
        }
    }
}


void MatrixGraph::deleteArc(int a, int b)
{
    if(a<0 || b<0 || a>numVertex || b>numVertex){
        cout<<"Uno o ambos vertices no existen!";
    }else{
        adjMatrix[a][b] = 0;
    }
}

bool MatrixGraph::containsArcs()
{
    for(int i=0;i<numVertex;i++){//Solo es necesario recorrerla hasta el número de vertices que existan
        for(int j=0;j<numVertex;j++){
            if(adjMatrix[i][j] != 0){
                return true;
            }
        }
    }
    return false;
}

vector<string> MatrixGraph::topologicalSort()
{
    vector<string> orderedElements;//Lista de elementos en orden
    queue<int> noEntryDegree;
    int arcs;
    for(int i=0; i<numVertex;i++){//Obtener indices de vértices sin aristas entrantes
        arcs = 0;
        for(int j=0; j<numVertex;j++){
            if(isAdjacent(j,i)){
                arcs++;
            }
        }
        if(arcs == 0){
            noEntryDegree.push(i);
        }
    }

    while(!noEntryDegree.empty()){
        int vertexIndex = noEntryDegree.front();
        orderedElements.push_back(vertices[vertexIndex].getName());
        noEntryDegree.pop();

        for(int i=0; i<numVertex; i++){
            if(isAdjacent(vertexIndex,i)){
                deleteArc(vertexIndex,i);
                if(entryDegree(i) == 0){//si no contiene arcos entrantes
                    noEntryDegree.push(i);
                }
            }
        }
    }

    if(containsArcs()){//si al acabar el grafo tiene algún arco significa que hay por lo menos un ciclo
        orderedElements.clear();//se borran todos los elementos que se habian guardado
    }

    return orderedElements;
    //esta funcion retorna orderedElements vacío si al finalizar el ordenamiento el grafo contiene arcos, de lo contrario retorna el vertor ordenado
}

int **MatrixGraph::warshall(int **matrix,int nVertices)
{
    for(int k=0; k<nVertices; k++){//donde k es vertice puente
        for(int i=0;i<nVertices;i++){
            for(int j=0;j<nVertices;j++){
                if(matrix[i][k] * matrix[k][j]){//si hay un arco de i->k y otro de k->j entonces hay uno de i->j, true = 1, false = 0
                    matrix[i][j] = 1;
                }
            }
        }
    }
    return matrix;
}

int **MatrixGraph::floyd(int **matrix, int **trace, int nVertices)
{
    int infinite = 9999;
    for(int i = 0;i< nVertices; i++){//Preparando la matriz con valores infinitos
        for(int j=0;j <nVertices; j++){
            trace[i][j] = -1;//para la traza, -1 significa que el camino es directo
          if(matrix[i][j] == 0){
              if(i!=j){
                matrix[i][j] = infinite;
              }
            }
        }
    }

    for(int k=0; k<nVertices; k++){//k es el vertice puente
        for(int i=0; i<nVertices; i++){
            for(int j=0; j<nVertices; j++){
                if(i!=j){
                    int wayValue = matrix[i][k]+matrix[k][j];
                    if(wayValue < matrix[i][j]){
                        matrix[i][j] = wayValue;
                        trace[i][j] = k;
                    }
                }
            }
        }
    }
    return matrix;
}

void MatrixGraph::recovery(string A,string B, int **trace)
{
    int a = exist(A);
    int b = exist(B);

    if(a < 0 || b < 0){
        cout<<"Uno o ambos vertices no existen!";
    }else{
        if(adjMatrix[a][b] == 9999 || adjMatrix[a][b] == 0){
            cout<<"\nNo existe camino";
        }else{
            cout<<vertices[a].getName()<<"->";
            pathRecovery(a,b,trace);
            cout<<vertices[b].getName();
        }
    }
}

void MatrixGraph::pathRecovery(int a, int b,int **trace)
{
    int k = trace[a][b];
    if(k!=-1){
        pathRecovery(a,k,trace);
        cout<<vertices[k].getName()<<"->";
        pathRecovery(k,b,trace);
    }
}

bool MatrixGraph::visited(vector<int> v, int number)
{
    for(int i=0; i< v.size();i++){
        if(v.at(i) == number){
            return true;
        }
    }
    return false;
}

void MatrixGraph::searchAllPath(int a, int b, vector<int> marks,vector<string> path)
{
    marks.push_back(a);//marcamos el origen
    path.push_back(vertices[a].getName());

    for(int i=0;i<numVertex;i++){
        if(isAdjacent(a,i) && !visited(marks,i)){
            if(i == b){
                for(int j =0;j<path.size();j++){//mostramos el camino excluyendo el destino
                    cout<<path.at(j);
                }
                cout<<vertices[b].getName();//mostramos el destino
                /*Obsérvese que el destino se muestra por aparte (nunca entra en el vector de ruta path),
                  para evitar enviarlo en el próximo camino (llamada recursiva)*/
                cout<<endl;
            }else{
                searchAllPath(i,b,marks,path);
            }
        }
    }
}


void MatrixGraph::searchMinimalPath(int a, int b,int sizePath, vector<int> marks, vector<string> path, vector<string> *minimalPath,int *sizeMinimalPath)
{
    marks.push_back(a);//marcamos el origen
    path.push_back(vertices[a].getName());

    for(int i=0;i<numVertex;i++){
        if(isAdjacent(a,i) && !visited(marks,i)){
            if(i == b){
                if((sizePath + adjMatrix[a][i]) < *sizeMinimalPath || *sizeMinimalPath == 0){
                    *sizeMinimalPath = sizePath + adjMatrix[a][i];
                    /*Obsérvese que el arco destino se suma por aparte (nunca se suma en sizePath, sino en adjMatrix),
                      para evitar enviarlo en el próximo camino (llamada recursiva)*/

                    minimalPath->clear();
                    for(int j =0;j<path.size();j++){//mostramos el camino excluyendo el destino
                        minimalPath->push_back(path.at(j));
                    }
                    minimalPath->push_back(vertices[b].getName());//agregamos el destino
                    /*Obsérvese que el destino se agrega por aparte (nunca entra en el vector de ruta path),
                      para evitar enviarlo en el próximo camino (llamada recursiva)*/
                }
            }else{
                searchMinimalPath(i, b,adjMatrix[a][i] + sizePath, marks, path, minimalPath, sizeMinimalPath);
                //sizePath es la distancia del arco anterior y adjMatrix es la distancia del nuevo -- i,b es el nuevo arco
            }
        }
    }
}

void MatrixGraph::findCycle(int a, int b, vector<int> marks, vector<string> path)
{
    path.push_back(vertices[a].getName());
    if(a != b){//Nunca se marca el origen, porque tiene que volver a el
        marks.push_back(a);
    }

    for(int i=0;i<numVertex;i++){
        if(isAdjacent(a,i) && !visited(marks,i)){
            if(i == b){//es el destino
                for(int j=0;j<path.size();j++){
                    cout<<path.at(j);
                }
                cout<<vertices[b].getName();
                cout<<endl;
            }else{//NO es el destino
                findCycle(i,b,marks,path);
            }
        }
    }
}
