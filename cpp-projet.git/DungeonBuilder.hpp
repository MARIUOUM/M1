#ifndef DUNGEON_BUILDER_HPP_INCLUDED
#define DUNGEON_BUILDER_HPP_INCLUDED

#include "Dungeon.hpp"
#include "SquareBuilder.hpp"

class DungeonBuilder
{
public:
	static Dungeon *buildFromFile(string path);
};

#endif