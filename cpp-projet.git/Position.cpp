#include "Position.hpp"

Position::Position() : x(OUT_POSITION), y(OUT_POSITION)
{
}

Position::Position(unsigned int _x, unsigned int _y) : x(_x), y(_y)
{
}

Position::~Position()
{
}

unsigned int Position::getX() const
{
	return x;
}

unsigned int Position::getY() const
{
	return y;
}

string Position::toString()
{
	return "Position{x = '" + to_string(x) + '\'' +
		", y = '" + to_string(y) + '\'' +
		"}";
}

bool Position::operator<(Position &pos) const
{
	return y < pos.y && x < pos.x;
}

ostream& operator<<(ostream& os, Position& pos)
{
	os << pos.toString();
	return os;
}
