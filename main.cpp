#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
Direction dir;

void Setup()
{
	srand((int)time(0));

	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Update()
{
	system("cls"); 
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";

			if (i == y && j == x)
				cout << "O";

			else if (i == fruitY && j == fruitX)
				cout << "@";

			else
			{
				bool print = false;

				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}

				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";

	cout << endl;
	cout << "Score: " << score << endl;
}
void Input()
{
	switch (_getch())
	{
		case 'w':
			dir = UP;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'a':
			dir = LEFT;
			break;

		case 'd':
			dir = RIGHT;
			break;

		case '`':
			gameOver = true;
			break;

		default:
			break;
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
		case UP:
			y--;
			break;

		case DOWN:
			y++;
			break;

		case LEFT:
			x--;
			break;

		case RIGHT:
			x++;
			break;

		default:
			break;
	}

	if (x > width || x < 0 || y > height || y < 0)
	{
		gameOver = true;
	}

	if (x == fruitX && y == fruitY)
	{
		score++;
		nTail++;

		srand((int)time(0));

		fruitX = rand() % width;
		fruitY = rand() % height;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}
}

int main()
{
	ofstream out;
	ifstream in;
	string file = "Scores.txt";
	string name;
	string players[100];
	int highscores[100];
	int count = 0;

	in.open(file);
	
	if (in.fail())
	{
		cout << "Open fail" << endl;
		exit(1);
	}

	while (!in.eof())
	{
		in >> players[count];
		in >> highscores[count];

		count++;
	}

	in.close();

	Setup();
	
	while (gameOver == false) //Game loop
	{
		Update();
		Input();
		Logic();
	}

	out.open(file);

	if (out.fail())
	{
		cout << "Out fail" << endl;
		exit(2);
	}
	
	cout << "\nEnter your name: ";
	cin >> name;

	players[count] = name;
	highscores[count] = score;

	int first, temp;
	string str;

	for (int i = count; i > 0; i--) // Selection sort decending
	{
		first = 0;

		for (int j = 1; j <= i; j++)
		{
			if (highscores[j] < highscores[first])
			{
				first = j;
			}
		}

		temp = highscores[first];
		highscores[first] = highscores[i];
		highscores[i] = temp;

		str = players[first];
		players[first] = players[i];
		players[i] = str;
	}


	for (int i = 0; i < count; i++)
	{
		out << players[i] << " " << highscores[i] << endl;
	}

	out.close();

	return 0;
}