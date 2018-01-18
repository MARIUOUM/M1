#ifndef SQUARE_BUILDER_HPP_INCLUDED
#define SQUARE_BUILDER_HPP_INCLUDED

#include "libs.hpp"
#include "Square.hpp"

class SquareBuilder
{
public:
	static vector<Square*>  buildFromString(int width, int y, string str);
};

#endif