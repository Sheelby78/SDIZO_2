#include "MacierzIncydencji.h"
#include <fstream>
#include <iomanip>
#include "Kopiec.h"
#include "Zbiory.h"

//konstruktor macierzy
MacierzIncydencji::~MacierzIncydencji() {
	delete[] A;
}

//Tworzenie losowego fragu dla alg. najkrótszej drogi
void MacierzIncydencji::createRandomD(int w, double d) {
	v = w;
	e = (d * v * (v - 1)) / 2;
	A = new Macierz * [v];

	int* X = new int[v];
	int z = e;
	int t = 0;

	for (int i = 0; i < v; i++) {
		A[i] = new Macierz[e];
		X[i] = i;
	}

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < e; j++) {
			A[i][j].id = 0;
			A[i][j].value = 0;
		}
	}

	for (int i = 0; i < v * 2; i++) {
		int temp = rand() % v;
		int temp2 = rand() % v;
		swap(X[temp], X[temp2]);
	}


	for (int i = 0; i < v - 1 && z>0; i++) {
			int temp3 = 1 + (rand() % (9));
			A[X[i]][t].id = 1;
			A[X[i]][t].value = temp3;
			A[X[i+1]][t].id = -1;
			A[X[i+1]][t].value = temp3;
			t++;
			z--;
	}
	

	for (int i = 0; i < z; i++) {
		int temp = rand() % v;
		int temp2 = rand() % v;
		int temp3 = 1 + (rand() % (9));
		if (temp2 == temp) {
			i--;
			continue;
		}
		if (isExist(temp, temp2)) {
			i--;
			continue;
		}
		else {
			A[temp][t].id = 1;
			A[temp][t].value = temp3;
			A[temp2][t].id = -1;
			A[temp2][t].value = temp3;
			t++;
		}
	}
	
}

//tworzenie losowego grafu dla alg. MST
void MacierzIncydencji::createRandomMST(int w, double d) {
	v = w;
	e = (d * v * (v - 1)) / 2;
	A = new Macierz * [v];
	int* X = new int[v];
	int z = e;
	int t = 0;

	for (int i = 0; i < v; i++) {
		A[i] = new Macierz[e*2];
		X[i] = i;
	}

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < e*2; j++) {
			A[i][j].id = 0;
			A[i][j].value = 0;
		}
	}

	for (int i = 0; i < v * 2; i++) {
		int temp = rand() % v;
		int temp2 = rand() % v;
		swap(X[temp], X[temp2]);
	}


	for (int i = 0; i < v - 1 && z>0; i++) {
		int temp3 = 1 + (rand() % (9));
		A[X[i]][t].id = 1;
		A[X[i]][t].value = temp3;
		A[X[i + 1]][t].id = -1;
		A[X[i + 1]][t].value = temp3;
		t++;

		A[X[i]][t].id = -1;
		A[X[i]][t].value = temp3;
		A[X[i + 1]][t].id = 1;
		A[X[i + 1]][t].value = temp3;
		t++;
		z--;
	}

	for (int i = 0; i < z; i++) {
		int temp = rand() % v;
		int temp2 = rand() % v;
		int temp3 = 1 + (rand() % (9));
		if (temp2 == temp) {
			i--;
			continue;
		}
		if (isExist(temp, temp2)) {
			i--;
			continue;
		}
		else {
			A[temp][t].id = 1;
			A[temp][t].value = temp3;
			A[temp2][t].id = -1;
			A[temp2][t].value = temp3;
			t++;

			A[temp][t].id = -1;
			A[temp][t].value = temp3;
			A[temp2][t].id = 1;
			A[temp2][t].value = temp3;
			t++;
		}

	}
	e *= 2;
}

//odczyt z pliku grafu 
bool MacierzIncydencji::fileRead(string name) {
	string name3 = ".txt";
	ifstream odczyt(name + name3);

	if (!odczyt.good()) {
		return false;
	}
	int v1, v2, value;
	odczyt >> e;
	odczyt >> v;
	A = new Macierz * [v];

	for (int i = 0; i < v; i++) {
		A[i] = new Macierz[e];
	}

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < e; j++) {
			A[i][j].id = 0;
			A[i][j].value = 0;
		}
	}


	for (int i = 0; i < e; i++) {
		odczyt >> v1;
		odczyt >> v2;
		odczyt >> value;
		A[v1][i].id = 1;
		A[v1][i].value = value;
		A[v2][i].id = -1;
		A[v2][i].value = value;
	}

	odczyt.close();
	return true;
}

//algorytm dijkstry
bool MacierzIncydencji::dijkstra(int start, int stop, bool show) {

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

		int temp3;

		for (int k = 0; k < e; k++) {
			if (A[u][k].id == 1) {
				for (int z = 0; z < v; z++) {
					if (A[z][k].id == -1) {
						if (!QS[z] && (d[z] > d[u] + A[z][k].value)) {
							d[z] = d[u] + A[z][k].value;
							p[z] = u;
						}
					}
				}
			}
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

//algorytm bellmana-forda
bool MacierzIncydencji::bellmanFord(int start, int stop) {
	int i, x;
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
		for (x = 0; x < v; x++) {
			for (int k = 0; k < e; k++) {
				if (A[x][k].id == 1) {
					for (int z = 0; z < v; z++) {
						if (A[z][k].id == -1) {
							if (d[z] > d[x] + A[z][k].value) {
								test = false;
								d[z] = d[x] + A[z][k].value;
								p[z] = x;
							}
						}
					}
				}
			}
		}

		if (test) return true;
	}



	for (x = 0; x < v; x++) {
		for (int k = 0; k < e; k++) {
			if (A[x][k].id == 1) {
				for (int z = 0; z < v; z++) {
					if (A[z][k].id == -1) {
						if (d[z]>d[x]+A[z][k].value) {
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}

//wywolywanie alg. bellmana-forda
bool MacierzIncydencji::showBellman(int start, int stop, bool show) {
	if (!A||start>=v||stop>=v) {
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
bool MacierzIncydencji::primMST(bool show) {
	if (!A) {
		return false;
	}
	weightMST = 0;
	Edge edg;
	int i, x;

	B = new Macierz * [v];

	for (int i = 0; i < v; i++) {
		B[i] = new Macierz[e];
	}

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < e; j++) {
			B[i][j].id = 0;
			B[i][j].value = 0;
		}
	}

	Kopiec Q(e);

	bool* visited = new bool[v];

	for (i = 0; i < v; i++)
		visited[i] = false;

	x = 0;
	visited[x] = true;

	for (i = 1; i < v; i++)
	{
		int temp3 = 0;
		for (int k = 0; k < e; k++) {
			if (A[x][k].id == 1) {
				for (int z = 0; z < v; z++) {
					if (A[z][k].id == -1) {
						if (!visited[z]) {
							temp3 = k;
							edg.v1 = x;
							edg.v2 = z;
							edg.weight = A[z][k].value;
							Q.push(edg);
						}
					}
				}
			}
		}

		do
		{
			edg = Q.front();
			Q.pop();
		} while (visited[edg.v2]);


		weightMST += edg.weight;
		B[edg.v1][temp3].id = 1;
		B[edg.v1][temp3].value = edg.weight;

		B[edg.v2][temp3].id = -1;
		B[edg.v2][temp3].value = edg.weight;


		visited[edg.v2] = true;
		x = edg.v2;
	}

	if (show) {

		cout << "       ";
		for (int i = 0; i < e; i++) cout << i << setw(6);
		cout << endl << endl;
		for (int i = 0; i < v; i++)
		{
			cout << setw(3) << i;
			for (int j = 0; j < e; j++) cout << setw(4) << (int)B[i][j].id << ":" << (int)B[i][j].value;
			cout << endl;
		}

		cout << endl << endl << "Waga MST: " << weightMST << endl;
	}

	delete[] B;
	delete[] visited;
	return true;
}

//algorytm kruskala MST
bool MacierzIncydencji::kruskalMST(bool show) {
	if (!A) {
		return false;
	}
	weightMST = 0;
	Edge edg;
	int i, x;

	Zbiory Z(v);
	Kopiec Q(e);
	B = new Macierz * [v];

	for (int i = 0; i < v; i++) {
		B[i] = new Macierz[e];
	}

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < e; j++) {
			B[i][j].id = 0;
			B[i][j].value = 0;
		}
	}

	for (i = 0; i < v; i++)
		Z.MakeSet(i);

	for (i = 0; i < v; i++)
	{
		for (int k = 0; k < e; k++) {
			if (A[i][k].id == 1) {
				for (int z = 0; z < v; z++) {
					if (A[z][k].id == -1) {
						edg.v1 = i;
						edg.v2 = z;
						edg.weight = A[z][k].value;
						Q.push(edg);
					}
				}
			}
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
		for (int k = 0; k < e; k++) {
			if (A[edg.v1][k].id == 1) {
				for (int z = 0; z < v; z++) {
					if (A[z][k].id == -1 && z==edg.v2) {
						B[edg.v1][k].id = 1;
						B[edg.v1][k].value = edg.weight;

						B[edg.v2][k].id = -1;
						B[edg.v2][k].value = edg.weight;
						k++;
						B[edg.v1][k].id = -1;
						B[edg.v1][k].value = edg.weight;

						B[edg.v2][k].id = 1;
						B[edg.v2][k].value = edg.weight;
						Z.UnionSets(edg);
					}
				}
			}
		}
	}

	if (show) {
		cout << "       ";
		for (int i = 0; i < e; i++) cout << i << setw(6);
		cout << endl << endl;
		for (int i = 0; i < v; i++)
		{
			cout << setw(3) << i;
			for (int j = 0; j < e; j++) cout << setw(4) << (int)B[i][j].id << ":" << (int)B[i][j].value;
			cout << endl;
		}

		cout << endl << endl << "Waga MST: " << weightMST << endl;
	}

	delete[] B;
	return true;
}

//wyswietlanie grafu w formie macierzowej
void MacierzIncydencji::showMatrix() {
	cout << "       ";
	for (int i = 0; i < e; i++) cout << i <<setw(6);
	cout << endl << endl;
	for (int i = 0; i < v; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < e; j++) cout << setw(4) << (int)A[i][j].id << ":" << (int)A[i][j].value;
		cout << endl;
	}
}

//sprawdzanie czy podnana krawêdz istnieje
bool MacierzIncydencji::isExist(int x, int y) {

	for (int k = 0; k < e; k++) {
		if (A[x][k].id == 1) {
			for (int z = 0; z < v; z++) {
				if (A[z][k].id == -1 && z==y) {
					return true;
				}
			}
		}
	}

	return false;
}