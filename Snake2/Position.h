#pragma once

enum class direction
{
	LEFT,
	DOWN,
	RIGHT,
	UP
};

class Pos
{

public:
	Pos();
	Pos(int x, int y);
	~Pos();

	void Move(direction dir);
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);

private:
	int _x;
	int _y;

};