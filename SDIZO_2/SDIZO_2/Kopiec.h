#pragma once
#include <iostream>

using namespace std;

struct Edge
{
    int v1, v2, weight;
};

class Kopiec
{
private:
    Edge* Heap;
    int hpos;
public:
    Kopiec(int n);
    ~Kopiec();
    Edge front();
    void push(Edge e);
    void pop();
};