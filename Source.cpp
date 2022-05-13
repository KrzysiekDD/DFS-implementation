#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// constant values
#define INT_8 8
#define INT_4 4
#define INT_40 40
#define INT_20 20
#define WHITE_SQUARE char(219)
#define BLACK_SQUARE char(255)
#define ROBOT_ICON char(167)
#define CLS system("cls")
#define PAUSE system("pause")

// the graph is represented by a linked list

struct GraphNode {
	GraphNode* next;
	int node_number;
};
void main_menu();
void robots_path();
void display_menu(int number);
void graphics(int n);
void show_nodes(GraphNode**& current_graph);
void show_graph(int graph_matrix[INT_40][INT_20]);
void show_segments(char segment_matrix[INT_8][INT_4]);
void show_path(int order[INT_40 * INT_20], int koncowy);
void generate_segments(char segment_matrix[INT_8][INT_4]);
void segment_values(int graph_matrix[INT_40][INT_20], int Segment, int w, int k);
void generate_graph(char segment_matrix[INT_8][INT_4], int graph_matrix[INT_40][INT_20]);
void graph_init(int graph_matrix[INT_40][INT_20], GraphNode**& current_graph, bool*& visited);
void segment_definition(char segment_matrix[INT_8][INT_4], int graph_matrix[INT_40][INT_20], int w, int k);
bool DFS(GraphNode**& current_graph, bool*& visited, int startowy, int koncowy, int graph_matrix[INT_40][INT_20]);
void create_neighbor(int graph_matrix[INT_40][INT_20], GraphNode**& current_graph, const char Kierunek, int row, int column);

/*
graphic design of the program
*/
void graphics(int n)
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
generation of 8 x 4 matrix of segments
*/
void generate_segments(char segment_matrix[INT_8][INT_4])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
			segment_matrix[i][j] = char(rand() % 6 + 65);
}
/*
draws the matrix of segments
*/
void show_segments(char segment_matrix[INT_8][INT_4])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << setw(3) << segment_matrix[i][j];
		}
		cout << "\n";
	}
}
/*
creates the graph that will be searched
*/
void generate_graph(char segment_matrix[INT_8][INT_4], int graph_matrix[INT_40][INT_20])
{
	for (int w = 0; w < INT_8; w++)
		for (int k = 0; k < INT_4; k++)
		{
			segment_values(segment_matrix, graph_matrix, w, k);
		}
}
/*
auxiliary function to fill the graph
*/
void segment_values(char segment_matrix[INT_8][INT_4], int graph_matrix[INT_40][INT_20], int w, int k)
{
	int var = int((segment_matrix[w][k]) - 64);
	switch (var)
	{
	case 1: segment_definition(graph_matrix, 1, w, k);
		break;
	case 2: segment_definition(graph_matrix, 2, w, k);
		break;
	case 3: segment_definition(graph_matrix, 3, w, k);
		break;
	case 4: segment_definition(graph_matrix, 4, w, k);
		break;
	case 5: segment_definition(graph_matrix, 5, w, k);
		break;
	case 6: segment_definition(graph_matrix, 6, w, k);
		break;
	}
}
/*
each segment consists of either black or white nodes, black nodes being not accesible by the algorithm
*/
void segment_definition(int graph_matrix[INT_40][INT_20], int Segment, int w, int k)
{
	int r = w;
	int c = k;
	switch (Segment)
	{
	case 1: {
		graph_matrix[r * 5][c * 5] = 0; graph_matrix[r * 5][(c * 5) + 1] = 0; graph_matrix[r * 5][(c * 5) + 2] = 1; graph_matrix[r * 5][(c * 5) + 3] = 0; graph_matrix[r * 5][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 1][c * 5] = 0; graph_matrix[(r * 5) + 1][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 3] = 0; graph_matrix[(r * 5) + 1][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 2][c * 5] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 2] = 0; graph_matrix[(r * 5) + 2][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 4] = 1;
		graph_matrix[(r * 5) + 3][c * 5] = 0; graph_matrix[(r * 5) + 3][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 4][c * 5] = 0; graph_matrix[(r * 5) + 4][(c * 5) + 1] = 0; graph_matrix[(r * 5) + 4][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 3] = 0; graph_matrix[(r * 5) + 4][(c * 5) + 4] = 0;
		break;
	}
	case 2: {
		graph_matrix[r * 5][c * 5] = 0; graph_matrix[r * 5][(c * 5) + 1] = 0; graph_matrix[r * 5][(c * 5) + 2] = 1; graph_matrix[r * 5][(c * 5) + 3] = 1; graph_matrix[r * 5][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 1][c * 5] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 1] = 0; graph_matrix[(r * 5) + 1][(c * 5) + 2] = 0; graph_matrix[(r * 5) + 1][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 2][c * 5] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 4] = 1;
		graph_matrix[(r * 5) + 3][c * 5] = 0; graph_matrix[(r * 5) + 3][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 4][c * 5] = 0; graph_matrix[(r * 5) + 4][(c * 5) + 1] = 0; graph_matrix[(r * 5) + 4][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 4] = 0;
		break;
	}
	case 3: {
		graph_matrix[r * 5][c * 5] = 1; graph_matrix[r * 5][(c * 5) + 1] = 1; graph_matrix[r * 5][(c * 5) + 2] = 1; graph_matrix[r * 5][(c * 5) + 3] = 1; graph_matrix[r * 5][(c * 5) + 4] = 1;
		graph_matrix[(r * 5) + 1][c * 5] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 2] = 0; graph_matrix[(r * 5) + 1][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 4] = 1;
		graph_matrix[(r * 5) + 2][c * 5] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 2] = 0; graph_matrix[(r * 5) + 2][(c * 5) + 3] = 0; graph_matrix[(r * 5) + 2][(c * 5) + 4] = 1;
		graph_matrix[(r * 5) + 3][c * 5] = 0; graph_matrix[(r * 5) + 3][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 2] = 0; graph_matrix[(r * 5) + 3][(c * 5) + 3] = 0; graph_matrix[(r * 5) + 3][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 4][c * 5] = 0; graph_matrix[(r * 5) + 4][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 4] = 1;
		break;
	}
	case 4: {
		graph_matrix[r * 5][c * 5] = 0; graph_matrix[r * 5][(c * 5) + 1] = 0; graph_matrix[r * 5][(c * 5) + 2] = 1; graph_matrix[r * 5][(c * 5) + 3] = 1; graph_matrix[r * 5][(c * 5) + 4] = 1;
		graph_matrix[(r * 5) + 1][c * 5] = 0; graph_matrix[(r * 5) + 1][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 3] = 0; graph_matrix[(r * 5) + 1][(c * 5) + 4] = 1;
		graph_matrix[(r * 5) + 2][c * 5] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 2] = 0; graph_matrix[(r * 5) + 2][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 4] = 1;
		graph_matrix[(r * 5) + 3][c * 5] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 1] = 0; graph_matrix[(r * 5) + 3][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 4][c * 5] = 0; graph_matrix[(r * 5) + 4][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 3] = 0; graph_matrix[(r * 5) + 4][(c * 5) + 4] = 0;
		break;
	}
	case 5: {
		graph_matrix[r * 5][c * 5] = 1; graph_matrix[r * 5][(c * 5) + 1] = 1; graph_matrix[r * 5][(c * 5) + 2] = 1; graph_matrix[r * 5][(c * 5) + 3] = 0; graph_matrix[r * 5][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 1][c * 5] = 0; graph_matrix[(r * 5) + 1][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 2][c * 5] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 2] = 0; graph_matrix[(r * 5) + 2][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 4] = 1;
		graph_matrix[(r * 5) + 3][c * 5] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 2] = 0; graph_matrix[(r * 5) + 3][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 4] = 1;
		graph_matrix[(r * 5) + 4][c * 5] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 4] = 0;
		break;
	}
	case 6: {
		graph_matrix[r * 5][c * 5] = 0; graph_matrix[r * 5][(c * 5) + 1] = 0; graph_matrix[r * 5][(c * 5) + 2] = 1; graph_matrix[r * 5][(c * 5) + 3] = 0; graph_matrix[r * 5][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 1][c * 5] = 0; graph_matrix[(r * 5) + 1][(c * 5) + 1] = 0; graph_matrix[(r * 5) + 1][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 1][(c * 5) + 3] = 0; graph_matrix[(r * 5) + 1][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 2][c * 5] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 1] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 3] = 1; graph_matrix[(r * 5) + 2][(c * 5) + 4] = 1;
		graph_matrix[(r * 5) + 3][c * 5] = 0; graph_matrix[(r * 5) + 3][(c * 5) + 1] = 0; graph_matrix[(r * 5) + 3][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 3][(c * 5) + 3] = 0; graph_matrix[(r * 5) + 3][(c * 5) + 4] = 0;
		graph_matrix[(r * 5) + 4][c * 5] = 0; graph_matrix[(r * 5) + 4][(c * 5) + 1] = 0; graph_matrix[(r * 5) + 4][(c * 5) + 2] = 1; graph_matrix[(r * 5) + 4][(c * 5) + 3] = 0; graph_matrix[(r * 5) + 4][(c * 5) + 4] = 0;
		break;
	}
	}
}
/*
"links" every white node with every other white node that directly neighbors it
*/
void graph_init(int graph_matrix[INT_40][INT_20], GraphNode**& current_graph, bool*& visited)
{
	current_graph = new GraphNode * [INT_40 * INT_20];
	visited = new bool[INT_40 * INT_20];
	GraphNode* p;
	char dol = 'D', gora = 'G', lewo = 'L', prawo = 'P';
	for (int i = 0; i < INT_40 * INT_20; i++)
	{
		current_graph[i] = NULL;
		visited[i] = false;
	}

	for (int i = 0; i < INT_40; i++)
		for (int j = 0; j < INT_20; j++)
		{
			if (graph_matrix[i][j] == 0) continue;
			if (i == 0)
			{
				if (j == 0)
				{
					create_neighbor(graph_matrix, current_graph, prawo, i, j);
					create_neighbor(graph_matrix, current_graph, dol, i, j);
				}
				else if (j == INT_20 - 1)
				{
					create_neighbor(graph_matrix, current_graph, lewo, i, j);
					create_neighbor(graph_matrix, current_graph, dol, i, j);
				}
				else
				{
					create_neighbor(graph_matrix, current_graph, lewo, i, j);
					create_neighbor(graph_matrix, current_graph, prawo, i, j);
					create_neighbor(graph_matrix, current_graph, dol, i, j);
				}
			}
			else if (j == 0)
			{
				if (i == INT_40 - 1)
				{
					create_neighbor(graph_matrix, current_graph, gora, i, j);
					create_neighbor(graph_matrix, current_graph, prawo, i, j);
				}
				else
				{
					create_neighbor(graph_matrix, current_graph, gora, i, j);
					create_neighbor(graph_matrix, current_graph, prawo, i, j);
					create_neighbor(graph_matrix, current_graph, dol, i, j);
				}
			}
			else if (i == INT_40 - 1)
			{
				if (j == INT_20 - 1)
				{
					create_neighbor(graph_matrix, current_graph, gora, i, j);
					create_neighbor(graph_matrix, current_graph, lewo, i, j);
				}
				else
				{
					create_neighbor(graph_matrix, current_graph, gora, i, j);
					create_neighbor(graph_matrix, current_graph, lewo, i, j);
					create_neighbor(graph_matrix, current_graph, prawo, i, j);
				}
			}
			else if (j == INT_20 - 1)
			{
				create_neighbor(graph_matrix, current_graph, gora, i, j);
				create_neighbor(graph_matrix, current_graph, lewo, i, j);
				create_neighbor(graph_matrix, current_graph, dol, i, j);
			}
			else
			{
				create_neighbor(graph_matrix, current_graph, gora, i, j);
				create_neighbor(graph_matrix, current_graph, lewo, i, j);
				create_neighbor(graph_matrix, current_graph, prawo, i, j);
				create_neighbor(graph_matrix, current_graph, dol, i, j);

			}
		}
};

void create_neighbor(int graph_matrix[INT_40][INT_20], GraphNode**& current_graph, const char Kierunek, int row, int column) // 68-D(1) 71-G(4) 76-L(9) 80-P(13)
{
	GraphNode* p;
	int variable = (int(Kierunek) - 67);
	switch (variable)
	{
	case 1:
		if (graph_matrix[row + 1][column] == 1)
		{
			p = new GraphNode;
			p->node_number = (((row + 1) * INT_20) + column);
			p->next = current_graph[(row * INT_20) + column];
			current_graph[(row * INT_20) + column] = p;
		}
		break;
	case 4:
		if (graph_matrix[row - 1][column] == 1)
		{
			p = new GraphNode;
			p->node_number = (((row - 1) * INT_20) + column);
			p->next = current_graph[(row * INT_20) + column];
			current_graph[(row * INT_20) + column] = p;
		}
		break;
	case 9:
		if (graph_matrix[row][column - 1] == 1)
		{
			p = new GraphNode;
			p->node_number = ((row * INT_20) + column - 1);
			p->next = current_graph[(row * INT_20) + column];
			current_graph[(row * INT_20) + column] = p;
		}
		break;
	case 13:
		if (graph_matrix[row][column + 1] == 1)
		{
			p = new GraphNode;
			p->node_number = ((row * INT_20) + column + 1);
			p->next = current_graph[(row * INT_20) + column];
			current_graph[(row * INT_20) + column] = p;
		}
		break;
	}
}
/*
outputs the neighbors of each node
*/
void show_nodes(GraphNode**& current_graph)
{
	GraphNode* p;
	for (int i = 0; i < INT_40 * INT_20; i++)
	{
		cout << "Lista [ " << i << " ] =";
		p = current_graph[i];
		while (p)
		{
			cout << setw(5) << p->node_number;
			p = p->next;
		}
		cout << endl;
	}
}
/*
Deletes the graph, as it is dynamically created and new graph is generated with each presentation of the algorithm
*/
void UsunGraf(GraphNode**& current_graph, bool*& visited)
{
	GraphNode* p, * r;
	for (int i = 0; i < INT_40 * INT_20; i++)
	{
		p = current_graph[i];
		while (p)
		{
			r = p;
			p = p->next;
			delete r;
		}
	}

	delete[] current_graph;
	delete[] visited;
}
/*
The Depth First Search recursive function, calls itself until it has found the target node
*/
bool DFS(GraphNode**& current_graph, bool*& visited, int startowy, int koncowy, int graph_matrix[INT_40][INT_20], int order[INT_40 * INT_20], int kolejny)

{
	GraphNode* p;
	visited[startowy] = true;
	if (startowy != koncowy) {
		order[kolejny] = startowy;
		kolejny++;
	}

	if (startowy == koncowy)
	{
		order[kolejny] = startowy;
		cout << "Funkcja znalazla droge.\n";
		return true;
	}
	for (p = current_graph[startowy]; p; p = p->next)
	{
		graph_matrix[startowy / 20][startowy % 20] = 2;
		if (!visited[p->node_number] && DFS(current_graph, visited, p->node_number, koncowy, graph_matrix, order, kolejny))
			return true;
	}
	return false;
}
/*
this function contains the main program loop
*/
void main_menu()
{
	int wybor;
	do
	{
		display_menu(1);
		cin >> wybor;
		switch (wybor)
		{
		case 1: robots_path();
			break;
		case 2:display_menu(2);
			break;
		case 3:exit(0);
			break;
		}
	} while (wybor != 3);


}
/*
displays selected menu
*/
void display_menu(int number)
{
	switch (number)
	{
	case 1:
		CLS;
			graphics(1);
		cout << setw(77) << "Wyznaczanie drogi robota przy uzyciu algorytmu typu Depth-First-Search\n"
			<< setw(60) << " By Damian Kakol and Krzysztof Dymanowski\n\n"
			<< "  Prosze wpisac number opcji ktora chce sie wybrac i wcisnac enter:\n"
			<< "  1. Prezentacja Algorytmu.\n"
			<< "  2. Krotkie objasnienie dzialania programu.\n"
			<< "  3. Wyjscie z programu.\n";
		graphics(2);
		graphics(3);
		break;
	case 2:
		CLS;
			graphics(1);
		cout << "  Graf, ktory tworzony jest na podstawie dwuwymiarowej tablicy i zapisany jako\n"
			<< "  dynamiczna lista sasiedztw wierzcholkow, przy pomocy rekurencyjnego wywolania funkcji\n"
			<< "  DFS, znajduje droge pomiedzy dwoma punktami na planszy o wymiarach 40 x 20\n"
			<< "  od punktu A do punktu B, poruszajac sie jedynie po polach bialych\n";
		graphics(2);
		graphics(3);
		PAUSE;
			break;
	case 3:
		graphics(1);
		cout << "Wybierz opcje wciskajac odpowiedni number i klikajac enter\n"
			<< "  1. Wyswietl Tablice segmentow\n"
			<< "  2. Wyswietl Plansze przed wyznaczeniem drogi\n"
			<< "  3. Wyswietl Liste sasiedztw wierzcholkow\n"
			<< "  4. Wyswietl Plansze po wyznaczeniu drogi\n"
			<< "  5. Wyswietl order odwiedzania wierzcholkow\n"
			<< "  6. Wyswietl number poczatkowego i koncowego wierzcholka\n"
			<< "  7. Wyczysc ekran\n"
			<< "  8. Wroc do menu glownego\n";
		break;
	}
}
/*
lists every node visited in chronological order
*/
void show_path(int order[INT_40 * INT_20],int koncowy)
{
	int i;
	for (i = 0; i < INT_40 * INT_20; i++) {
		if (order[i] == 800) continue;
		cout << order[i] << "->" << setw(6);
	}
	cout << " Ostatni (odwiedzony) GraphNode ma number: " << koncowy << "\n";
}
/*
displays the 40 x 20 board that represents the graph, either before or after the DFS algorithm has been called
*/
void show_graph(int graph_matrix[INT_40][INT_20])
{
	for (int i = 0; i < INT_40; i++) {
		for (int j = 0; j < INT_20; j++)
		{
			if (graph_matrix[i][j] == 0)
				cout << BLACK_SQUARE;
			else if (graph_matrix[i][j] == 1)
				cout << WHITE_SQUARE;
			else if (graph_matrix[i][j] == 2)
				cout << "+";
			else if (graph_matrix[i][j] == 3)
				cout << "A";
			else if (graph_matrix[i][j] == 4)
				cout << "B";
			else if (graph_matrix[i][j] == 5)
				cout << ROBOT_ICON;
		}
		cout << "\n";
	}
}
/*
contains the presentation part of the program
*/
void robots_path()
{
	int order[INT_40 * INT_20];
	int start = 0;
	int kolejny = start;
	srand(time(NULL));
	CLS;
	bool* visited;
	int R1, C1, R2, C2;
	int opcja;
	char Macierz[INT_8][INT_4];
	int graph_matrix[INT_40][INT_20];
	int MacierzPoWyznaczeniuDrogi[INT_40][INT_20];
	GraphNode** current_graph;
	for (int i = 0; i < INT_40 * INT_20; i++)
		order[i] = 800;

	generate_segments(Macierz);

	generate_graph(Macierz, graph_matrix);
	generate_graph(Macierz, MacierzPoWyznaczeniuDrogi);

	graph_init(graph_matrix, current_graph, visited);

	do {
		R1 = rand() % INT_40;
		C1 = rand() % INT_20;
	} while (graph_matrix[R1][C1] != 1);

	do {
		R2 = rand() % INT_40;
		C2 = rand() % INT_20;
	} while ((graph_matrix[R2][C2] != 1) && (R2 != R1) && (C2 != C1));

	int random_node = (R1 * INT_20) + C1;

	int current_target = (R2 * INT_20) + C2;
	cout << random_node << setw(5) << current_target << "\n";

	bool result = DFS(current_graph, visited, random_node, current_target, MacierzPoWyznaczeniuDrogi, order, kolejny);

	graph_matrix[R1][C1] = 5;
	graph_matrix[R2][C2] = 4;
	MacierzPoWyznaczeniuDrogi[R1][C1] = 3;
	MacierzPoWyznaczeniuDrogi[R2][C2] = 5;

	CLS;

		display_menu(3);

	do {
		cin >> opcja;
		switch (opcja)
		{
		case 1: show_segments(Macierz);
			PAUSE;
				break;
		case 2:show_graph(graph_matrix);
			PAUSE;
				break;
		case 3:show_nodes(current_graph);
			PAUSE;
				break;
		case 4:show_graph(MacierzPoWyznaczeniuDrogi);
			PAUSE;
				break;
		case 5:show_path(order,current_target);
			PAUSE;
				break;
		case 6: cout << " GraphNode poczatkowy ma number: " << random_node << " , a koncowy ma number: " << current_target << "\n";
			PAUSE;
				break;
		case 7: CLS;
			display_menu(3);
			break;
		case 8:
			break;
		}
	} while (opcja != 8);

	UsunGraf(current_graph, visited);
	PAUSE;
}

int main()
{
	main_menu();
	return 0;
}