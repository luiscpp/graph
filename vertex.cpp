#include "vertex.h"

Vertex::Vertex()
{
    this->name = "";
    this->number = -1;
}

Vertex::Vertex(string name, int number)
{
    this->name = name;
    this->number = number;
}

string Vertex::getName()
{
    return name;
}

void Vertex::setName(string name)
{
    this->name = name;
}

int Vertex::getNumber()
{
    return number;
}

void Vertex::setNumber(int number)
{
    this->number = number;
}
