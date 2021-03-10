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

struct Wierzcholek{
	int Wartosc;
	bool kolor; // false - kolor czarny, robot nie moze sie przemiescic, true - kolor bialy
	Wierzcholek* Kolejny;
};


void MacierzSegmentow(char MacierzPosegmentowana[Wymiar8][Wymiar4])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
			MacierzPosegmentowana[i][j] = char(rand() % 6 + 65);
}

void WypiszMacierz(char MacierzPosegmentowana[Wymiar8][Wymiar4])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << setw(3) << MacierzPosegmentowana[i][j];
		}
	cout << "\n";
	}
}

void StworzMacierzPlanszy(char MacierzPosegmentowana[Wymiar8][Wymiar4], int MacierzGrafu[Wymiar40][Wymiar20])
{
	
}

void MenuGlowne()
{

}

void InicjalizacjaListy(int MacierzGrafu[Wymiar40][Wymiar20])
{

};

int main()
{
	char Macierz[Wymiar8][Wymiar4];
	int MacierzGrafu[Wymiar40][Wymiar20];
	srand(time(NULL));
	MacierzSegmentow(Macierz);
	WypiszMacierz(Macierz);
	return 0;
}