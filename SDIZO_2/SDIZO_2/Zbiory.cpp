#include "Zbiory.h"

Zbiory::Zbiory(int n)
{
    Z = new DSNode[n];
}

// Destruktor
Zbiory::~Zbiory()
{
    delete[] Z;
}

// Tworzy wpis w tablicy Z
void Zbiory::MakeSet(int v)
{
    Z[v].up = v;
    Z[v].rank = 0;
}

// Zwraca indeks reprezentanta zbioru, w którym jest wierzcho³ek v
int Zbiory::FindSet(int v)
{
    if (Z[v].up != v) Z[v].up = FindSet(Z[v].up);
    return Z[v].up;
}

// £¹czy ze sob¹ zbiory z v i u
void Zbiory::UnionSets(Edge e)
{
    int ru, rv;

    ru = FindSet(e.v1);
    rv = FindSet(e.v2);
    if (ru != rv)
    {
        if (Z[ru].rank > Z[rv].rank)
            Z[rv].up = ru;
        else
        {
            Z[ru].up = rv;
            if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
        }
    }
}