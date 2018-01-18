#include "SquareBuilder.hpp"


vector<Square*> SquareBuilder::buildFromString(int width, int y, string str)
{
	vector<Square*> sq = vector<Square*>();
	int x = 0, i = 0;

	for (string::iterator it = str.begin(); it != str.end(); ++it)
	{	
		if ((*it) == Square::EMPTY && i % 2 == 0)
			sq.push_back(new Square(x++, y, SquareType::EMPTY));
		else if ((*it) == Square::BEGIN)
			sq.push_back(new Square(x++, y, SquareType::BEGIN));
		else if ((*it) == Square::END)
			sq.push_back(new Square(x++, y, SquareType::END));
		else if ((*it) == Square::MONSTER)
			sq.push_back(new Square(x++, y, SquareType::MONSTER));
		else if ((*it) == Square::PLAYER)
			sq.push_back(new Square(x++, y, SquareType::PLAYER));
		else if ((*it) == Square::WALL)
			sq.push_back(new Square(x++, y, SquareType::WALL));
		//cout << *it;
		i++;
	}

	//cout << endl;

	return sq;
}
