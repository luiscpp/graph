#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>

using namespace std;

class Vertex
{
private:
    string name;
    int number;
public:
    Vertex();
    Vertex(string name, int number);
    string getName();
    void setName(string name);
    int getNumber();
    void setNumber(int number);
};

#endif // VERTEX_H
