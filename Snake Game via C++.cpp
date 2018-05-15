#include <iostream>
#include <cstdlib>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int headX, headY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tailN;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup();
void Draw();
void Input();
void Logic();

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
	system("cls");
	cout << "GAME OVER!" << endl;
	return 0;
}

void Setup()
{
	gameOver = false;
	dir = STOP;
	headX = width - 38;
	headY = height - 18;
	fruitX = rand() % (width - 2);
	fruitY = rand() % (height - 2);
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width + 1; i++)
	{
		cout << "#";
	}

	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((j == 0) || (j == width - 1))
			{
				cout << "#";
			}
			if ((i == headY) && (j == headX))
			{
				cout << "O";
			}
			else if ((i == fruitY) && (j == fruitX))
			{
				cout << "@";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < tailN; k++)
				{
					if ((tailX[k] == j) && (tailY[k] == i))
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 1; i++)
	{
		for (int p = 0; p;)
			cout << "#";
	}
	cout << endl;
	cout << "Rezultatas: " << score << "." << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'q':
			gameOver = true;
			break;
		case 'A':
			dir = LEFT;
			break;
		case 'D':
			dir = RIGHT;
			break;
		case 'W':
			dir = UP;
			break;
		case 'S':
			dir = DOWN;
			break;
		case 'Q':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevTX = tailX[0];
	int prevTY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = headX;
	tailY[0] = headY;
	for (int i = 1; i < tailN; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevTX;
		tailY[i] = prevTY;
		prevTX = prev2X;
		prevTY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		headX--;
		break;
	case RIGHT:
		headX++;
		break;
	case UP:
		headY--;
		break;
	case DOWN:
		headY++;
		break;
	default:
		break;
	}

	if (headX < 0)
	{
		headX = headX + 39;
	}
	if (headY < 0)
	{
		headY = headY + 20;
	}
	if (headX > width - 2)
	{
		headX = headX - 39;
	}
	if (headY > height - 1)
	{
		headY = headY - 20;
	}
	for (int i = 0; i < tailN; i++)
	{
		if ((tailX[i] == headX) && (tailY[i] == headY))
		{
			gameOver = true;
		}
	}
	if ((headX == fruitX) && (headY == fruitY))
	{
		score++;
		fruitX = rand() % width;
		fruitY = rand() % height;
		tailN++;
	}
}
