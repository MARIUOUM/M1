#include "Map.hpp"

Map::Map(int w, int h) : width(w), height(h), begin(Position()), end(Position()), atEnd(false), sq(vector<vector<Square*>>()), monsters(vector<Monster*>())
{
}

Map::~Map()
{
	for (vector<vector<Square*>>::iterator it = sq.begin(); it != sq.end(); it++)
	{
		for (vector<Square*>::iterator val = it->begin(); val != it->end(); val++)
		{
			delete (*val);
		}
		it->clear();
	}
	sq.clear();

	for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); it++)
	{
		delete(*it);
	}
	monsters.clear();
}

Position Map::getPositionBegin() const
{
	return begin;
}

Position Map::getPositionEnd() const
{
	return end;
}

bool Map::getAtEnd() const
{
	return atEnd;
}

vector<Monster*> Map::getMonsters()
{
	return monsters;
}

int Map::getRemainingMonsters()
{
	int nb = 0;

	for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); it++)
	{
		if (!(*it)->isDead())
			nb++;
	}
	return nb;
}

unsigned int Map::getRows() const
{
	return sq.size();
}

unsigned int Map::getColumnsFromARow(int i) const
{
	return sq.at(i).size();
}

void Map::setPositionBegin(Position b)
{
	begin = b;
}

void Map::setPositionEnd(Position e)
{
	end = e;
}

void Map::setAtEnd(bool ae)
{
	atEnd = ae;
}

void Map::initPositionsAndCharacters()
{
	int i = 0;
	for (vector<vector<Square*>>::iterator it = sq.begin(); it != sq.end(); it++)
	{
		for (vector<Square*>::iterator val = it->begin(); val != it->end(); val++)
		{
			if ((*val)->getType() == SquareType::BEGIN)
				setPositionBegin(Position((*val)->getX(), (*val)->getY()));
			else if ((*val)->getType() == SquareType::END)
				setPositionEnd(Position((*val)->getX(), (*val)->getY()));
			else if ((*val)->getType() == SquareType::MONSTER)
			{
				if (DYNAMIC_MONSTER(i))
					monsters.push_back(new DynamicMonster(Position((*val)->getX(), (*val)->getY())));
				else if (TELEPORTER_MONSTER(i))
					monsters.push_back(new TeleporterMonster(Position((*val)->getX(), (*val)->getY())));
				else
					monsters.push_back(new StaticMonster(Position((*val)->getX(), (*val)->getY())));

				i++;
			}
		}
	}

}

void Map::initViewPlayer(Player *p)
{
	Position pos = p->getPosition();

	if (pos.getY() == (sq.size() - 1))
		p->setCurrentView(p->NORTH_VIEW);
	else if (pos.getY() == 0)
		p->setCurrentView(p->SOUTH_VIEW);
	else if (pos.getX() == 0)
		p->setCurrentView(p->EAST_VIEW);
	else if (pos.getX() == sq.at(pos.getY()).size() - 1)
		p->setCurrentView(p->WEST_VIEW);
}

void Map::addSquares(vector<Square*> _sq)
{
	sq.push_back(_sq);
}

void Map::drawMap(bool player)
{

	for (vector<vector<Square*>>::iterator it = sq.begin(); it != sq.end(); it++)
	{
		for (vector<Square*>::iterator val = it->begin(); val != it->end(); val++)
		{
			if ((*val)->getType() == SquareType::BEGIN)
				cout << Square::BEGIN;
			else if ((*val)->getType() == SquareType::END)
				cout << Square::END;
			else if ((*val)->getType() == SquareType::MONSTER)
				if (!player)
					cout << Square::MONSTER;
				else
					cout << Square::EMPTY;
			else if ((*val)->getType() == SquareType::PLAYER)
				cout << Square::PLAYER;
			else if ((*val)->getType() == SquareType::WALL)
				cout << Square::WALL;
			else if ((*val)->getType() == SquareType::EMPTY)
				cout << Square::EMPTY;

			cout << Square::EMPTY;
		}
		cout << endl;
	}

	cout << "Monsters : " << monsters.size() << endl;
}

void Map::drawPlayerHub(Player *p)
{
	Position pos = p->getPosition();
	Square* square;
	Position front1, front2, left, right, front_left, front_right;
	string str = "";

	if (p->getCurrentView() == p->NORTH_VIEW)
	{
		front1 = Position(pos.getX(), pos.getY() - 1);
		left = Position(pos.getX() - 1, pos.getY());
		right = Position(pos.getX() + 1, pos.getY());
		front_left = Position(front1.getX() - 1, front1.getY());
		front_right = Position(front1.getX() + 1, front1.getY());
		 
		if (pos.getY() - 1 >= 0)
		{
			square = getSquare(front1);

			if (square->getType() == SquareType::EMPTY && (pos.getY() - 2 >= 0))
			{
				front2 = Position(pos.getX(), pos.getY() - 2);
				str += "   " + getSquare(front2)->getStringType() + "\n";
			}

			str += " " + getSquare(front_left)->getStringType() + " " + square->getStringType() + " " + getSquare(front_right)->getStringType() + "\n";
		}

		str += " " + getSquare(left)->getStringType() + " " + getSquare(pos)->getStringType() + " " + getSquare(right)->getStringType() + "\n";


	}
	else if (p->getCurrentView() == p->SOUTH_VIEW)
	{
		front1 = Position(pos.getX(), pos.getY() + 1);
		left = Position(pos.getX() - 1, pos.getY());
		right = Position(pos.getX() + 1, pos.getY());

		front_left = Position(front1.getX() - 1, front1.getY());
		front_right = Position(front1.getX() + 1, front1.getY());

		str += " " + getSquare(left)->getStringType() + " " + getSquare(pos)->getStringType() + " " + getSquare(right)->getStringType() + "\n";

		if (pos.getY() + 1 < sq.size())
		{
			square = getSquare(front1);

			str += " " + getSquare(front_left)->getStringType() + " " + square->getStringType() + " " + getSquare(front_right)->getStringType() + "\n";

			if (square->getType() == SquareType::EMPTY && (pos.getY() + 2 < sq.size()))
			{
				front2 = Position(pos.getX(), pos.getY() + 2);
				str += "   " + getSquare(front2)->getStringType() + "\n";
			}

		}
	}
	else if (p->getCurrentView() == p->WEST_VIEW)
	{
		front1 = Position(pos.getX() - 1, pos.getY());
		left = Position(pos.getX(), pos.getY() + 1);
		right = Position(pos.getX(), pos.getY() - 1);

		front_left = Position(front1.getX(), front1.getY() + 1);
		front_right = Position(front1.getX(), front1.getY() - 1);

		str += "  " + getSquare(front_right)->getStringType() + " " + getSquare(right)->getStringType() + "\n";

		if (pos.getX() - 1 >= 0)
		{
			square = getSquare(front1);

			if (square->getType() == SquareType::EMPTY && pos.getX() - 2 >= 0)
			{
				front2 = Position(pos.getX() - 2, pos.getY());
				str += getSquare(front2)->getStringType();
			}
			else
				str += " ";

			str += " " + square->getStringType() + " " + getSquare(pos)->getStringType() + "\n";
		}
		else
			str += "    " + getSquare(pos)->getStringType() + "\n";

		str += "  " + getSquare(front_left)->getStringType() + " " + getSquare(left)->getStringType() + "\n";
	}
	else if (p->getCurrentView() == p->EAST_VIEW)
	{
		front1 = Position(pos.getX() + 1, pos.getY());
		left = Position(pos.getX(), pos.getY() - 1);
		right = Position(pos.getX(), pos.getY() + 1);
		square = getSquare(front1);

		front_left = Position(front1.getX(), front1.getY() - 1);
		front_right = Position(front1.getX(), front1.getY() + 1);


		str += getSquare(left)->getStringType() + " " + getSquare(front_left)->getStringType() + "\n";

		str += getSquare(pos)->getStringType();

		if (pos.getX() + 1 < sq.at(pos.getY()).size())
		{
			str += " " + square->getStringType();
			if (square->getType() == SquareType::EMPTY && pos.getX() + 2 < sq.at(pos.getY()).size())
			{
				front2 = Position(pos.getX() + 2, pos.getY());
				str += " " + getSquare(front2)->getStringType();
			}
		}

		str += "\n" + getSquare(right)->getStringType() + " " + getSquare(front_right)->getStringType() + "\n";
	}
	cout << str;
	cout << *p << endl;

}

Square * Map::getSquare(Position&p)
{
	return sq.at(p.getY()).at(p.getX());
}

Monster * Map::getMonster(Position &p)
{
	for (vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); it++)
	{
		if ((*it)->getPosition().getX() == p.getX() && (*it)->getPosition().getY() == p.getY())
			return (*it);
	}
	return nullptr;
}