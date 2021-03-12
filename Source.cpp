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


struct Wierzcholek {
	Wierzcholek* next;
	int wartosc;
	bool kolor; // false - kolor czarny, robot nie moze sie przemiescic, true - kolor bialy
};

void GenerujMacierzSegmentow(char MacierzSegmentow[Wymiar8][Wymiar4]);
void WypiszMacierz(char MacierzSegmentow[Wymiar8][Wymiar4]);
void StworzMacierzPlanszy(char MacierzSegmentow[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20]);
void DefinicjaSegmentu(char MacierzSegmentow[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20], int w, int k);
void WypelnienieSegmentu(int MacierzGrafu[Wymiar40][Wymiar20], int Segment, int w, int k);
void UwtorzSasiada(int MacierzGrafu[Wymiar40][Wymiar20], Wierzcholek**& TablicaList, const char Kierunek, int row, int column);

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


void InicjalizacjaListy(int MacierzGrafu[Wymiar40][Wymiar20], Wierzcholek **& TablicaList)
{
	TablicaList = new Wierzcholek * [Wymiar40 * Wymiar20];
	Wierzcholek* p;
	char dol = 'D', gora = 'G', lewo = 'L', prawo = 'P';
	for (int i = 0; i < Wymiar40 * Wymiar20; i++)
		TablicaList[i] = nullptr;

	for (int i = 0; i < Wymiar40; i++)
		for (int j = 0; j < Wymiar20; j++)
		{
			if (MacierzGrafu[i][j] == 0) continue;
			if (i == 0)
			{
				if (j == 0)
				{
					UwtorzSasiada(MacierzGrafu, TablicaList, dol, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
				}
				else if (j == Wymiar40 - 1)
				{
					UwtorzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, dol, i, j);
				}
				else
				{
					UwtorzSasiada(MacierzGrafu, TablicaList, lewo, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, dol, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
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
					UwtorzSasiada(MacierzGrafu, TablicaList, dol, i, j);
					UwtorzSasiada(MacierzGrafu, TablicaList, prawo, i, j);
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
				UwtorzSasiada(MacierzGrafu, TablicaList, dol, i, j);
				UwtorzSasiada(MacierzGrafu, TablicaList, prawo, i, j);

			}
			/*cin >> v1 >> v2;  // wierzcholek poczatkowy i koncowy
			p = new Wierzcholek;
			p->wartosc = v2;
			p->next = TablicaList[v1];
			TablicaList[v1] = p;*/
		}
};

void UwtorzSasiada(int MacierzGrafu[Wymiar40][Wymiar20], Wierzcholek **& TablicaList,const char Kierunek, int row, int column) // 68-D(1) 71-G(4) 76-L(9) 80-P(13)
{
	Wierzcholek* p;
	int variable = int(Kierunek) - 67;
	switch (variable)
	{
	case 1: {
		if (MacierzGrafu[row + 1][column] == 1)
		{
			p = new Wierzcholek;
			p->wartosc = (((row + 1) * Wymiar20) + column);
			p->next = TablicaList[(row * Wymiar20) + column];
			TablicaList[(row * Wymiar20) + column] = p;
		}
	}break;
	case 4: {
		if (MacierzGrafu[row - 1][column] == 1)
		{
			p = new Wierzcholek;
			p->wartosc = (((row - 1) * Wymiar20) + column);
			p->next = TablicaList[(row * Wymiar20) + column];
			TablicaList[(row * Wymiar20) + column] = p;
		}
	}break;
	case 9: {
		if (MacierzGrafu[row][column - 1] == 1)
		{
			p = new Wierzcholek;
			p->wartosc = ((row * Wymiar20) + column - 1);
			p->next = TablicaList[(row * Wymiar20) + column];
			TablicaList[(row * Wymiar20) + column] = p;
		}
	}break;
	case 13: {
		if (MacierzGrafu[row][column + 1] == 1)
		{
			p = new Wierzcholek;
			p->wartosc = ((row * Wymiar20) + column + 1);
			p->next = TablicaList[(row * Wymiar20) + column];
			TablicaList[(row * Wymiar20) + column] = p;
		}
	}break;
	}
}

int main()
{
	Wierzcholek* p;
	Wierzcholek* r;
	int v1, v2, n;

	char Macierz[Wymiar8][Wymiar4];
	int MacierzGrafu[Wymiar40][Wymiar20];
	srand(time(NULL));

	GenerujMacierzSegmentow(Macierz);

	WypiszMacierz(Macierz);

	StworzMacierzPlanszy(Macierz, MacierzGrafu);

	for (int g = 0; g < Wymiar40; g++)
	{
		for (int z = 0; z < 20; z++)
			if (MacierzGrafu[g][z])
				cout << BialePole;
			else cout << CzarnePole;
		cout << "\n";
	}
	Wierzcholek** TablicaList;

	InicjalizacjaListy(MacierzGrafu, TablicaList);
	/*
			cin >> v1 >> v2;  // wierzcholek poczatkowy i koncowy 
			p = new Wierzcholek;
			p->wartosc = v2;
			p->next = TablicaList[v1];
			TablicaList[v1] = p;
		}
*/

	for (int i = 0; i < Wymiar40 * Wymiar20; i++)
	{
		cout << "Lista [ " << i << " ] =";
		p = TablicaList[i];
		while (p)
		{
			cout << setw(5) << p->wartosc;
			p = p->next;
		}
		cout << endl;
	}


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

	return 0;
}