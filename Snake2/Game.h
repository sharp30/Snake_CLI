#pragma once

#include "Snake.h"
#include <mutex>
#include <conio.h>

namespace level
{
	typedef enum level
	{
		EASY = 1,
		MEDIUM,
		HARD,
		LEGENDERY,
		IMPOSSIBLE
	}level;
};

enum class speed
{
	EASY = 800,
	MEDIUM =400,
	HARD = 100,
	LEGENDERY = 50,
	IMPOSSIBLE =20
};

using std::cout;

class Game
{
public:
	Game(int tableSize);
	int playGame();
	~Game();

private:
	void chooseLevel();
	void placeFood();
	void printBoard();//condition variable
	void getInput();
	void initial();

	std::condition_variable _printBoardCond;
	std::condition_variable _placeFoodCond;
	std::mutex _boardMutex;
	std::mutex _keyMutex;

	speed _speed;
	char** _board;
	Snake _snake;
	int _score;
	direction _dir;
	bool _game;
	const int _tableSize;
};