#ifndef STATIC_MONSTER_HPP_INCLUDED
#define STATIC_MONSTER_HPP_INCLUDED

#include "Monster.hpp"

class StaticMonster : public Monster
{
public:
	StaticMonster(Position);
	StaticMonster(int, int, int, int, int, int, int);
	StaticMonster(int, int, int, int, int, int, int, Position);
	~StaticMonster();
};

#endif