/*
	Delvis Kouete
	Computer Science Fall 2024
	Due: Dec. 17, 2024
	Lab Name: Lab 7 Battleship
	For this lab you will make a simple battleship game. 
	*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int GRID_SIZE = 10;
const int NUM_SHIPS = 5;

const char WATER = '~';
const char SHIP = 'S';
const char HIT = 'X';
const char MISS = 'O';


void initializeGrid(char grid[GRID_SIZE][GRID_SIZE]);
void printGrid(const char grid[GRID_SIZE][GRID_SIZE]);
void placeComputerShips(char grid[GRID_SIZE][GRID_SIZE]);
bool placeUserShip(char grid[GRID_SIZE][GRID_SIZE], int x, int y, int size, bool vertical);
bool fire(char grid[GRID_SIZE][GRID_SIZE], int x, int y);
bool checkVictory(char grid[GRID_SIZE][GRID_SIZE]);
bool isValid(int x, int y);
void displayGameStatus(char unserGrid[GRID_SIZE][GRID_SIZE], char compGrid[GRID_SIZE][GRID_SIZE], int userHits, int compHits);


int main()
{
	srand(time(0));

	char userGrid[GRID_SIZE][GRID_SIZE], compGrid[GRID_SIZE][GRID_SIZE];
	initializeGrid(userGrid);
	initializeGrid(compGrid);

	placeComputerShips(compGrid);


	cout << "Place your ships on the grid. \n";
	for (int i = 0; i < NUM_SHIPS; ++i)
	{
		int x, y, size = 3;
		char direction;
		bool vertical;

		printGrid(userGrid);
		cout << "Enter coordiantes (x,y) to place ship #" << i + 1 << " (Size: " << size << "): ";
		cin >> x >> y;
		cout << "Enter direction (v for vertical, h for horizontal): ";
		cin >> direction;
		vertical = (direction == 'v' || direction == 'V');

		while (!placeUserShip(userGrid, x, y, size, vertical))
		{
			cout << "Invalid placement! Try again. \n";
			cout << "Enter coordinates (x,y) to place ship #" << i + 1 << " (Size: " << size << "): ";
			cin >> x >> y;
			cout << "Enter direction (v for vertical, h for horizontal): ";
			cin >> direction;
			vertical = (direction == 'v' || direction == 'V');
		}
	}

	int userHits = 0, compHits = 0;
	bool gameRunning = true;

	while (gameRunning)
	{
		int x, y;

		x = rand() % GRID_SIZE;
		y = rand() % GRID_SIZE;
		while (compGrid[y][x] == HIT || compGrid[y][x] == MISS)
		{
			x = rand() % GRID_SIZE;
			y = rand() % GRID_SIZE;
		}
		if (fire(userGrid, x, y))
		{
			cout << "Computer fired at (" << x << ", " << y << ") and HIT! \n";
			compHits++;
		}
		else
		{
			cout << "Computer fired at (" << x << ", " << y << ") and MISSED.\n";
		}

		if (checkVictory(userGrid))
		{
			cout << "The computer wins! All your ships are destroyed.\n";
			gameRunning = false;
			break;
		}

		cout << "Your turn! Enter coordinates to fire (x,y): ";
		cin >> x >> y;
		while (!isValid(x, y) || userGrid[y][x] == HIT || userGrid[y][x] == MISS)
		{
			cout << "Invalid or already fired coordinates. Try again: ";
			cin >> x >> y;
		}
		if (fire(compGrid, x, y))
		{
			cout << "You fired at (" << x << ", " << y << ") and HIT!\n";
			userHits++;
		}
		else
		{
			cout << "You fired at (" << x << ", " << y << ") and MISSED.\n";
		}

		if (checkVictory(compGrid))
		{
			cout << "You win! All computer ships are destroyed.\n";
			gameRunning = false;
			break;
		}

		displayGameStatus(userGrid, compGrid, userHits, compHits);
	}
	return 0;
}

void initializeGrid(char grid[GRID_SIZE][GRID_SIZE])
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			grid[i][j] = WATER;
		}
	}
}

void printGrid(const char grid[GRID_SIZE][GRID_SIZE])
{
	cout << " ";
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		cout << i << " ";
	}
	cout << endl;

	for (int i = 0; i < GRID_SIZE; ++i)
	{
		cout << i << " ";
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}

void placeComputerShips(char grid[GRID_SIZE][GRID_SIZE])
{
	int shipsPlaced = 0;
	while (shipsPlaced < NUM_SHIPS)
	{
		int x = rand() % GRID_SIZE;
		int y = rand() % GRID_SIZE;
		bool vertical = rand() % 2;

		if (placeUserShip(grid, x, y, 3, vertical))
		{
			shipsPlaced++;
		}
	}
}

bool placeUserShip(char grid[GRID_SIZE][GRID_SIZE], int x, int y, int size, bool vertical)
{
	if (vertical)
	{
		if (y + size > GRID_SIZE) return false;
		for (int i = 0; i < size; ++i)
		{
			if (grid[y + i][x] == SHIP) return false;
		}
		for (int i = 0; i < size; ++i)
		{
			grid[y + i][x] = SHIP;
		}
	}
	else
	{
		if (x + size > GRID_SIZE) return false;
		for (int i = 0; i < size; ++i)
		{
			if (grid[y][x + i] == SHIP) return false;
		}
		for (int i = 0; i < size; ++i)
		{
			grid[y][x + i] = SHIP;
		}
	}
	return true;
}

bool fire(char grid[GRID_SIZE][GRID_SIZE], int x, int y)
{
	if (grid[y][x] == SHIP)
	{
		grid[y][x] = HIT;
		return true;
	}
	else
	{
		grid[y][x] = MISS;
		return false;
	}
}

bool checkVictory(char grid[GRID_SIZE][GRID_SIZE])
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		for (int j = 0; j < GRID_SIZE; ++j)
		{
			if (grid[i][j] == SHIP) return false;
		}
	}
	return true;
}

bool isValid(int x, int y)
{
	return (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE);
}

void displayGameStatus(char userGrid[GRID_SIZE][GRID_SIZE], char compGrid[GRID_SIZE][GRID_SIZE], int userHits, int compHits)
{
	cout << "\nUser's grid:\n";
	printGrid(userGrid);
	cout << "\nComputer's grid:\n";
	printGrid(compGrid);
	cout << "User Hits: " << userHits << " | Computer Hits: " << compHits << endl;
}