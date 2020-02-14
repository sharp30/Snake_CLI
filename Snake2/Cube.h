#pragma once

#include <queue>
#include "Position.h"

using std::queue;


class Cube
{
public:
	Cube();
	Cube(Pos start);
	Cube(Pos start, direction dir, int cnt);
	Cube(Pos start, const Cube& other, direction last);
	~Cube();
	void Move();
	void SetPos(Pos other);
	Pos GetPos() const;
	void AddMove(direction dir);


private:
	Pos _pos;
	queue<direction> _aheadMoves;
};