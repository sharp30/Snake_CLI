#pragma once

#include <queue>
#include "Position.h"

using std::queue;


class Cube
{
public:
	Cube();
	Cube(Pos start);
	Cube(Pos start, int dir, int cnt);
	Cube(Pos start, const Cube& other, int last);
	~Cube();
	void Move();
	void SetPos(Pos other);
	Pos GetPos() const;
	void AddMove(int dir);


private:
	Pos _pos;
	queue<int> _aheadMoves;
};