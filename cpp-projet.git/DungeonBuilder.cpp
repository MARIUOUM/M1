#include "DungeonBuilder.hpp"


Dungeon * DungeonBuilder::buildFromFile(string path)
{
	ifstream myfile;
	int floor, width, height;
	string line = "";
	myfile.open(path);

	if (myfile.is_open())
	{
		Dungeon* dungeon = nullptr;

		if (getline(myfile, line))
			floor = atoi(line.c_str());
		else return nullptr;

		dungeon = new Dungeon();


		for (int i = 0; i < floor; i++)
		{
			if (getline(myfile, line))
				width = atoi(line.c_str());
			else
			{
				delete dungeon;
				return nullptr;
			}

			if (getline(myfile, line))
				height = atoi(line.c_str());
			else
			{
				delete dungeon;
				return nullptr;
			}

			Map* map = new Map(width, height);

			for (int j = 0; j < height; j++)
			{
				getline(myfile, line);
				map->addSquares(SquareBuilder::buildFromString(width, j, line));
			}

			map->initPositionsAndCharacters();
			dungeon->addMap(map);
		}
		myfile.close();
		return dungeon;
	}
	else
	{
		cout << "Unable to open file" << endl;
		return nullptr;
	}
}