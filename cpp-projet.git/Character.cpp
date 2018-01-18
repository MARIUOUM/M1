#include "Character.hpp"
#include "Player.hpp"
#include "Monster.hpp"

int Character::count = 0;

Character::Character() :
	id(++count), health(DEFAULT_HEALTH), strength(DEFAULT_STRENGTH), dexterity(DEFAULT_DEXTERITY),
	constitution(DEFAULT_CONSTITUTION), intelligence(DEFAULT_INTELLIGENCE),
	wisdom(DEFAULT_WISDOM), charisma(DEFAULT_CHARISMA), position(Position())
{
}

Character::Character(Position _pos) :
	id(++count), health(DEFAULT_HEALTH), strength(DEFAULT_STRENGTH), dexterity(DEFAULT_DEXTERITY),
	constitution(DEFAULT_CONSTITUTION), intelligence(DEFAULT_INTELLIGENCE),
	wisdom(DEFAULT_WISDOM), charisma(DEFAULT_CHARISMA), position(_pos)//, inventory(Inventory())
{
}

Character::Character(int _health, int _strength, int _dexterity, int _constitution, int _intelligence, int _wisdom, int _charisma) :
	id(++count), health(_health), strength(_strength), dexterity(_dexterity),
	constitution(_constitution), intelligence(_intelligence),
	wisdom(_wisdom), charisma(_charisma), position(Position())
{
}

Character::Character(int _health, int _strength, int _dexterity, int _constitution, int _intelligence, int _wisdom, int _charisma, Position _pos) :
	id(++count), health(_health), strength(_strength), dexterity(_dexterity),
	constitution(_constitution), intelligence(_intelligence),
	wisdom(_wisdom), charisma(_charisma), position(_pos)//, inventory(Inventory())
{
}

Character::~Character()
{
}

int Character::getId() const
{
	return id;
}

int Character::getHealth() const
{
	return health;
}

int Character::getStrength() const
{
	return strength;
}

int Character::getDexterity() const
{
	return dexterity;
}

int Character::getConstitution() const
{
	return constitution;
}

int Character::getIntelligence() const
{
	return intelligence;
}

int Character::getWisdom() const
{
	return wisdom;
}

int Character::getCharisma() const
{
	return charisma;
}

Position Character::getPosition() const
{
	return position;
}

/*
Inventory Character::getInventory() const
{
	return inventory;
}*/

void Character::setHealth(int hlt)
{
	health = hlt;
}

void Character::setStrength(int str)
{
	strength = str;
}

void Character::setPosition(Position pos)
{
	position = pos;
}

bool Character::isDead()
{
	return health <= 0;
}

void Character::attack(Character *p)
{
	int val;
	if ((val = strength - p->getConstitution()) <= 0)
		val = 1;

	if (instanceof<Monster>(p)) 
		cout << "You deal " + to_string(val) + " dammage to a monster" << endl;
	else if(instanceof<Player>(p))
		cout << "You receive " + to_string(val) + " dammage" << endl;

	p->setHealth(p->getHealth() - val);
}

string Character::toString()
{
	return "Character{id = '" + to_string(id) + '\'' +
		",health = '" + to_string(health) + '\'' +
		",strength = '" + to_string(strength) + '\'' +
		", dexterity = '" + to_string(dexterity) + '\'' +
		", constitution = '" + to_string(constitution) + '\'' +
		",intelligence= '" + to_string(intelligence) + '\'' +
		", wisdom = '" + to_string(wisdom) + '\'' +
		", charisma = '" + to_string(charisma) + '\'' +
		//", inventory = '" + inventory->toString() + '\'' +
		"}";
}

ostream& operator<<(ostream& os, Character& ch)
{
	os << ch.toString();
	return os;
}
