#ifndef POSITION_HPP_INCLUDED
#define POSITION_HPP_INCLUDED

#include "libs.hpp"

#define OUT_POSITION 10000

class Position
{
private:
	unsigned int x;
	unsigned int y;

public:
	Position();
	Position(unsigned int, unsigned int);
	~Position();

	unsigned int getX() const;
	unsigned int getY() const;

	string toString();
	bool operator<(Position&) const;
	friend ostream& operator<<(ostream&, Position&);
};

#endif
