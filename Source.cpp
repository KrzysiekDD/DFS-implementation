// Damian Kakol 184890 i Krzysztof Dymanowski 184836 ACiR 3 IDE: Microsoft Visual Studio / JetBrains Clion 
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

const int Wymiar8 = 8;
const int Wymiar4 = 4;
const int Wymiar40 = 40;
const int Wymiar20 = 20;

//definicje dla preprocesora

#define BialePole char(219);
#define CzarnePole char(255);
#define Robocik char(167);
#define CLS system("cls");
#define PAUSE system("pause");

//struktura wierzcholka grafu, czyli jednokierunkowa lista

struct Wierzcholek {
	Wierzcholek* next;
	int numerwierzcholka;
};
void MenuGlowne();
void DrogaRobota();
void PiszMenu(int Numer);
void OprawaGraficzna(int n);
void WypiszWierzcholki(Wierzcholek**& TablicaList);
void WypiszPlansze(int MacierzGrafu[Wymiar40][Wymiar20]);
void WypiszPlansze(int MacierzGrafu[Wymiar40][Wymiar20]);
void WypiszMacierz(char MacierzSegmentow[Wymiar8][Wymiar4]);
void WypiszDroge(int Kolejnosc[Wymiar40 * Wymiar20], int koncowy);
void GenerujMacierzSegmentow(char MacierzSegmentow[Wymiar8][Wymiar4]);
void WypelnienieSegmentu(int MacierzGrafu[Wymiar40][Wymiar20], int Segment, int w, int k);
void StworzMacierzPlanszy(char MacierzSegmentow[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20]);
void InicjalizacjaListy(int MacierzGrafu[Wymiar40][Wymiar20], Wierzcholek**& TablicaList, bool*& visited);
void DefinicjaSegmentu(char MacierzSegmentow[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20], int w, int k);
bool DFS(Wierzcholek**& TablicaList, bool*& visited, int startowy, int koncowy, int MacierzGrafu[Wymiar40][Wymiar20]);
void UtworzSasiada(int MacierzGrafu[Wymiar40][Wymiar20], Wierzcholek**& TablicaList, const char Kierunek, int row, int column);

/*
Minimum mimorum oprawy graficznej dla programu
*/
void OprawaGraficzna(int n)
{
	switch (n)
	{
	case 1: cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n";
		break;
	case 2: cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
		break;
	case 3: cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
		break;
	}
}
/*
Stworzenie planszy zlozonej z segmentow A do F
*/
void GenerujMacierzSegmentow(char MacierzSegmentow[Wymiar8][Wymiar4])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
			MacierzSegmentow[i][j] = char(rand() % 6 + 65);
}
/*
Wypisanie planszy segmentow
*/
void WypiszMacierz(char MacierzSegmentow[Wymiar8][Wymiar4])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << setw(3) << MacierzSegmentow[i][j];
		}
		cout << "\n";
	}
}
/*
Stworzenie rzeczywistej planszy, na podstawie ktorej tworzona jest lista lub wyswietlana jest droga robota
*/
void StworzMacierzPlanszy(char MacierzSegmentow[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20])
{
	for (int w = 0; w < Wymiar8; w++)
		for (int k = 0; k < Wymiar4; k++)
		{
			DefinicjaSegmentu(MacierzSegmentow, MacierzGrafu, w, k);
		}
}
/*
Funkcja pomocnicza w tworzeniu planszy
*/
void DefinicjaSegmentu(char MacierzSegmentow[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20], int w, int k)
{
	int var = int((MacierzSegmentow[w][k]) - 64);
	switch (var)
	{
	case 1: WypelnienieSegmentu(MacierzGrafu, 1, w, k);
		break;
	case 2: WypelnienieSegmentu(MacierzGrafu, 2, w, k);
		break;
	case 3: WypelnienieSegmentu(MacierzGrafu, 3, w, k);
		break;
	case 4: WypelnienieSegmentu(MacierzGrafu, 4, w, k);
		break;
	case 5: WypelnienieSegmentu(MacierzGrafu, 5, w, k);
		break;
	case 6: WypelnienieSegmentu(MacierzGrafu, 6, w, k);
		break;
	}
}
/*
Recznie wpisane kombinacje segmentow planszy
*/
void WypelnienieSegmentu(int MacierzGrafu[Wymiar40][Wymiar20], int Segment, int w, int k)
{
	int r = w;
	int c = k;
	switch (Segment)
	{
	case 1: {
		MacierzGrafu[r * 5][c * 5] = 0; MacierzGrafu[r * 5][(c * 5) + 1] = 0; MacierzGrafu[r * 5][(c * 5) + 2] = 1; MacierzGrafu[r * 5][(c * 5) + 3] = 0; MacierzGrafu[r * 5][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 1][c * 5] = 0; MacierzGrafu[(r * 5) + 1][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 3] = 0; MacierzGrafu[(r * 5) + 1][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 2][c * 5] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 2] = 0; MacierzGrafu[(r * 5) + 2][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 4] = 1;
		MacierzGrafu[(r * 5) + 3][c * 5] = 0; MacierzGrafu[(r * 5) + 3][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 4][c * 5] = 0; MacierzGrafu[(r * 5) + 4][(c * 5) + 1] = 0; MacierzGrafu[(r * 5) + 4][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 3] = 0; MacierzGrafu[(r * 5) + 4][(c * 5) + 4] = 0;
		break;
	}
	case 2: {
		MacierzGrafu[r * 5][c * 5] = 0; MacierzGrafu[r * 5][(c * 5) + 1] = 0; MacierzGrafu[r * 5][(c * 5) + 2] = 1; MacierzGrafu[r * 5][(c * 5) + 3] = 1; MacierzGrafu[r * 5][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 1][c * 5] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 1] = 0; MacierzGrafu[(r * 5) + 1][(c * 5) + 2] = 0; MacierzGrafu[(r * 5) + 1][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 2][c * 5] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 4] = 1;
		MacierzGrafu[(r * 5) + 3][c * 5] = 0; MacierzGrafu[(r * 5) + 3][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 4][c * 5] = 0; MacierzGrafu[(r * 5) + 4][(c * 5) + 1] = 0; MacierzGrafu[(r * 5) + 4][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 4] = 0;
		break;
	}
	case 3: {
		MacierzGrafu[r * 5][c * 5] = 1; MacierzGrafu[r * 5][(c * 5) + 1] = 1; MacierzGrafu[r * 5][(c * 5) + 2] = 1; MacierzGrafu[r * 5][(c * 5) + 3] = 1; MacierzGrafu[r * 5][(c * 5) + 4] = 1;
		MacierzGrafu[(r * 5) + 1][c * 5] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 2] = 0; MacierzGrafu[(r * 5) + 1][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 4] = 1;
		MacierzGrafu[(r * 5) + 2][c * 5] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 2] = 0; MacierzGrafu[(r * 5) + 2][(c * 5) + 3] = 0; MacierzGrafu[(r * 5) + 2][(c * 5) + 4] = 1;
		MacierzGrafu[(r * 5) + 3][c * 5] = 0; MacierzGrafu[(r * 5) + 3][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 2] = 0; MacierzGrafu[(r * 5) + 3][(c * 5) + 3] = 0; MacierzGrafu[(r * 5) + 3][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 4][c * 5] = 0; MacierzGrafu[(r * 5) + 4][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 4] = 1;
		break;
	}
	case 4: {
		MacierzGrafu[r * 5][c * 5] = 0; MacierzGrafu[r * 5][(c * 5) + 1] = 0; MacierzGrafu[r * 5][(c * 5) + 2] = 1; MacierzGrafu[r * 5][(c * 5) + 3] = 1; MacierzGrafu[r * 5][(c * 5) + 4] = 1;
		MacierzGrafu[(r * 5) + 1][c * 5] = 0; MacierzGrafu[(r * 5) + 1][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 3] = 0; MacierzGrafu[(r * 5) + 1][(c * 5) + 4] = 1;
		MacierzGrafu[(r * 5) + 2][c * 5] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 2] = 0; MacierzGrafu[(r * 5) + 2][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 4] = 1;
		MacierzGrafu[(r * 5) + 3][c * 5] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 1] = 0; MacierzGrafu[(r * 5) + 3][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 4][c * 5] = 0; MacierzGrafu[(r * 5) + 4][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 3] = 0; MacierzGrafu[(r * 5) + 4][(c * 5) + 4] = 0;
		break;
	}
	case 5: {
		MacierzGrafu[r * 5][c * 5] = 1; MacierzGrafu[r * 5][(c * 5) + 1] = 1; MacierzGrafu[r * 5][(c * 5) + 2] = 1; MacierzGrafu[r * 5][(c * 5) + 3] = 0; MacierzGrafu[r * 5][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 1][c * 5] = 0; MacierzGrafu[(r * 5) + 1][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 2][c * 5] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 2] = 0; MacierzGrafu[(r * 5) + 2][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 4] = 1;
		MacierzGrafu[(r * 5) + 3][c * 5] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 2] = 0; MacierzGrafu[(r * 5) + 3][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 4] = 1;
		MacierzGrafu[(r * 5) + 4][c * 5] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 4] = 0;
		break;
	}
	case 6: {
		MacierzGrafu[r * 5][c * 5] = 0; MacierzGrafu[r * 5][(c * 5) + 1] = 0; MacierzGrafu[r * 5][(c * 5) + 2] = 1; MacierzGrafu[r * 5][(c * 5) + 3] = 0; MacierzGrafu[r * 5][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 1][c * 5] = 0; MacierzGrafu[(r * 5) + 1][(c * 5) + 1] = 0; MacierzGrafu[(r * 5) + 1][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 1][(c * 5) + 3] = 0; MacierzGrafu[(r * 5) + 1][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 2][c * 5] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 1] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 3] = 1; MacierzGrafu[(r * 5) + 2][(c * 5) + 4] = 1;
		MacierzGrafu[(r * 5) + 3][c * 5] = 0; MacierzGrafu[(r * 5) + 3][(c * 5) + 1] = 0; MacierzGrafu[(r * 5) + 3][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 3][(c * 5) + 3] = 0; MacierzGrafu[(r * 5) + 3][(c * 5) + 4] = 0;
		MacierzGrafu[(r * 5) + 4][c * 5] = 0; MacierzGrafu[(r * 5) + 4][(c * 5) + 1] = 0; MacierzGrafu[(r * 5) + 4][(c * 5) + 2] = 1; MacierzGrafu[(r * 5) + 4][(c * 5) + 3] = 0; MacierzGrafu[(r * 5) + 4][(c * 5) + 4] = 0;
		break;
	}
	}
}
/*
Stworzenie listy sasiedztw wierzcholkow, algorytm szuka w kolejnosci sasiadow dol,prawo,lewo,gora
*/
void InicjalizacjaListy(int MacierzGrafu[Wymiar40][Wymiar20], Wierzcholek**& TablicaList, bool*& visited)
{
	TablicaList = new Wierzcholek * [Wymiar40 * Wymiar20];
	visited = new bool[Wymiar40 * Wymiar20];
	Wierzcholek* p;
	char dol = 'D', gora = 'G', lewo = 'L', prawo = 'P';
	for (int i = 0; i < Wymiar40 * Wymiar20; i++)
	{
		TablicaList[i] = NULL;
		visited[i] = false;
	}

	for (int i = 0; i < Wymiar40; i++)
		for (int j = 0; j < Wymiar20; j++)
		{
			if (MacierzGrafu[i][j] == 0) continue;
			if (i == 0)
			{
				if (j == 0)
				{
					UtworzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
					UtworzSasiada(MacierzGrafu, TablicaList, dol, i, j);
				}
				else if (j == Wymiar20 - 1)
				{
					UtworzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
					UtworzSasiada(MacierzGrafu, TablicaList, dol, i, j);
				}
				else
				{
					UtworzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
					UtworzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
					UtworzSasiada(MacierzGrafu, TablicaList, dol, i, j);
				}
			}
			else if (j == 0)
			{
				if (i == Wymiar40 - 1)
				{
					UtworzSasiada(MacierzGrafu, TablicaList, gora, i, j);
					UtworzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
				}
				else
				{
					UtworzSasiada(MacierzGrafu, TablicaList, gora, i, j);
					UtworzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
					UtworzSasiada(MacierzGrafu, TablicaList, dol, i, j);
				}
			}
			else if (i == Wymiar40 - 1)
			{
				if (j == Wymiar20 - 1)
				{
					UtworzSasiada(MacierzGrafu, TablicaList, gora, i, j);
					UtworzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
				}
				else
				{
					UtworzSasiada(MacierzGrafu, TablicaList, gora, i, j);
					UtworzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
					UtworzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
				}
			}
			else if (j == Wymiar20 - 1)
			{
				UtworzSasiada(MacierzGrafu, TablicaList, gora, i, j);
				UtworzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
				UtworzSasiada(MacierzGrafu, TablicaList, dol, i, j);
			}
			else
			{
				UtworzSasiada(MacierzGrafu, TablicaList, gora, i, j);
				UtworzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
				UtworzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
				UtworzSasiada(MacierzGrafu, TablicaList, dol, i, j);

			}
		}
};

void UtworzSasiada(int MacierzGrafu[Wymiar40][Wymiar20], Wierzcholek**& TablicaList, const char Kierunek, int row, int column) // 68-D(1) 71-G(4) 76-L(9) 80-P(13)
{
	Wierzcholek* p;
	int variable = (int(Kierunek) - 67);
	switch (variable)
	{
	case 1:
		if (MacierzGrafu[row + 1][column] == 1)
		{
			p = new Wierzcholek;
			p->numerwierzcholka = (((row + 1) * Wymiar20) + column);
			p->next = TablicaList[(row * Wymiar20) + column];
			TablicaList[(row * Wymiar20) + column] = p;
		}
		break;
	case 4:
		if (MacierzGrafu[row - 1][column] == 1)
		{
			p = new Wierzcholek;
			p->numerwierzcholka = (((row - 1) * Wymiar20) + column);
			p->next = TablicaList[(row * Wymiar20) + column];
			TablicaList[(row * Wymiar20) + column] = p;
		}
		break;
	case 9:
		if (MacierzGrafu[row][column - 1] == 1)
		{
			p = new Wierzcholek;
			p->numerwierzcholka = ((row * Wymiar20) + column - 1);
			p->next = TablicaList[(row * Wymiar20) + column];
			TablicaList[(row * Wymiar20) + column] = p;
		}
		break;
	case 13:
		if (MacierzGrafu[row][column + 1] == 1)
		{
			p = new Wierzcholek;
			p->numerwierzcholka = ((row * Wymiar20) + column + 1);
			p->next = TablicaList[(row * Wymiar20) + column];
			TablicaList[(row * Wymiar20) + column] = p;
		}
		break;
	}
}
/*
Funkcja wypisuje listy sasiedztw dla kazdego wierzcholka
*/
void WypiszWierzcholki(Wierzcholek**& TablicaList)
{
	Wierzcholek* p;
	for (int i = 0; i < Wymiar40 * Wymiar20; i++)
	{
		cout << "Lista [ " << i << " ] =";
		p = TablicaList[i];
		while (p)
		{
			cout << setw(5) << p->numerwierzcholka;
			p = p->next;
		}
		cout << endl;
	}
}
/*
Zwalnia miejsce w pamieci po dynamicznie tworzonych obiektach w programie
*/
void UsunGraf(Wierzcholek**& TablicaList, bool*& visited)
{
	Wierzcholek* p, * r;
	for (int i = 0; i < Wymiar40 * Wymiar20; i++)
	{
		p = TablicaList[i];
		while (p)
		{
			r = p;
			p = p->next;
			delete r;
		}
	}

	delete[] TablicaList;
	delete[] visited;
}
/*
Najwazniejsza i najbardziej skomplikowana funkcja programu, algorytm przeszukiwania stworzonego grafu
*/
bool DFS(Wierzcholek**& TablicaList, bool*& visited, int startowy, int koncowy, int MacierzGrafu[Wymiar40][Wymiar20], int Kolejnosc[Wymiar40 * Wymiar20], static int kolejny)

{
	Wierzcholek* p;
	visited[startowy] = true;
	if (startowy != koncowy) {
		Kolejnosc[kolejny] = startowy;
		kolejny++;
	}

	if (startowy == koncowy)
	{
		Kolejnosc[kolejny] = startowy;
		cout << "Funkcja znalazla droge.\n";
		return true;
	}
	for (p = TablicaList[startowy]; p; p = p->next)
	{
		MacierzGrafu[startowy / 20][startowy % 20] = 2;
		if (!visited[p->numerwierzcholka] && DFS(TablicaList, visited, p->numerwierzcholka, koncowy, MacierzGrafu, Kolejnosc, kolejny))
			return true;
	}
	return false;
}
/*
Menu glowne, w nim zawiera sie caly program
*/
void MenuGlowne()
{
	int wybor;
	do
	{
		PiszMenu(1);
		cin >> wybor;
		switch (wybor)
		{
		case 1: DrogaRobota();
			break;
		case 2:PiszMenu(2);
			break;
		case 3:exit(0);
			break;
		}
	} while (wybor != 3);


}
/*
Funkcja wypisujaca wybrane menu
*/
void PiszMenu(int Numer)
{
	switch (Numer)
	{
	case 1:
		CLS
			OprawaGraficzna(1);
		cout << setw(77) << "Wyznaczanie drogi robota przy uzyciu algorytmu typu Depth-First-Search\n"
			<< setw(60) << " By Damian Kakol and Krzysztof Dymanowski\n\n"
			<< "  Prosze wpisac numer opcji ktora chce sie wybrac i wcisnac enter:\n"
			<< "  1. Prezentacja Algorytmu.\n"
			<< "  2. Krotkie objasnienie dzialania programu.\n"
			<< "  3. Wyjscie z programu.\n";
		OprawaGraficzna(2);
		OprawaGraficzna(3);
		break;
	case 2:
		CLS
			OprawaGraficzna(1);
		cout << "  Graf, ktory tworzony jest na podstawie dwuwymiarowej tablicy i zapisany jako\n"
			<< "  dynamiczna lista sasiedztw wierzcholkow, przy pomocy rekurencyjnego wywolania funkcji\n"
			<< "  DFS, znajduje droge pomiedzy dwoma punktami na planszy o wymiarach 40 x 20\n"
			<< "  od punktu A do punktu B, poruszajac sie jedynie po polach bialych\n";
		OprawaGraficzna(2);
		OprawaGraficzna(3);
		PAUSE
			break;
	case 3:
		OprawaGraficzna(1);
		cout << "Wybierz opcje wciskajac odpowiedni numer i klikajac enter\n"
			<< "  1. Wyswietl Tablice segmentow\n"
			<< "  2. Wyswietl Plansze przed wyznaczeniem drogi\n"
			<< "  3. Wyswietl Liste sasiedztw wierzcholkow\n"
			<< "  4. Wyswietl Plansze po wyznaczeniu drogi\n"
			<< "  5. Wyswietl kolejnosc odwiedzania wierzcholkow\n"
			<< "  6. Wyswietl numer poczatkowego i koncowego wierzcholka\n"
			<< "  7. Wyczysc ekran\n"
			<< "  8. Wroc do menu glownego\n";
		break;
	}
}
/*
Wypisanie wszystkich sprawdzonych przez DFS wierzcholkow w kolejnosci "zagladania" do nich, w rzeczywistosci znajduje wierzcholek szybciej ale 
*/
void WypiszDroge(int Kolejnosc[Wymiar40 * Wymiar20],int koncowy)
{
	int i;
	for (i = 0; i < Wymiar40 * Wymiar20; i++) {
		if (Kolejnosc[i] == 800) continue;
		cout << Kolejnosc[i] << "->" << setw(6);
	}
	cout << " Ostatni (odwiedzony) wierzcholek ma numer: " << koncowy << "\n";
}
/*
Wypisuje plansze 40x20, w dzialaniu programu mamy dwa wywolania funkcji, jeden dla planszy przed przejsciem po grafie, drugi po przejsciu po grafie
*/
void WypiszPlansze(int MacierzGrafu[Wymiar40][Wymiar20])
{
	for (int i = 0; i < Wymiar40; i++) {
		for (int j = 0; j < Wymiar20; j++)
		{
			if (MacierzGrafu[i][j] == 0)
				cout << CzarnePole
			else if (MacierzGrafu[i][j] == 1)
				cout << BialePole
			else if (MacierzGrafu[i][j] == 2)
				cout << "+";
			else if (MacierzGrafu[i][j] == 3)
				cout << "A";
			else if (MacierzGrafu[i][j] == 4)
				cout << "B";
			else if (MacierzGrafu[i][j] == 5)
				cout << Robocik
		}
		cout << "\n";
	}
}
/*
Druga glowna funkcja programu, zawiera w sobie wiekszosc funkcji ktore obejmuje program
*/
void DrogaRobota()
{
	int Kolejnosc[Wymiar40 * Wymiar20];
	static int kolejny = 0;
	srand(time(NULL));
	CLS
	bool* visited;
	int R1, C1, R2, C2;
	int opcja;
	char Macierz[Wymiar8][Wymiar4];
	int MacierzGrafu[Wymiar40][Wymiar20];
	int MacierzPoWyznaczeniuDrogi[Wymiar40][Wymiar20];
	Wierzcholek** TablicaList;
	for (int i = 0; i < Wymiar40 * Wymiar20; i++)
		Kolejnosc[i] = 800;

	GenerujMacierzSegmentow(Macierz);

	StworzMacierzPlanszy(Macierz, MacierzGrafu);
	StworzMacierzPlanszy(Macierz, MacierzPoWyznaczeniuDrogi);

	InicjalizacjaListy(MacierzGrafu, TablicaList, visited);

	do {
		R1 = rand() % Wymiar40;
		C1 = rand() % Wymiar20;
	} while (MacierzGrafu[R1][C1] != 1);

	do {
		R2 = rand() % Wymiar40;
		C2 = rand() % Wymiar20;
	} while ((MacierzGrafu[R2][C2] != 1) && (R2 != R1) && (C2 != C1));

	int LosowyWierzcholek = (R1 * Wymiar20) + C1;

	int KoncowyWierzcholek = (R2 * Wymiar20) + C2;
	cout << LosowyWierzcholek << setw(5) << KoncowyWierzcholek << "\n";

	bool result = DFS(TablicaList, visited, LosowyWierzcholek, KoncowyWierzcholek, MacierzPoWyznaczeniuDrogi, Kolejnosc, kolejny);

	MacierzGrafu[R1][C1] = 5;
	MacierzGrafu[R2][C2] = 4;
	MacierzPoWyznaczeniuDrogi[R1][C1] = 3;
	MacierzPoWyznaczeniuDrogi[R2][C2] = 5;

	CLS

		PiszMenu(3);

	do {
		cin >> opcja;
		switch (opcja)
		{
		case 1: WypiszMacierz(Macierz);
			PAUSE
				break;
		case 2:WypiszPlansze(MacierzGrafu);
			PAUSE
				break;
		case 3:WypiszWierzcholki(TablicaList);
			PAUSE
				break;
		case 4:WypiszPlansze(MacierzPoWyznaczeniuDrogi);
			PAUSE
				break;
		case 5:WypiszDroge(Kolejnosc,KoncowyWierzcholek);
			PAUSE
				break;
		case 6: cout << " Wierzcholek poczatkowy ma numer: " << LosowyWierzcholek << " , a koncowy ma numer: " << KoncowyWierzcholek << "\n";
			PAUSE
				break;
		case 7: CLS
			PiszMenu(3);
			break;
		case 8:
			break;
		}
	} while (opcja != 8);

	UsunGraf(TablicaList, visited);
	PAUSE
}

int main()
{
	MenuGlowne();
	return 0;
}