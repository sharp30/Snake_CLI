#include "Game.h"
#include <thread>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>

Game::Game(const int tableSize): _tableSize(tableSize)
{
	srand(time(NULL));
	this->_board = new char*[_tableSize];
	for (int i = 0; i < _tableSize; i++)
	{
		this->_board[i] = new char[_tableSize];
	}
	this->_dir = direction::UP;
	this->_score = 0;
	this->_speed = speed::EASY;
}

int Game::playGame()
{
	//initial values

	this->initial();

	std::thread tInput = std::thread(&Game::getInput, this);
	tInput.detach();
	std::thread tPrint = std::thread(&Game::printBoard, this);
	std::thread tFood = std::thread(&Game::placeFood, this);
	tFood.detach();
	while (this->_game)
	{
		{
			std::lock_guard<std::mutex> l(this->_keyMutex);
			this->_snake.addDir(this->_dir);
		}
		this->_game = this->_snake.move(this->_board, this->_score,this->_tableSize,this->_placeFoodCond);
		this->_printBoardCond.notify_one();
		std::this_thread::sleep_for(std::chrono::milliseconds((int)this->_speed));
	}
	tPrint.join();

	return this->_score;
}

Game::~Game()
{
	for (int i = 0; i < _tableSize; i++)
	{
		free(this->_board[i]);
	}
	free(_board);
	this->_score = 0;
}

void Game::chooseLevel()
{
	cout << "Please Choose your level : " << std::endl;
	int choice = 0;
	while (choice < level::EASY|| choice > level::IMPOSSIBLE)
	{

		cout << "Easy - press "<<level::EASY << std::endl;
		cout << "Medium - press " <<level::MEDIUM<< std::endl;
		cout << "Hard - press " << level::HARD<<std::endl;
		cout << "Legendery - press " << level::LEGENDERY<<std::endl;
		cout << "Impossible - press " <<level::IMPOSSIBLE <<std::endl;
		std::cin >> choice;
	}
	switch (choice)
	{
	case level::EASY:
		this->_speed = speed::EASY;
		break;
	case level::MEDIUM:
		this->_speed = speed::MEDIUM;
		break;
	case level::HARD:
		this->_speed = speed::HARD;
		break;
	case level::LEGENDERY:
		this->_speed = speed::LEGENDERY;
		break;
	case level::IMPOSSIBLE:
		this->_speed = speed::IMPOSSIBLE;
		break;
	default:
		break;
	}
	system("cls");
}

void Game::placeFood()
{
	while (true)
	{
		std::unique_lock<std::mutex> l(this->_boardMutex);
		bool placed = false;
		while (!placed)
		{
			Pos pos(rand() % this->_tableSize, rand() % this->_tableSize);
			if (this->_board[pos.getX()][pos.getY()] == ' ')
			{
				this->_board[pos.getX()][pos.getY()] = EAT_KEY;
				placed = true;
			}
		}
		//this->_printBoardCond.notify_one();
		//TO DO: FIX THIS FUCK OF CODE 
		this->_placeFoodCond.wait(l);
	}
}
void clearScreen()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void Game::printBoard()
{
	while (this->_game)
	{
		std::unique_lock<std::mutex> l(this->_boardMutex);
		this->_printBoardCond.wait(l);
		clearScreen();
		cout << "			SCORE:	" << this->_score << std::endl << std::endl;
		for (int row = 0; row < this->_tableSize; row++)
		{
			for (size_t i = 0; i < _tableSize; i++)
			{
				cout << " _ ";
			}
			cout << std::endl;

			for (int col = 0; col < this->_tableSize; col++)
			{
				cout << '|';
				cout << this->_board[row][col];
				cout << '|';
			}
			cout << std::endl;
		}
	}
}

void Game::getInput()
{
	const int values[] = { 75, 72, 77, 80 };
	while (true)
	{
		while (!_kbhit())
		{

		}
		char key = _getch();
		for (size_t i = 0; i < 4; i++)
		{
			if(key == values[i])
			{
				{
					std::lock_guard<std::mutex> l(this->_keyMutex);

					this->_dir = direction(i);
					
				}
				break;
			}
		}
	}
}

void Game::initial()
{
	this->_score = 0;
	this->_game = true;
	
	for (int row = 0; row < this->_tableSize; row++)
	{
		for (int col = 0;  col < this->_tableSize; col++)
		{
			this->_board[row][col] = ' ';
		}
	}
	this->_dir = direction::RIGHT;
	this->_snake = Snake(this->_board,_tableSize > 8? 4:_tableSize/2,this->_dir);

	this->chooseLevel();
}
