#pragma once

#include <iostream>
#include <vector>
#include "Cube.h"
#include "Position.h"

using std::vector;


const char PART_KEY = '5';
const char EAT_KEY = 'o';
class Snake
{
public:
	Snake();
	Snake(char**& table, int size, direction startDir);
	~Snake();


	bool move(char** table, int& score, int size);
	int getLength() const;
	void addDir(direction dir);
private:
	vector<Cube> _parts;
	int _len;


};