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
	int Wartosc;
	bool kolor; // false - kolor czarny, robot nie moze sie przemiescic, true - kolor bialy
	Wierzcholek* Kolejny;
};

void GenerujMacierzSegmentow(char MacierzSegmentow[Wymiar8][Wymiar4]);
void WypiszMacierz(char MacierzSegmentow[Wymiar8][Wymiar4]);
void StworzMacierzPlanszy(char MacierzSegmentow[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20]);
void DefinicjaSegmentu(char MacierzSegmentow[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20], int w, int k);
void WypelnienieSegmentu(int MacierzGrafu[Wymiar40][Wymiar20], int Segment, int w, int k);

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


void InicjalizacjaListy(int MacierzGrafu[Wymiar40][Wymiar20])
{

};

int main()
{
	char Macierz[Wymiar8][Wymiar4];
	int MacierzGrafu[Wymiar40][Wymiar20];
	srand(time(NULL));
	GenerujMacierzSegmentow(Macierz);
	WypiszMacierz(Macierz);
	StworzMacierzPlanszy(Macierz, MacierzGrafu);
	for (int g = 0; g < 40; g++) {
		for (int z = 0; z < 20; z++)
			if (MacierzGrafu[g][z]) cout << BialePole;
			else cout << CzarnePole;
		cout << "\n";
	}
	return 0;
}