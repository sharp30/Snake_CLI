#pragma once

typedef enum direction
{
	LEFT = 0,
	UP,
	RIGHT,
	DOWN
}direction;

class Pos
{
public:
	Pos();
	Pos(int x, int y);
	~Pos();

	void Move(int dir);
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
private:
	int _x;
	int _y;

};