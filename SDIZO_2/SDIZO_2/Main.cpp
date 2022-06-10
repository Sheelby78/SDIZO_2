#include <iostream>
#include "ListaSasiedztwa.h"
#include "MenuTesty.h"
#include "MacierzIncydencji.h"

using namespace std;

void menuMacierz();
void menuLista();

//menu glowne programu
int main()
{
	srand(time(NULL));
	bool koniec = false;
	char wybor;
	while (!koniec) {
		cout << " MENU GLOWNE " << endl;
		cout << "---------------------------" << endl;
		cout << "1.  Reprezentacja Macierzowa" << endl;
		cout << "2.  Reprezentacja Listowa" << endl;
		cout << "x.  Zamkniecie programu " << endl;
		cout << "---------------------------" << endl;
		cout << "Wybor: ";
		cin >> wybor;

		switch (wybor)
		{
		case '1':;	system("cls");  menuMacierz();  break;
		case '2':;	system("cls");  menuLista(); break;
		case 'x':;	koniec = true; break;
		default:	system("cls"); cout << endl << "POMYLKA!" << endl << endl;
		}
	}
}

//menu dla macierzy
void menuMacierz() {
		MacierzIncydencji mc = *(new MacierzIncydencji());
		MenuTesty tst = *(new MenuTesty());
		bool koniec = false;
		char wybor;
		while (!koniec) {
			cout << " MENU MACIERZY " << endl;
			cout << "---------------------------" << endl;
			cout << "1.  MST - algorytm Prima" << endl;
			cout << "2.  MST - algorytm Kruskala" << endl;
			cout << "3.  Najkrotsza sciezka - Dijkstra" << endl;
			cout << "4.  Najkrotsza sciezka - Bellman-Ford" << endl;
			cout << "5.  Wczytanie z pliku" << endl;
			cout << "6.  Wygeneruj graf dla najkrotszej siezki" << endl;
			cout << "7.  Wygeneruj graf dla MST" << endl;
			cout << "s.  Wyswietl graf w postaci macierzy" << endl;
			cout << "t.  Testowanie" << endl;
			cout << "x.  Powrot " << endl;
			cout << "---------------------------" << endl;
			cout << "Wybor: ";
			cin >> wybor;

			switch (wybor)
			{
			case '1': {
				system("cls");
				cout << endl;
				if (!mc.primMST(true)) {
					cout << "Nie znaleziono grafu" << endl;
				}
				cout << endl << endl;
				break;
			}
			case '2': {
				system("cls");
				cout << endl;
				if (!mc.kruskalMST(true)) {
					cout << "Nie znaleziono grafu" << endl;
				}
				cout << endl << endl;
				break;
			}
			case '3': {
				system("cls");
				cout << endl;
				int start, stop;
				cout << "Podaj wierzcholek poczatkowy: ";
				cin >> start;
				cout << endl;
				cout << "Podaj wierzcholek koncowy: ";
				cin >> stop;
				if (start < 0 || stop < 0) {
					cout << endl << "Bledne dane wejsciowe" << endl<<endl;
					break;
				}
				cout << endl;
				if (!mc.dijkstra(start, stop, true)) {
					cout << " Blad wykonania algorytmu " << endl;
				}
				cout << endl;
				break;
			}
			case '4': {
				system("cls");
				cout << endl;
				int start, stop;
				cout << "Podaj wierzcholek poczatkowy: ";
				cin >> start;
				cout << endl;
				cout << "Podaj wierzcholek koncowy: ";
				cin >> stop;
				if (start < 0 || stop < 0) {
					cout << endl << "Bledne dane wejsciowe" << endl << endl;
					break;
				}
				cout << endl;
				if (!mc.showBellman(start, stop, true)) {
					cout << " Blad wykonania algorytmu " << endl;
				}
				cout << endl;
				break;
			}
			case '5': {
				system("cls");
				cout << endl;
				string name;
				cout << "Podaj nazwe pliku bez rozszerzenia(.txt): ";
				cin >> name;
				if (mc.fileRead(name)) {
					cout << endl << "Pomyslnie wczytano dane z pliku: " << name << ".txt" << endl << endl;
				}
				else {
					cout << endl << "Blad odczytu pliku" << endl << endl;
				}
				break;
			}
			case '6': {
				system("cls");
				cout << endl;
				int v;
				double d;
				cout << "Podaj liczbe wierzcholkow: ";
				cin >> v;
				cout << endl;
				cout << "Podaj gestosc grafu: ";
				cin >> d;
				cout << endl;
				mc.createRandomD(v, d);
				mc.showMatrix();
				cout << endl << endl;
				break;
			}
			case '7': {
				system("cls");
				cout << endl;
				int v;
				double d;
				cout << "Podaj liczbe wierzcholkow: ";
				cin >> v;
				cout << endl;
				cout << "Podaj gestosc grafu: ";
				cin >> d;
				cout << endl;
				mc.createRandomMST(v, d);
				mc.showMatrix();
				cout << endl << endl;
				break;
			}
			case 's': {
				system("cls");
				cout << endl;
				mc.showMatrix();
				cout << endl << endl;
				break;
			}
			case 't': {
				system("cls");
				tst.testyMacierz();
				break;
			}
			case 'x':;	system("cls");  koniec = true; break;
			default:	system("cls"); cout << endl << "POMYLKA!" << endl << endl;
			}
		}
}

//menu dla listy
void menuLista() {
	ListaSasiedztwa ls = *(new ListaSasiedztwa());
	MenuTesty tst = *(new MenuTesty());
	bool koniec = false;
	char wybor;
	while (!koniec) {
		cout << " MENU LISTY " << endl;
		cout << "---------------------------" << endl;
		cout << "1.  MST - algorytm Prima" << endl;
		cout << "2.  MST - algorytm Kruskala" << endl;
		cout << "3.  Najkrotsza sciezka - Dijkstra" << endl;
		cout << "4.  Najkrotsza sciezka - Bellman-Ford" << endl;
		cout << "5.  Wczytanie z pliku" << endl;
		cout << "6.  Wygeneruj graf dla najkrotszej siezki" << endl;
		cout << "7.  Wygeneruj graf dla MST" << endl;
		cout << "s.  Wyswietl graf w postaci listy" << endl;
		cout << "t.  Testowanie" << endl;
		cout << "x.  Powrot " << endl;
		cout << "---------------------------" << endl;
		cout << "Wybor: ";
		cin >> wybor;

		switch (wybor)
		{
		case '1': {
			system("cls");
			cout << endl;
			if (!ls.primMST(true)) {
				cout << "Nie znaleziono grafu" << endl;
			}
			cout << endl << endl;
			break;
		}
		case '2': {
			system("cls");
			cout << endl;
			if (!ls.kruskalMST(true)) {
				cout << "Nie znaleziono grafu" << endl;
			}
			cout << endl << endl;
			break;
		}
		case '3': {
			system("cls");
			cout << endl;
			int start, stop;
			cout << "Podaj wierzcholek poczatkowy: ";
			cin >> start;
			cout << endl;
			cout << "Podaj wierzcholek koncowy: ";
			cin >> stop;
			if (start < 0 || stop < 0) {
				cout << endl << "Bledne dane wejsciowe" << endl << endl;
				break;
			}
			cout << endl;
			if (!ls.dijkstra(start, stop, true)) {
				cout << " Blad wykonania algorytmu " << endl;
			}
			cout << endl;
			break;
		}
		case '4': {
			system("cls");
			cout << endl;
			int start, stop;
			cout << "Podaj wierzcholek poczatkowy: ";
			cin >> start;
			cout << endl;
			cout << "Podaj wierzcholek koncowy: ";
			cin >> stop;
			if (start < 0 || stop < 0) {
				cout << endl << "Bledne dane wejsciowe" << endl << endl;
				break;
			}
			cout << endl;
			if (!ls.showBellman(start, stop, true)) {
				cout << " Blad wykonania algorytmu " << endl;
			}
			cout << endl;
			break;
		}
		case '5': {
			system("cls");
			cout << endl;
			string name;
			cout << "Podaj nazwe pliku bez rozszerzenia(.txt): ";
			cin >> name;
			if (ls.fileRead(name)) {
				cout << endl << "Pomyslnie wczytano dane z pliku: " << name << ".txt" << endl << endl;
			}
			else {
				cout << endl << "Blad odczytu pliku" << endl << endl;
			}
			break;
		}
		case '6': {
			system("cls");
			cout << endl;
			int v;
			double d;
			cout << "Podaj liczbe wierzcholkow: ";
			cin >> v;
			cout << endl;
			cout << "Podaj gestosc grafu: ";
			cin >> d;
			cout << endl;
			ls.createRandomD(v, d);
			ls.showList();
			cout << endl << endl;
			break;
		}
		case '7': {
			system("cls");
			cout << endl;
			int v;
			double d;
			cout << "Podaj liczbe wierzcholkow: ";
			cin >> v;
			cout << endl;
			cout << "Podaj gestosc grafu: ";
			cin >> d;
			cout << endl;
			ls.createRandomMST(v, d);
			ls.showList();
			cout << endl << endl;
			break;
		}
		case 't': {
			system("cls");
			tst.testyLista();
			break;
		}
		case 's': {
			system("cls");
			cout << endl;
			ls.showList();
			cout << endl << endl;
			break;
		}
		case 'x':;	system("cls");  koniec = true; break;
		default:	system("cls"); cout << endl << "POMYLKA!" << endl << endl;
		}
	}
}

