#pragma once
#include <iostream>
#include <string>
using namespace std;

class ListaSasiedztwa {

	struct Lista {
		Lista* next;
		int value;
		int id;
	};

private:
	int v, e, *S, *p, *d, weightMST;
	Lista** A, **B;
	Lista* pw, *rw;
	bool* QS;

	const int MAXINT = 1000000;


public:
	~ListaSasiedztwa();
	bool primMST(bool show);
	bool kruskalMST(bool show);
	bool showBellman(int start, int stop, bool show);
	bool bellmanFord(int start, int stop);
	bool dijkstra(int start, int stop, bool show);
	void createRandomD(int w, double d);
	void createRandomMST(int w, double d);
	bool fileRead(string name);
	void showList();
	bool isExist(int x, int y);
};