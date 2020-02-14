#include "Position.h"

Pos::Pos()
{
	this->_x = 0;
	this->_y = 0;
}

Pos::Pos(int x, int y)
{
	this->_x = x;
	this->_y = y;
}

Pos::~Pos() = default;

void Pos::Move(direction dir)
{
	switch (dir)
	{
	case direction::UP:
		this->_x++;
		break;
	case direction::DOWN:
		this->_x--;
		break;
	case direction::RIGHT:
		this->_y++;
		break;
	case direction::LEFT:
		this->_y--;
		break;
	default:
		break;
	}
}

int Pos::getX() const
{
	return this->_x;
}

int Pos::getY() const
{
	return this->_y;
}

void Pos::setX(int x)
{
	this->_x = x;
}

void Pos::setY(int y)
{
	this->_y = y;
}
