#include "Snake.h"

Snake::Snake()
{
	this->_len = 0;
}

Snake::Snake(char**& table, int size,int startDir)
{
	this->_len = size;
	Pos first(0,size-1);
	for (size_t i = 0; i < size; i++)
	{
		this->_parts.push_back(Cube(first, startDir, i + 1));
		table[first.getX()][first.getY()] = PART_KEY;
		first.Move(LEFT);
	}
}

Snake::~Snake()
{
	this->_len = 0;
	while (this->_parts.empty())
	{
		this->_parts.pop_back();
	}
}

bool Snake::move(char** table, int& score,int size)//, bool grow)
{
	Pos pre;
	bool cond = true;
	bool eaten = false;
	int i = 0;
	for (i = 0; i < this->_parts.size(); i++)
	{
		pre = this->_parts[i].GetPos();
		this->_parts[i].Move();
		Pos after = this->_parts[i].GetPos();
		//if out_of_table_bounds
		if (after.getX() >= size || after.getX() < 0 || after.getY() >= size || after.getY() < 0)
		{
			return false;
		}
		else if (table[after.getX()][after.getY()] == PART_KEY)
		{
			cond = false;
		}
		eaten = eaten || (cond && table[after.getX()][after.getY()] == EAT_KEY);
		//put in table
		table[after.getX()][after.getY()] = PART_KEY;
	}
	if (eaten)
	{
		score += 5;
		Cube lastCube = this->_parts[i - 1];
		Pos last =lastCube.GetPos();
		int dir= last.getX() > pre.getX() ? RIGHT : last.getX() < pre.getX() ? LEFT : last.getY() > pre.getY() ? UP : DOWN;
		this->_parts.push_back(Cube(pre, lastCube, dir));
	}
	return cond;
}

int Snake::getLength() const
{
	return this->_len;
}

void Snake::addDir(int dir)
{
	for (size_t i = 0; i < this->_parts.size(); i++)
	{
		this->_parts[i].AddMove(dir);
	}
}
