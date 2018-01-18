#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "Character.hpp"

#define VIEWS	4
#define WEAST	0
#define EAST	1
#define SOUTH	2
#define NORTH	3

class Player : public Character
{
private:
	string currentView;
public:
	string views[4] = { ("<"), (">"), ("V"), ("^") };
	string WEST_VIEW = views[WEAST];
	string EAST_VIEW = views[EAST];
	string SOUTH_VIEW = views[SOUTH];
	string NORTH_VIEW = views[NORTH];

	Player();
	Player(Position);
	Player(int, int, int, int, int, int, int);
	Player(int, int, int, int, int, int, int, Position);
	~Player();

	string getCurrentView() const;
	void setCurrentView(string);
	
};

#endif
