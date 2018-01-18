#include "DynamicMonster.hpp"



DynamicMonster::DynamicMonster(Position _pos) : 
	Monster(DEFAULT_MONSTER_HEALTH, DEFAULT_MONSTER_STRENGTH, DEFAULT_MONSTER_DEXTERITY,
		DEFAULT_MONSTER_CONSTITUTION, DEFAULT_MONSTER_INTELLIGENCE,
		DEFAULT_MONSTER_WISDOM, DEFAULT_MONSTER_CHARISMA, _pos)
{
}

DynamicMonster::DynamicMonster(int health, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma) :
	Monster(health, strength, dexterity, constitution, intelligence, wisdom, charisma)
{
}

DynamicMonster::DynamicMonster(int health, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma, Position position) :
	Monster(health, strength, dexterity, constitution, intelligence, wisdom, charisma, position)
{
}


DynamicMonster::~DynamicMonster()
{
}