#pragma once

#include "Snake.h"
#include <mutex>
#include <conio.h>
using std::cout;

class Game
{
public:
	Game(int tableSize);
	int playGame();
	~Game();

private:
	void placeFood();
	void printBoard();//condition variable
	void getInput();
	void initial();

	std::condition_variable _printBoardCond;
	std::condition_variable _placeFoodCond;
	std::mutex _boardMutex;
	std::mutex _keyMutex;

	char** _board;
	Snake _snake;
	int _score;
	direction _dir;
	bool _game;
	const int _tableSize;
};