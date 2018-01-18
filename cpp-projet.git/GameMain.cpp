#include "libs.hpp"

#include "DungeonBuilder.hpp"
#include "Square.hpp"
#include "TeleporterMonster.hpp"
#include "StaticMonster.hpp"
#include "DynamicMonster.hpp"
#include "Player.hpp"

#define null "NULL"

static bool gameFinished = false;
static bool adminDisplay = false;

void launchGame();
#if defined(_WIN32)
void move(Map *);
#else
void move(Map *, string);
#endif
bool deathInFight(Monster *);
void updateMap(Map *);
void moveDynamicMonster(Map *, Monster *);
void moveTeleporterMonster(Map *, Monster *);
void congratulation();

void menuStart();
void menuCreateDungeon();
void menuLoadDungeon();
void menuDisplayDungeon();
void menuCreateOrLoadPlayer();
Player *menuCreatePlayer();
string selectDungeonFile();
void clear();
void clearAll();

Dungeon *dungeon = nullptr;
Player *P1 = nullptr;

int main(int argc, char **argv)
{
	menuStart();
	clearAll();

#if defined(_WIN32)
	system("pause");
#else
	cin.get();
#endif

	return EXIT_SUCCESS;
}

void launchGame()
{
	Map *currentMap;
	string gameContinue, listenEvent;

	while (!gameFinished)
	{
		currentMap = dungeon->getMap(Dungeon::dungeon_level++);
		P1->setPosition(currentMap->getPositionBegin());
		currentMap->initViewPlayer(P1);

#if defined(_WIN32)
		while (!gameFinished && !currentMap->getAtEnd() && !P1->isDead())
		{
			system("CLS");
			currentMap->drawMap(!adminDisplay);
			currentMap->drawPlayerHub(P1);
			while (true)
			{
				_getch();

				if (QUIT)
				{
					gameFinished = true;
					break;
				}
				else if (MOVE)
				{
					move(currentMap);
					updateMap(currentMap);
					break;
				}
				else if (PACK)
				{
					cout << "TODO BACKPACK" << endl;
				}
			}
		}
#else
		while (!gameFinished && !currentMap->getAtEnd() && !P1->isDead())
		{
			system("clear");
			currentMap->drawMap(!adminDisplay);
			currentMap->drawPlayerHub(P1);
			string ch = "";
			while (ch != "z" && ch != "s" && ch != "q" && ch != "d" && ch != "a" && ch != "e" && ch != "w" && ch != "c" && ch != "f" && ch != "i")
			{
				cin >> ch;
				if (ch == "f")
					gameFinished = true;
				else if (ch == "z")
					move(currentMap, "z");
				else if (ch == "s")
					move(currentMap, "s");
				else if (ch == "q")
					move(currentMap, "q");
				else if (ch == "d")
					move(currentMap, "d");
				else if (ch == "a")
					move(currentMap, "a");
				else if (ch == "e")
					move(currentMap, "e");
				else if (ch == "w")
					move(currentMap, "w");
				else if (ch == "c")
					move(currentMap, "c");
				else if (ch == "i")
					cout << "TODO BACKPACK" << endl;
			}
			if (ch == "z" || ch == "s" || ch == "q" || ch == "d" || ch != "a" || ch != "e" || ch != "w" || ch != "c")
				updateMap(currentMap);
		}
#endif
		if (P1->isDead())
		{
			cout << "You lose ! Try Next Time !" << endl;
			cout << "Monsters remaining in this map : " << currentMap->getRemainingMonsters() << endl;
			gameFinished = true;

#if defined(_WIN32)
			Sleep(5000);
#else
			sleep(5);
#endif
		}

		if (!gameFinished)
		{
			if (Dungeon::dungeon_level >= dungeon->sizeDungeon())
			{
				gameFinished = true;
				congratulation();
			}
			else
			{
				cout << "You go to the next level" << endl;
				cout << "Monsters remaining in this map : " << currentMap->getRemainingMonsters() << endl;
#if defined(_WIN32)
				Sleep(5000);
#else
				sleep(5);
#endif
			}
		}
	}
}

#if defined(_WIN32)
void move(Map *map)
{
	Position pos = P1->getPosition(), find;
	Square *square = map->getSquare(pos);

	if (MOVE_UP && (pos.getY() - 1 > 0))
	{
		find = Position(pos.getX(), pos.getY() - 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->NORTH_VIEW)
				P1->setCurrentView(P1->NORTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (MOVE_LEFT && (pos.getX() - 1 > 0))
	{
		find = Position(pos.getX() - 1, pos.getY());
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->WEST_VIEW)
				P1->setCurrentView(P1->WEST_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (MOVE_DOWN && (pos.getY() + 1 < map->getRows()))
	{
		find = Position(pos.getX(), pos.getY() + 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->SOUTH_VIEW)
				P1->setCurrentView(P1->SOUTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (MOVE_RIGHT && (pos.getX() + 1 < map->getColumnsFromARow(pos.getY())))
	{
		find = Position(pos.getX() + 1, pos.getY());
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->EAST_VIEW)
				P1->setCurrentView(P1->EAST_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (MOVE_UP_RIGHT &&
			 (pos.getY() - 1 > 0 && pos.getX() + 1 < map->getColumnsFromARow(pos.getY() - 1)))
	{
		find = Position(pos.getX() + 1, pos.getY() - 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->NORTH_VIEW)
				P1->setCurrentView(P1->NORTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (MOVE_UP_LEFT &&
			 (pos.getY() - 1 > 0) && pos.getX() - 1 > 0)
	{
		find = Position(pos.getX() - 1, pos.getY() - 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->NORTH_VIEW)
				P1->setCurrentView(P1->NORTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (MOVE_DOWN_LEFT &&
			 (pos.getX() - 1 > 0 && pos.getY() + 1 < map->getRows()))
	{
		find = Position(pos.getX() - 1, pos.getY() + 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->SOUTH_VIEW)
				P1->setCurrentView(P1->SOUTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (MOVE_DOWN_RIGHT &&
			 (pos.getY() + 1 < map->getRows() && pos.getX() + 1 < map->getColumnsFromARow(pos.getY() + 1)))
	{
		find = Position(pos.getX() + 1, pos.getY() + 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->SOUTH_VIEW)
				P1->setCurrentView(P1->SOUTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
}
#else
void move(Map *map, string mv)
{
	Position pos = P1->getPosition(), find;
	Square *square = map->getSquare(pos);

	if (mv == "z" && (pos.getY() - 1 > 0))
	{
		find = Position(pos.getX(), pos.getY() - 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->NORTH_VIEW)
				P1->setCurrentView(P1->NORTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (mv == "q" && (pos.getX() - 1 > 0))
	{
		find = Position(pos.getX() - 1, pos.getY());
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->WEST_VIEW)
				P1->setCurrentView(P1->WEST_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (mv == "s" && (pos.getY() + 1 < map->getRows()))
	{
		find = Position(pos.getX(), pos.getY() + 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->SOUTH_VIEW)
				P1->setCurrentView(P1->SOUTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (mv == "d" && (pos.getX() + 1 < map->getColumnsFromARow(pos.getY())))
	{
		find = Position(pos.getX() + 1, pos.getY());
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->EAST_VIEW)
				P1->setCurrentView(P1->EAST_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (mv == "e" &&
			 (pos.getY() - 1 > 0 && pos.getX() + 1 < map->getColumnsFromARow(pos.getY() - 1)))
	{
		find = Position(pos.getX() + 1, pos.getY() - 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->NORTH_VIEW)
				P1->setCurrentView(P1->NORTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (mv == "a" &&
			 (pos.getY() - 1 > 0) && pos.getX() - 1 > 0)
	{
		find = Position(pos.getX() - 1, pos.getY() - 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->NORTH_VIEW)
				P1->setCurrentView(P1->NORTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (mv == "w" &&
			 (pos.getX() - 1 > 0 && pos.getY() + 1 < map->getRows()))
	{
		find = Position(pos.getX() - 1, pos.getY() + 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->SOUTH_VIEW)
				P1->setCurrentView(P1->SOUTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
	else if (mv == "c" &&
			 (pos.getY() + 1 < map->getRows() && pos.getX() + 1 < map->getColumnsFromARow(pos.getY() + 1)))
	{
		find = Position(pos.getX() + 1, pos.getY() + 1);
		if (map->getSquare(find)->getType() != SquareType::WALL)
		{
			if (square->getType() != SquareType::BEGIN)
				square->setType(SquareType::EMPTY);

			if (map->getSquare(find)->getType() == SquareType::MONSTER)
			{
				Monster *monster = map->getMonster(find);

				if (monster != nullptr)
				{
					if (deathInFight(monster))
						return;
				}
			}

			P1->setPosition(find);

			if (P1->getCurrentView() != P1->SOUTH_VIEW)
				P1->setCurrentView(P1->SOUTH_VIEW);

			if (map->getSquare(find)->getType() != SquareType::END)
				map->getSquare(find)->setType(SquareType::PLAYER);
			else
				map->setAtEnd(true);
		}
	}
}
#endif

void congratulation()
{
	cout << "You are at the end of the game, Congratulation!" << endl;
	cout << *P1 << endl;
}

bool deathInFight(Monster *monster)
{
	while (!P1->isDead() && !monster->isDead())
	{
		P1->attack(monster);
		if (monster->isDead())
		{
			cout << "Good job ! You killed a monster ! Your health = " + to_string(P1->getHealth()) << endl;
#if defined(_WIN32)
			Sleep(2000);
#else
			sleep(2);
#endif
			return false;
		}
		monster->attack(P1);
		if (P1->isDead())
			return true;
	}
	return false;
}

void updateMap(Map *map)
{
	for (auto it : map->getMonsters())
	{
		if (it == nullptr || it->isDead() || instanceof <StaticMonster>((it)))
			continue;

		if (instanceof <DynamicMonster>(it))
			moveDynamicMonster(map, it);
		else if (instanceof <TeleporterMonster>(it))
			moveTeleporterMonster(map, it);

		if (P1->isDead())
			return;
	}
}

void moveDynamicMonster(Map *map, Monster *monster)
{
	vector<Square *> canMove = vector<Square *>();
	Square *tmp = nullptr, *curr = nullptr;
	Position pos, up, down, left, right;
	int can = 0;

	pos = monster->getPosition();
	up = Position(pos.getX(), pos.getY() - 1);
	down = Position(pos.getX(), pos.getY() + 1);
	left = Position(pos.getX() - 1, pos.getY());
	right = Position(pos.getX() + 1, pos.getY());

	curr = map->getSquare(pos);
	tmp = map->getSquare(up);
	if (tmp->getType() != SquareType::WALL && tmp->getType() != SquareType::BEGIN && tmp->getType() != SquareType::END && tmp->getType() != SquareType::MONSTER)
	{
		can++;
		canMove.push_back(tmp);
	}

	tmp = map->getSquare(down);
	if (tmp->getType() != SquareType::WALL && tmp->getType() != SquareType::BEGIN && tmp->getType() != SquareType::END && tmp->getType() != SquareType::MONSTER)
	{
		can++;
		canMove.push_back(tmp);
	}

	tmp = map->getSquare(left);
	if (tmp->getType() != SquareType::WALL && tmp->getType() != SquareType::BEGIN && tmp->getType() != SquareType::END && tmp->getType() != SquareType::MONSTER)
	{
		can++;
		canMove.push_back(tmp);
	}

	tmp = map->getSquare(right);
	if (tmp->getType() != SquareType::WALL && tmp->getType() != SquareType::BEGIN && tmp->getType() != SquareType::END && tmp->getType() != SquareType::MONSTER)
	{
		can++;
		canMove.push_back(tmp);
	}

	if (canMove.size() > 1)
	{
		curr->setType(SquareType::EMPTY);
		tmp = canMove.at(rand() % can);

		if (tmp->getType() == SquareType::PLAYER)
		{
			cout << "A Monster attack you !" << endl;
#if defined(_WIN32)
			Sleep(1000);
#else
			sleep(1);
#endif
			while (!P1->isDead() && !monster->isDead())
			{
				monster->attack(P1);

				if (P1->isDead())
					return;

				P1->attack(monster);

				if (monster->isDead())
				{
					cout << "Good job ! You killed a monster ! Your health = " + to_string(P1->getHealth()) << endl;
#if defined(_WIN32)
					Sleep(2000);
#else
					sleep(2);
#endif
					return;
				}
			}
		}
		else
		{
			tmp->setType(SquareType::MONSTER);
			monster->setPosition(Position(tmp->getX(), tmp->getY()));
		}
	}
	canMove.clear();
}

void moveTeleporterMonster(Map *map, Monster *monster)
{
}

void menuStart()
{
	string map;

	do
	{
		cout << "[C]reate donjon, [L]oad donjon, [D]isplay donjon, [S]top" << endl;
		cin >> map;
		for (auto &c : map)
			c = toupper(c);
		if (map == "S")
			return;

	} while (map != "C" && map != "L" && map != "D");

	if (map == "C")
		menuCreateDungeon();
	else if (map == "L")
		menuLoadDungeon();
	else if (map == "D")
		menuDisplayDungeon();
}

void menuCreateDungeon()
{
	cout << "TODO" << endl;
}

void menuLoadDungeon()
{
	string map;
	if ((map = selectDungeonFile()) == null)
		return;
	dungeon = DungeonBuilder::buildFromFile(map);
	dungeon->drawDungeon();
	menuCreateOrLoadPlayer();
}

void menuDisplayDungeon()
{
	string map;
	if ((map = selectDungeonFile()) == null)
		return;
	Dungeon::displayDungeon(map);
}

void menuCreateOrLoadPlayer()
{
	string pl, start;

	do
	{
		cout << "[C]reate a new player or [L]oad a default player setting or else [B]ack to the main Menu" << endl;
		cin >> pl;
		for (auto &c : pl)
			c = toupper(c);
		if (pl == "B")
			return;

	} while (pl != "C" && pl != "L");

	if (pl == "C")
		P1 = menuCreatePlayer();
	else
	{
		P1 = new Player();
	}

	do
	{
		cout << "Admin display ? [Y or N]" << endl;
		cin >> start;
		for (auto &c : start)
			c = toupper(c);
		if (start == "Y")
			adminDisplay = true;
		//Game::launchGame(dungeon, P1);

	} while (start != "Y" && start != "N");

	do
	{
		cout << "Start the game ? [Y or N]" << endl;
		cin >> start;
		for (auto &c : start)
			c = toupper(c);
		if (start == "Y")
			launchGame();
		//Game::launchGame(dungeon, P1);

	} while (start != "Y" && start != "N");
}

Player *menuCreatePlayer()
{
	int hlt;
	int str;
	int dex;
	int cons;
	int intel;
	int wis;
	int cha;

	do
	{
		cout << "Your health between 0 and 10" << endl;
		cin >> hlt;
	} while (hlt <= DEFAULT_HEALTH);

	do
	{
		cout << "Your strength between 0 and 5" << endl;
		cin >> str;
	} while (str <= DEFAULT_STRENGTH);

	do
	{
		cout << "Your dexterity between 0 and 5" << endl;
		cin >> dex;
	} while (dex <= DEFAULT_DEXTERITY);

	do
	{
		cout << "Your constitution between 0 and 5" << endl;
		cin >> cons;
	} while (cons <= DEFAULT_CONSTITUTION);
	do
	{
		cout << "Your intelligence between 0 and 5" << endl;
		cin >> intel;
	} while (intel <= DEFAULT_INTELLIGENCE);

	do
	{
		cout << "Your intelligence between 0 and 5" << endl;
		cin >> wis;
	} while (intel <= DEFAULT_WISDOM);

	do
	{
		cout << "Your charisma between 0 and 5" << endl;
		cin >> cha;
	} while (cha <= DEFAULT_CHARISMA);

	return new Player(hlt, str, dex, cons, intel, wis, cha);
}

string selectDungeonFile()
{
	vector<string> files;
	int i = 0;
	size_t map;

	cout << "Choisissez un Donjon (arret si 0)" << endl;
	for (auto &p : fs::directory_iterator(*Dungeon::DUNGEONS_PATH))
	{
		string str = p.path().string();
		cout << "[" + to_string(++i) + "] " + str << endl;
		files.push_back(str);
	}
	cin >> map;

	if (map == 0)
		return null;

	while (map > files.size())
	{
		i = 0;
		cout << "Donjon non existant. Choisissez un Donjon (arret si 0)" << endl;
		for (auto &p : files)
		{
			cout << "[" + to_string(++i) + "] " + p << endl;
		}
		cin >> map;
		if (map == 0)
			return null;
	}
	return files.at(map - 1);
}

void clear()
{
	if (dungeon != nullptr)
	{
		delete dungeon;
	}

	if (P1 != nullptr)
	{
		delete P1;
	}
}

void clearAll()
{
	clear();
	delete Dungeon::DUNGEONS_PATH;
}