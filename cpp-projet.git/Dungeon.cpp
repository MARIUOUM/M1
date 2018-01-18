#include "Dungeon.hpp"

#if defined(_WIN32)
const string* Dungeon::DUNGEONS_PATH = new string(".\\dungeons");
#else
const string* Dungeon::DUNGEONS_PATH = new string("./dungeons");
#endif

unsigned int Dungeon::dungeon_level = 0;

void Dungeon::displayDungeon(string path)
{
	ifstream myfile;
	string line = "";
	myfile.open(path);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
			cout << line << endl;
		myfile.close();
	}
	else
		cout << "Unable to open file" << endl;
}

Dungeon::Dungeon() : maps(new vector<Map*>())
{
}


Dungeon::~Dungeon()
{
	for (vector<Map*>::iterator it = maps->begin(); it != maps->end(); it++)
	{
		delete (*it);
	}
	maps->clear();
	delete maps;
}

void Dungeon::addMap(Map* g)
{
	maps->push_back(g);
}

Map* Dungeon::getMap(int index)
{
	return maps->at(index);
}

Map * Dungeon::getMap()
{
	return maps->back();
}

unsigned int Dungeon::sizeDungeon() const
{
	return maps->size();
}

void Dungeon::drawDungeon()
{
	for (vector<Map*>::iterator it = maps->begin(); it != maps->end(); it++)
	{
		(*it)->drawMap(false);
	}

}