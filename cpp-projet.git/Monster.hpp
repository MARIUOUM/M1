#ifndef MONSTER_HPP_INCLUDED
#define MONSTER_HPP_INCLUDED

#include "Character.hpp"

#define DEFAULT_MONSTER_HEALTH			(rand() % 10 + 1)
#define DEFAULT_MONSTER_STRENGTH		(rand() % 10 + 1)
#define DEFAULT_MONSTER_DEXTERITY		(rand() % 10 + 1)
#define DEFAULT_MONSTER_CONSTITUTION	(rand() % 10 + 1)
#define DEFAULT_MONSTER_INTELLIGENCE	(rand() % 10 + 1)
#define DEFAULT_MONSTER_WISDOM 			(rand() % 10 + 1)
#define DEFAULT_MONSTER_CHARISMA 		(rand() % 10 + 1)

class Monster : public Character
{
public:
	Monster(Position);
	Monster(int, int, int, int, int, int, int);
	Monster(int, int, int, int, int, int, int, Position);
	virtual ~Monster();

};

#endif