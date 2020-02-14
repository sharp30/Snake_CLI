#pragma once

#include <iostream>
#include <vector>
#include "Cube.h"
#include "Position.h"
#include <mutex>
using std::vector;


const char PART_KEY = '5';
const char EAT_KEY = '4';
class Snake
{
public:
	Snake();
	Snake(char**& table, int size, direction startDir);
	~Snake();

	bool move(char** table, int& score, int size, std::condition_variable& foodCond);
	int getLength() const;
	void addDir(direction dir);
private:
	vector<Cube> _parts;
	int _len;


};