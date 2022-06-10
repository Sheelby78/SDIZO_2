#include "MenuTesty.h"
#include "Timer.h"

//testy na liscie
void MenuTesty::testyLista() {
	bool koniec = false;
	Timer test = *(new Timer());
	while (!koniec) {
		char wybor;
		cout << " TESTOWANIE LISTY " << endl;
		cout << "---------------------------" << endl;
		cout << "1.  MST - algorytm Prima" << endl;
		cout << "2.  MST - algorytm Kruskala" << endl;
		cout << "3.  Najkrotsza sciezka - Dijkstra" << endl;
		cout << "4.  Najkrotsza sciezka - Bellman-Ford" << endl;
		cout << "x.  Powrot" << endl;
		cout << "---------------------------" << endl;
		cout << "Wybor: ";
		cin >> wybor;

		switch (wybor)
		{

		case '1': {
			system("cls");
			long count = 0;
			int v;
			double d;

			cout << endl << "Podaj ilosc wierzcholkow: ";
			cin >> v;
			cout << endl << "Podaj gestosc grafu: ";
			cin >> d;

			for (int i = 0; i < 50; i++) {
				ListaSasiedztwa lss = *(new ListaSasiedztwa());
				lss.createRandomMST(v,d);
				test.start();
				lss.primMST(false);
				test.stop();
				count += test.timeCount();
			}

			cout << endl << "Sredni czas wykonania algorytmu MST Prima: " << count / 50 << endl << endl;
			break;
		}
		case '2': {
			system("cls");
			long count = 0;
			int v;
			double d;

			cout << endl << "Podaj ilosc wierzcholkow: ";
			cin >> v;
			cout << endl << "Podaj gestosc grafu: ";
			cin >> d;

			for (int i = 0; i < 50; i++) {
				ListaSasiedztwa lss = *(new ListaSasiedztwa());
				lss.createRandomMST(v,d);
				test.start();
				lss.kruskalMST(false);
				test.stop();
				count += test.timeCount();
			}

			cout << endl << "Sredni czas wykonania algorytmu MST Kruskala: " << count / 50 << endl << endl;
			break;
		}
		case '3': {
			system("cls");
			long count = 0;
			int v, v1, v2;
			double d;

			cout << endl << "Podaj ilosc wierzcholkow: ";
			cin >> v;
			cout << endl << "Podaj gestosc grafu: ";
			cin >> d;

			v1 = 0;
			v2 = v - 1;

			for (int i = 0; i < 50; i++) {
				ListaSasiedztwa lss = *(new ListaSasiedztwa());
				lss.createRandomD(v, d);
				test.start();
				lss.dijkstra(v1,v2,false);
				test.stop();
				count += test.timeCount();
			}

			cout << endl << "Sredni czas wykonania algorytmu najkrotszej drogi Dijkstry: " << count / 50 << endl << endl;
			break;
		}
		case '4': {
			system("cls");
			long count = 0;
			int v, v1, v2;
			double d;

			cout << endl << "Podaj ilosc wierzcholkow: ";
			cin >> v;
			cout << endl << "Podaj gestosc grafu: ";
			cin >> d;

			v1 = 0;
			v2 = v - 1;

			for (int i = 0; i < 50; i++) {
				ListaSasiedztwa lss = *(new ListaSasiedztwa());
				lss.createRandomD(v, d);
				test.start();
				lss.showBellman(v1, v2, false);
				test.stop();
				count += test.timeCount();
			}

			cout << endl << "Sredni czas wykonania algorytmu najkrotszej drogi Bellmana-Forda: " << count / 50 << endl << endl;
			break;
		}
		

		case 'x': {
			system("cls");
			koniec = true;
			break;
		}

		
		default: {
			system("cls");
			cout << endl << "POMYLKA!" << endl << endl;
			break;
		}
		}
	}
}

//testy na macierzy
void MenuTesty::testyMacierz() {
	bool koniec = false;
	MacierzIncydencji mcc = *(new MacierzIncydencji());
	Timer test = *(new Timer());
	while (!koniec) {
		char wybor;
		cout << " TESTOWANIE MACIERZY " << endl;
		cout << "---------------------------" << endl;
		cout << "1.  MST - algorytm Prima" << endl;
		cout << "2.  MST - algorytm Kruskala" << endl;
		cout << "3.  Najkrotsza sciezka - Dijkstra" << endl;
		cout << "4.  Najkrotsza sciezka - Bellman-Ford" << endl;
		cout << "x.  Powrot" << endl;
		cout << "---------------------------" << endl;
		cout << "Wybor: ";
		cin >> wybor;

		switch (wybor)
		{

		case '1': {
			system("cls");
			long count = 0;
			int v;
			double d;

			cout << endl << "Podaj ilosc wierzcholkow: ";
			cin >> v;
			cout << endl << "Podaj gestosc grafu: ";
			cin >> d;
			for (int i = 0; i < 50; i++) {
				mcc.createRandomMST(v, d);
				test.start();
				mcc.primMST(false);
				test.stop();
				count += test.timeCount();
			}

			cout << endl << "Sredni czas wykonania algorytmu MST Prima: " << count / 50 << endl << endl;
			break;
		}
		case '2': {
			system("cls");
			long count = 0;
			int v;
			double d;

			cout << endl << "Podaj ilosc wierzcholkow: ";
			cin >> v;
			cout << endl << "Podaj gestosc grafu: ";
			cin >> d;

			for (int i = 0; i < 50; i++) {
				//MacierzIncydencji mcc = *(new MacierzIncydencji());
				mcc.createRandomMST(v, d);
				test.start();
				mcc.kruskalMST(false);
				test.stop();
				count += test.timeCount();
			}

			cout << endl << "Sredni czas wykonania algorytmu MST Kruskala: " << count / 50 << endl << endl;
			break;
		}
		case '3': {
			system("cls");
			long count = 0;
			int v, v1, v2;
			double d;

			cout << endl << "Podaj ilosc wierzcholkow: ";
			cin >> v;
			cout << endl << "Podaj gestosc grafu: ";
			cin >> d;

			v1 = 0;
			v2 = v - 1;

			for (int i = 0; i < 50; i++) {
				//MacierzIncydencji mcc = *(new MacierzIncydencji());
				mcc.createRandomD(v, d);
				test.start();
				mcc.dijkstra(v1, v2, false);
				test.stop();
				count += test.timeCount();
			}

			cout << endl << "Sredni czas wykonania algorytmu najkrotszej drogi Dijkstry: " << count / 50 << endl << endl;
			break;
		}
		case '4': {
			system("cls");
			long count = 0;
			int v, v1, v2;
			double d;

			cout << endl << "Podaj ilosc wierzcholkow: ";
			cin >> v;
			cout << endl << "Podaj gestosc grafu: ";
			cin >> d;

			v1 = 0;
			v2 = v - 1;

			for (int i = 0; i < 50; i++) {
				//MacierzIncydencji mcc = *(new MacierzIncydencji());
				mcc.createRandomD(v, d);
				test.start();
				mcc.showBellman(v1, v2, false);
				test.stop();
				count += test.timeCount();
			}

			cout << endl << "Sredni czas wykonania algorytmu najkrotszej drogi Bellmana-Forda: " << count / 50 << endl << endl;
			break;
		}


		case 'x': {
			system("cls");
			koniec = true;
			break;
		}


		default: {
			system("cls");
			cout << endl << "POMYLKA!" << endl << endl;
			break;
		}
		}
	}
}