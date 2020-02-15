#include "Cube.h"

Cube::Cube()
{

}


Cube::Cube(Pos start) :_pos(start)
{

}

Cube::Cube(Pos start, direction dir, int cnt):_pos(start)
{
	for (size_t i = 0; i < cnt; i++)
	{
		this->AddMove(dir);
	}
}

Cube::Cube(Pos start, const Cube& other, direction last):_pos(start)
{
	std::queue<direction> temp = other._aheadMoves;
	this->AddMove(last);
	while (!temp.empty())
	{
		this->AddMove(temp.front());
		temp.pop();
	}
}

Cube::~Cube()
{
	while (!this->_aheadMoves.empty())
	{
		this->_aheadMoves.pop();
	}
}

void Cube::Move()
{
	this->_pos.Move(this->_aheadMoves.front());
	this->_aheadMoves.pop();
}

void Cube::SetPos(Pos other)
{
	this->_pos = other;
}

Pos Cube::GetPos() const
{
	return this->_pos;
}

void Cube::AddMove(direction dir)
{
	this->_aheadMoves.push(dir);
}
