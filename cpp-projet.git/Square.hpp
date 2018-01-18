#ifndef SQUARE_HPP_INCLUDED
#define SQUARE_HPP_INCLUDED

#include "libs.hpp"

enum class SquareType
{
	WALL = '#',
	PLAYER = 'P',
	MONSTER = 'M',
	BEGIN = 'B',
	END = 'E',
	EMPTY = ' ',
};

class Square
{
private:
	int x;
	int y;
	SquareType type;

public:
	static char const WALL = '#';
	static char const PLAYER = 'P';
	static char const MONSTER = 'M';
	static char const BEGIN = 'B';
	static char const END = 'E';
	static char const EMPTY = ' ';

	Square(int, int, SquareType);
	~Square();

	int getX() const;
	int getY() const;
	SquareType getType() const;
	string getStringType() const;

	void setType(SquareType);

	string toString();
	friend ostream& operator<<(ostream&, Square&);
};

#endif