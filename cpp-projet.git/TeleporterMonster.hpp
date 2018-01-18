#ifndef TELEPORTER_MONSTER_HPP_INCLUDED
#define TELEPORTER_MONSTER_HPP_INCLUDED

#include "Monster.hpp"

class TeleporterMonster : public Monster
{
public:
	TeleporterMonster(Position);
	TeleporterMonster(int, int, int, int, int, int, int);
	TeleporterMonster(int, int, int, int, int, int, int, Position);
	~TeleporterMonster();
};

#endif