#include "Player.hpp"

Player::Player() : Character(), currentView("")
{
}

Player::Player(Position _pos) : Character(_pos), currentView("")
{
}

Player::Player(int health, int strength,int dexterity,int constitution, int intelligence, int wisdom, int charisma) : 
	Character(health, strength, dexterity, constitution, intelligence, wisdom, charisma), currentView("")
{
}

Player::Player(int health, int strength,int dexterity,int constitution, int intelligence, int wisdom, int charisma, Position _pos) :
	Character(health, strength, dexterity, constitution, intelligence, wisdom, charisma, _pos), currentView("")
{
}

Player::~Player()
{
}

string Player::getCurrentView() const
{
	return currentView;
}

void Player::setCurrentView(string str)
{
	currentView = str;
}