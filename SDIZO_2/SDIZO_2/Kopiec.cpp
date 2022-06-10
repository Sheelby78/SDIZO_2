#include "Kopiec.h"


Kopiec::Kopiec(int n)
{
    Heap = new Edge[n];
    hpos = 0;
}

// Destruktor - usuwa kopiec z pamiêci
Kopiec::~Kopiec()
{
    delete[] Heap;
}

// Zwraca krawêdŸ z pocz¹tku kopca
Edge Kopiec::front()
{
    return Heap[0];
}

// Umieszcza w kopcu now¹ krawêdŸ i odtwarza strukturê kopca
void Kopiec::push(Edge e)
{
    int i, j;

    i = hpos++;                    
    j = (i - 1) >> 1;

    while (i && (Heap[j].weight > e.weight))
    {
        Heap[i] = Heap[j];
        i = j;
        j = (i - 1) >> 1;
    }

    Heap[i] = e;    
}

// Usuwa korzeñ z kopca i odtwarza jego strukturê
void Kopiec::pop()
{
    int i, j;
    Edge e;

    if (hpos)
    {
        e = Heap[--hpos];

        i = 0;
        j = 1;

        while (j < hpos)
        {
            if ((j + 1 < hpos) && (Heap[j + 1].weight < Heap[j].weight)) j++;
            if (e.weight <= Heap[j].weight) break;
            Heap[i] = Heap[j];
            i = j;
            j = (j << 1) + 1;
        }

        Heap[i] = e;
    }
}