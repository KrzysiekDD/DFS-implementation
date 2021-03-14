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

#define BialePole char(219)
#define CzarnePole char(255)
#define Robocik char(167)
#define CLS system("cls");
#define PAUSE system("pause");

struct Wierzcholek {
	Wierzcholek* next;
	int numerwierzcholka;
};

void GenerujMacierzSegmentow(char MacierzSegmentow[Wymiar8][Wymiar4]);
void WypiszMacierz(char MacierzSegmentow[Wymiar8][Wymiar4]);
void StworzMacierzPlanszy(char MacierzSegmentow[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20]);
void DefinicjaSegmentu(char MacierzSegmentow[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20], int w, int k);
void WypelnienieSegmentu(int MacierzGrafu[Wymiar40][Wymiar20], int Segment, int w, int k);
void UwtorzSasiada(int MacierzGrafu[Wymiar40][Wymiar20], Wierzcholek**& TablicaList, const char Kierunek, int row, int column);
void InicjalizacjaListy(int MacierzGrafu[Wymiar40][Wymiar20], Wierzcholek**& TablicaList, bool*& visited);
bool DFS(Wierzcholek**& TablicaList, bool*& visited, int startowy, int koncowy, int MacierzGrafu[Wymiar40][Wymiar20]);
void PiszMenu(int Numer);
void MenuGlowne();
void DrogaRobota();
void OprawaGraficzna(int n);

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

void GenerujMacierzSegmentow(char MacierzSegmentow[Wymiar8][Wymiar4])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
			MacierzSegmentow[i][j] = char(rand() % 6 + 65);
}

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

void StworzMacierzPlanszy(char MacierzSegmentow[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20])
{
	for (int w = 0; w < Wymiar8; w++)
		for (int k = 0; k < Wymiar4; k++)
		{
			DefinicjaSegmentu(MacierzSegmentow, MacierzGrafu, w, k);
		}

}

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
			if (MacierzGrafu[i][j] == 0) continue;    // Gora,lewo,prawo,dol
			if (i == 0)
			{
				if (j == 0)
				{
					UwtorzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, dol, i, j);
				}
				else if (j == Wymiar40 - 1)
				{
					UwtorzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, dol, i, j);
				}
				else
				{
					UwtorzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, dol, i, j);
				}
			}
			else if (j == 0)
			{
				if (i == Wymiar40 - 1)
				{
					UwtorzSasiada(MacierzGrafu, TablicaList, gora, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
				}
				else
				{
					UwtorzSasiada(MacierzGrafu, TablicaList, gora, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, dol, i, j);
				}
			}
			else if (i == Wymiar40 - 1)
			{
				if (j == Wymiar40 - 1)
				{
					UwtorzSasiada(MacierzGrafu, TablicaList, gora, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
				}
				else
				{
					UwtorzSasiada(MacierzGrafu, TablicaList, gora, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
				}
			}
			else if (j == Wymiar40 - 1)
			{
				UwtorzSasiada(MacierzGrafu, TablicaList, gora, i, j);
				UwtorzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
				UwtorzSasiada(MacierzGrafu, TablicaList, dol, i, j);
			}
			else
			{
				UwtorzSasiada(MacierzGrafu, TablicaList, gora, i, j);
				UwtorzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
				UwtorzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
				UwtorzSasiada(MacierzGrafu, TablicaList, dol, i, j);

			}
			/*cin >> v1 >> v2;  // wierzcholek poczatkowy i koncowy
			p = new Wierzcholek;
			p->wartosc = v2;
			p->next = TablicaList[v1];
			TablicaList[v1] = p;*/
		}
};

void UwtorzSasiada(int MacierzGrafu[Wymiar40][Wymiar20], Wierzcholek**& TablicaList, const char Kierunek, int row, int column) // 68-D(1) 71-G(4) 76-L(9) 80-P(13)
{
	Wierzcholek* p;
	int variable = int(Kierunek) - 67;
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

bool DFS(Wierzcholek**& TablicaList, bool*& visited, int startowy, int koncowy, int MacierzGrafu[Wymiar40][Wymiar20])

{
	Wierzcholek* p;
	visited[startowy] = true;

	cout << setw(3) << startowy << "->";

		if (startowy == koncowy)
		{
			cout << koncowy << setw(5) << "funkcja znalazla droge";
		return true;
		}
	for (p = TablicaList[startowy]; p; p = p->next)
	{
		MacierzGrafu[startowy / 20][startowy % 20] = 2;
		if (!visited[p->numerwierzcholka] && DFS(TablicaList, visited, p->numerwierzcholka, koncowy, MacierzGrafu));
		return true;
	}
	return false;
}

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
		cout <<  "Graf, ktory tworzony jest na podstawie dwuwymiarowej tablicy i zapisany jako\n"
			<<  "  dynamiczna lista sasiedztw wierzcholkow, przy pomocy rekurencyjnego wywolania funkcji\n"
			<<  "  DFS, znaduje droge pomiedzy dwoma punktami na planszy o wymiarach 40 x 20\n"
			<<  "  od punktu A do punktu B\n";
		OprawaGraficzna(2);
		OprawaGraficzna(3);
		PAUSE
		break;
	}
}

void DrogaRobota()
{
	CLS
	bool* visited;
	int R1, C1, R2, C2;

	char Macierz[Wymiar8][Wymiar4];
	int MacierzGrafu[Wymiar40][Wymiar20];
	srand(time(NULL));

	GenerujMacierzSegmentow(Macierz);

	WypiszMacierz(Macierz);

	StworzMacierzPlanszy(Macierz, MacierzGrafu);
	Wierzcholek** TablicaList;

	InicjalizacjaListy(MacierzGrafu, TablicaList, visited);
	do {
		R1 = rand() % Wymiar40;
		C1 = rand() % Wymiar20;
	} while (!MacierzGrafu[R1][C1]);

	do {
		R2 = rand() % Wymiar40;
		C2 = rand() % Wymiar20;
	} while (!MacierzGrafu[R2][C2] && (R2 != R1) && (C2 != C1));

	int LosowyWierzcholek = (R1 * Wymiar20) + C1;

	int KoncowyWierzcholek = (R2 * Wymiar20) + C2;
	cout << LosowyWierzcholek << setw(5) << KoncowyWierzcholek << "\n";

	bool result = DFS(TablicaList, visited, LosowyWierzcholek, KoncowyWierzcholek, MacierzGrafu);
	cout << "result: " << result;
	/*
*	{
		cin >> v1 >> v2;  // wierzcholek poczatkowy i koncowy
		p = new Wierzcholek;
		p->wartosc = v2;
		p->next = TablicaList[v1];
		TablicaList[v1] = p;
	}
*/
	cout << endl << endl << endl;

	for (int g = 0; g < Wymiar40; g++)
	{

		for (int z = 0; z < Wymiar20; z++) {
			if (g == R1 && z == C1) {
				cout << "A";
			}
			else if (g == R2 && z == C2) {
				cout << "R";
			}
			else if (MacierzGrafu[g][z] == 1) {
				cout << BialePole;
			}
			else if (MacierzGrafu[g][z] == 2) {
				cout << "+";
			}
			else {
				cout << CzarnePole;
			}

			//cout << setw(5) << (g*Wymiar20)+z;
		}
		cout << "\n";

	}

	UsunGraf(TablicaList, visited);
	PAUSE
}

int main()
{
	MenuGlowne();
	return 0;
}