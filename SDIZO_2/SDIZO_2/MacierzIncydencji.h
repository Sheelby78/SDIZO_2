#pragma once
#include <iostream>
#include <string>

using namespace std;

class MacierzIncydencji{
	struct Macierz {
		int value;
		int id;
	};
private:
	int v, e, * S, * p, * d, weightMST;
	Macierz** A, **B;
	bool* QS;

	const int MAXINT = 1000000;


public:
	~MacierzIncydencji();
	bool primMST(bool show);
	bool kruskalMST(bool show);
	bool showBellman(int start, int stop, bool show);
	bool bellmanFord(int start, int stop);
	bool dijkstra(int start, int stop, bool show);
	void createRandomD(int w, double d);
	void createRandomMST(int w, double d);
	bool fileRead(string name);
	void showMatrix();
	bool isExist(int x, int y);
};