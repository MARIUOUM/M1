#ifndef DYNAMMIC_MONSTER_HPP_INCLUDED
#define DYNAMMIC_MONSTER_HPP_INCLUDED

#include "Monster.hpp"

class DynamicMonster : public Monster
{
public:
	DynamicMonster(Position);
	DynamicMonster(int, int, int, int, int, int, int);
	DynamicMonster(int, int, int, int, int, int, int, Position);
	~DynamicMonster();

	string move(int, int);
};

#endif