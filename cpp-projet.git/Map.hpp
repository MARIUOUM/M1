#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "Position.hpp"
#include "Square.hpp"
#include "Player.hpp"
#include "StaticMonster.hpp"
#include "DynamicMonster.hpp"
#include "TeleporterMonster.hpp"

#define DYNAMIC_MONSTER( i ) ( i % 3 == 0 ) 
#define TELEPORTER_MONSTER( i ) ( i % 5 == 0 ) 

class Map
{
private:
	int width;
	int height;
	Position begin;
	Position end;
	bool atEnd;
	vector<vector<Square*>> sq;
	vector<Monster*> monsters;

public:
	Map(int, int);
	~Map();
	Position getPositionBegin() const;
	Position getPositionEnd() const;
	bool getAtEnd() const;
	vector<Monster*> getMonsters();
	int getRemainingMonsters();
	unsigned int getRows() const;
	unsigned int getColumnsFromARow(int) const;
	void setPositionBegin(Position);
	void setPositionEnd(Position);
	void setAtEnd(bool);
	void initPositionsAndCharacters();
	void initViewPlayer(Player*);
	void addSquares(vector<Square*>);
	void drawMap(bool player);
	void drawPlayerHub(Player*);
	Square* getSquare(Position&);
	Monster* getMonster(Position&);

};

#endif
