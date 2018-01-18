#include "Monster.hpp"



Monster::Monster(Position _pos) : Character(_pos)
{
}

Monster::Monster(int health, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma) :
	Character(health, strength, dexterity, constitution, intelligence, wisdom, charisma)
{
}

Monster::Monster(int health, int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma, Position position) :
	Character(health, strength, dexterity, constitution, intelligence, wisdom, charisma, position)
{
}

Monster::~Monster()
{
}