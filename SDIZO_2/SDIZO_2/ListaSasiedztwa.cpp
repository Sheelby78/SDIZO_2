#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "ListaSasiedztwa.h"
#include <iomanip>
#include "Kopiec.h"
#include "Zbiory.h"

using namespace std;
//Konstruktor listy
ListaSasiedztwa::~ListaSasiedztwa() {
	for (int i = 0; i < v; i++)
	{
		pw = A[i];
		while (pw)
		{
			rw = pw;
			pw = pw->next;
			delete rw;
		}
	}

	delete[] A;
}

//Tworzenie losowego fragu dla alg. najkrótszej drogi
void ListaSasiedztwa::createRandomD(int w, double d) {
	v = w;
	e = (d * v * (v - 1)) / 2;
	A = new Lista * [v];

	int* X = new int[v];
	int z = e;

	for (int i = 0; i < v; i++) {
		A[i] = NULL;
		X[i] = i;
	}

	for (int i = 0; i < v * 2; i++) {
		int temp = rand() % v;
		int temp2 = rand() % v;
		swap(X[temp], X[temp2]);
	}


	for (int i = 0; i < v - 1 && z>0; i++) {
		int temp3 = 1 + (rand() % (20));
		pw = new Lista;
		pw->id = X[i + 1];
		pw->value = temp3;
		pw->next = A[X[i]];
		A[X[i]] = pw;
		z--;
	}

	for (int i = 0; i < z; i++ ) {
		int temp = rand() % v;
		int temp2 = rand() % v;
		int temp3 = 1 + (rand() % (20));
		if (temp2 == temp) {
			i--;
			continue;
		}
		if (isExist(temp, temp2)) {
			i--;
			continue;
		}
		else {
			pw = new Lista;
			pw->id = temp2;
			pw->value = temp3;
			pw->next = A[temp];
			A[temp] = pw;
		}
		
	}
}

//tworzenie losowego grafu dla alg. MST
void ListaSasiedztwa::createRandomMST(int w, double d) {
	v = w;
	e = (d * v * (v - 1)) / 2;
	A = new Lista * [v];
	int* X = new int[v];
	int z = e;

	for (int i = 0; i < v; i++) {
		A[i] = NULL;
		X[i] = i;
	}

	for (int i = 0; i < v*2; i++) {
		int temp = rand() % v;
		int temp2 = rand() % v;
		swap(X[temp], X[temp2]);
	}


	for (int i = 0; i < v - 1 && z>0; i++) {
		int temp3 = 1 + (rand() % (20));
		pw = new Lista;
		pw->id = X[i+1];
		pw->value = temp3;
		pw->next = A[X[i]];
		A[X[i]] = pw;

		pw = new Lista;
		pw->id = X[i];
		pw->value = temp3;
		pw->next = A[X[i+1]];
		A[X[i+1]] = pw;
		z--;
	}

	for (int i = 0; i < z; i ++) {
		int temp = rand() % v;
		int temp2 = rand() % v;
		int temp3 = 1 + (rand() % (20));
		if (temp2 == temp) {
			i--;
			continue;
		}
		if (isExist(temp, temp2)) {
			i--;
			continue;
		}
		else {
			pw = new Lista;
			pw->id = temp2;
			pw->value = temp3;
			pw->next = A[temp];
			A[temp] = pw;

			pw = new Lista;
			pw->id = temp;
			pw->value = temp3;
			pw->next = A[temp2];
			A[temp2] = pw;
		}

	}
	e *= 2;
}

//odczyt z pliku grafów
bool ListaSasiedztwa::fileRead(string name) {

	string name3 = ".txt";
	ifstream odczyt(name + name3);

	if (!odczyt.good()) {
		return false;
	}
	int v1, v2, value;
	odczyt >> e;
	odczyt >> v;
	A = new Lista * [v];

	for (int i = 0; i < v; i++) {
		A[i] = NULL;
	}


	for (int i = 0; i < e; i++) {
		odczyt >> v1;
		odczyt >> v2;
		odczyt >> value;
		pw = new Lista;
		pw->id = v2;
		pw->value = value;
		pw->next = A[v1];
		A[v1] = pw;
	}

	odczyt.close();
	return true;
}

//algorytm dijkstry
bool ListaSasiedztwa::dijkstra(int start, int stop, bool show) {
	
	if (!A || start >= v || stop >= v) {
		return false;
	}

	d = new int[v];
	p = new int[v];
	QS = new bool[v];
	S = new int[v];
	int sptr = 0;
	int j, u, i;

	for (i = 0; i < v; i++)
	{
		d[i] = MAXINT;
		p[i] = -1;
		QS[i] = false;
	}

	d[start] = 0;

	for (i = 0; i < v; i++)
	{

		for (j = 0; QS[j]; j++);
		for (u = j++; j < v; j++)
			if (!QS[j] && (d[j] < d[u])) u = j;

		QS[u] = true;


		for (pw = A[u]; pw; pw = pw->next)
			if (!QS[pw->id] && (d[pw->id] > d[u] + pw->value))
			{
				d[pw->id] = d[u] + pw->value;
				p[pw->id] = u;
			}
	}

	if (show) {
		for (j = stop; j > -1; j = p[j]) {
			S[sptr] = j;
			sptr++;
		}
		cout << S[sptr - 1];
		sptr -= 2;

		for (; sptr >= 0; sptr--) {
			cout << " -> " << S[sptr];
		}

		cout << "  Droga: " << d[stop] << endl;
	}

	delete[] d;
	delete[] p;
	delete[] QS;
	delete[] S;
	return true;

}

//alg. bellmana-forda
bool ListaSasiedztwa::bellmanFord(int start, int stop) {

	int i,x;
	bool test;
	d = new int[v];
	p = new int[v];
	for (i = 0; i < v; i++)
	{
		d[i] = MAXINT;
		p[i] = -1;
	}

	d[start] = 0; 

	for (i = 1; i < v; i++)  
	{
		test = true;             
		for (x = 0; x < v; x++)
			for (pw = A[x]; pw; pw = pw->next) 
				if (d[pw->id] > d[x] + pw->value) 
				{
					test = false;      
					d[pw->id] = d[x] + pw->value; 
					p[pw->id] = x;   
				}
		if (test) return true;  
	}

	

	for (x = 0; x < v; x++)
		for (pw = A[x]; pw; pw = pw->next)
			if (d[pw->id] > d[x] + pw->value) return false;

	return true;
}

//alg. bellmana-forda wywolanie 
bool ListaSasiedztwa::showBellman(int start, int stop, bool show) {

	if (!A || start >= v || stop >= v) {
		return false;
	}

	int sptr = 0;
	int j;
	if (bellmanFord(start, stop))
	{
		if (show) {
			S = new int[v];
			for (j = stop; j > -1; j = p[j]) {
				S[sptr] = j;
				sptr++;
			}
			cout << S[sptr - 1];
			sptr -= 2;

			for (; sptr >= 0; sptr--) {
				cout << " -> " << S[sptr];
			}

			cout << "  Droga: " << d[stop] << endl;
			delete[] S;
		}
		delete[] p;
		delete[] d;
	}
	else return false;
	return true;
}

//algorytm prima MST
bool ListaSasiedztwa::primMST(bool show) {

	if (!A) {
		return false;
	}

	weightMST = 0;
	Edge edg;
	int i,x;

	B = new Lista * [v];
	for (int i = 0; i < v; i++) B[i] = NULL;

	Kopiec Q(e);

	bool* visited = new bool[v];

	for (i = 0; i < v; i++)
		visited[i] = false;

	x = 0;                     
	visited[x] = true;

	for (i = 1; i < v; i++) 
	{
		for (pw = A[x]; pw; pw = pw->next) 
			if (!visited[pw->id])
			{
				edg.v1 = x; 
				edg.v2 = pw->id;
				edg.weight = pw->value;
				Q.push(edg);
			}

		do
		{
			edg = Q.front(); 
			Q.pop();
		} while (visited[edg.v2]);


		weightMST += edg.weight;
		rw = new Lista;
		rw->id = edg.v2;
		rw->value = edg.weight; 
		rw->next = B[edg.v1]; 
		B[edg.v1] = rw;

		rw = new Lista;
		rw->id = edg.v1; 
		rw->value = edg.weight;
		rw->next = B[edg.v2]; 
		B[edg.v2] = rw;

		visited[edg.v2] = true;
		x = edg.v2;
	}

	if(show){
	for (i = 0; i <= (v - 1); i++)
	{
		cout << "Wierzcholek [" << i << "] - ";
		for (pw = B[i]; pw; pw = pw->next) cout << pw->id << ":" << pw->value << " ";
		cout << endl;
	}
	cout << endl << endl << "Waga MST: " << weightMST << endl;
	}
	
	delete[] visited;
	delete[] B;
	return true;
}

//alg. kruskala MST
bool ListaSasiedztwa::kruskalMST(bool show) {

	if (!A) {
		return false;
	}

	weightMST = 0;
	Edge edg;
	int i, x;

	B = new Lista * [v];
	for (int i = 0; i < v; i++) B[i] = NULL;

	Zbiory Z(v);
	Kopiec Q(e);

	for (i = 0; i < v; i++)
		Z.MakeSet(i);

	for (i = 0; i < v; i++)
	{
		pw = A[i];
		while (pw) {
			edg.v1 = i;
			edg.v2 = pw->id;
			edg.weight = pw->value;
			pw = pw->next;
			Q.push(edg);
		}          
	}

	for (i = 1; i < v; i++)
	{
		do
		{
			edg = Q.front();
			Q.pop();
		} while (Z.FindSet(edg.v1) == Z.FindSet(edg.v2));
		
		weightMST += edg.weight;
		rw = new Lista; 
		rw->id = edg.v2;
		rw->value = edg.weight;
		rw->next = B[edg.v1];
		B[edg.v1] = rw;

		rw = new Lista;
		rw->id = edg.v1;
		rw->value = edg.weight;
		rw->next = B[edg.v2];
		B[edg.v2] = rw;
		Z.UnionSets(edg);
	}

	if (show) {
		for (i = 0; i <= (v - 1); i++)
		{
			cout << "Wierzcholek [" << i << "] - ";
			for (pw = B[i]; pw; pw = pw->next) cout << pw->id << ":" << pw->value << " ";
			cout << endl;
		}
		cout << endl << endl << "Waga MST: " << weightMST << endl;
	}
	delete[] B;
	return true;
}

//Wyswietlanie listy 
void ListaSasiedztwa::showList() {
	for (int i = 0; i < v; i++)
	{
		cout << "Wierzcholek [" << i <<"] - ";
		pw = A[i];
		while (pw)
		{
			cout << setw(3) << pw->id << ":"<<pw->value;
			pw = pw->next;
		}
		cout << endl;
	}
}

//sprawdzanie czy podana krawedz istnieje
bool ListaSasiedztwa::isExist(int x, int y) {

	pw = A[x];
	while (pw) {
		if (pw->id == y) {
			return true;
		}
		pw = pw->next;
	}

	return false;
}