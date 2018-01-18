#ifndef DUNGEON_HPP_INCLUDED
#define DUNGEON_HPP_INCLUDED

#include "libs.hpp"
#include "Map.hpp"

class Dungeon
{
private:
	vector<Map*> *maps;
public:
	static const string* DUNGEONS_PATH;
	static unsigned int dungeon_level;
	static void displayDungeon(string path);

	Dungeon();
	~Dungeon();

	void addMap(Map*);
	Map* getMap(int index);
	Map* getMap();

	unsigned int sizeDungeon() const;

	void drawDungeon();
};

#endif