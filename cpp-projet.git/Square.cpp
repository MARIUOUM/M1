#include "Square.hpp"


Square::Square(int _x, int _y, SquareType _type) : x(_x), y(_y), type(_type)
{
}

Square::~Square()
{
}

int Square::getX() const
{
	return x;
}

int Square::getY() const
{
	return y;
}

SquareType Square::getType() const
{
	return type;
}

string Square::getStringType() const
{
	if (type == SquareType::BEGIN)
		return "B";
	else if (type == SquareType::END)
		return "E";
	else if (type == SquareType::MONSTER)
		return "M";
	else if (type == SquareType::PLAYER)
		return "P";
	else if (type == SquareType::WALL)
		return "W";
	else if (type == SquareType::EMPTY)
		return "+";
	else
		return nullptr;
}

void Square::setType(SquareType t)
{
	type = t;
}

string Square::toString()
{
	return "Square{x = '" + to_string(x) + '\'' +
		", y = '" + to_string(y) + '\'' +
		", type = '" + getStringType() + '\'' +
		"}";
}

ostream & operator<<(ostream &os, Square &sq)
{
	os << sq.toString();
	return os;
}
