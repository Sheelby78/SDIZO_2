#pragma once
#include <iostream>
#include "Kopiec.h"

using namespace std;

struct DSNode
{
    int up, rank;
};

class Zbiory
{
private:
    DSNode* Z;
public:
    Zbiory(int n);
    ~Zbiory();
    void MakeSet(int v);
    int FindSet(int v);
    void UnionSets(Edge e);
};