#include "Game.h"
#include <thread>
#include <iostream>

Game::Game(const int tableSize): _tableSize(tableSize)
{
	
	this->_board = new char*[_tableSize];
	for (int i = 0; i < _tableSize; i++)
	{
		this->_board[i] = new char[i];
	}
	
	this->_score = 0;

}

int Game::playGame()
{
	//initial values

	this->initial();

	std::thread t = std::thread(&Game::getInput, this);
	while (this->_game)
	{
		this->_snake.addDir(this->_dir);
		this->_game = this->_snake.move(this->_board, this->_score,this->_tableSize);
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
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

void Game::printBoard()
{
	while (true)
	{
		std::unique_lock<std::mutex> l(this->_boardMutex);
		this->_printBoardCond.wait(l);
		system("cls");
		for (int row = 0; row < this->_tableSize; row++)
		{
			for (size_t i = 0; i < _tableSize; i++)
			{
				cout << '_';
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
		for (size_t i = 0; i < _tableSize; i++)
		{
			cout << '_';
		}
	}

}

void Game::getInput()
{
	while (true)
	{
		while (!_kbhit())
		{

		}
		char key = _getch();
		if (key >= 37 && key <= 40)
		{
			this->_dir = int(key - 37);
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
	this->_dir = RIGHT;
	this->_snake = Snake(this->_board,_tableSize > 8? 4:_tableSize/2,this->_dir);
}
