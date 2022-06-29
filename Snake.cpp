#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
int d;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
void Setup() //Sets up the game
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	cout<<"Welcome to Snake :)\nPlease choose your difficulty between 1, 2 and 3(1 - Hard, 3 - Easy):";
	cin>>d;
}
void Draw()  //The drawing function for every iteration
{
	system("cls"); 
	for (int i = 0; i < width+2; i++)
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
				cout << "F";
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

	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
	cout<<"Press x to exit the game";
}
void Input()  //Function for using input from keyboard
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if(dir==RIGHT) break;
			dir = LEFT;
			break;
		case 'd':
			if(dir==LEFT) break;
			dir = RIGHT;
			break;
		case 'w':
			if(dir==DOWN) break;
			dir = UP;
			break;
		case 's':
			if(dir==UP) break;
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()  //Logic segment for game rules
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
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
	Setup();
	Sleep(100);
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(10*d);
	}
	cout<<"\nGAME OVER || Thank you for playing :)";
	return 0;
}