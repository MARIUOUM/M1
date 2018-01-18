#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include "libs.hpp"
#include "Observable.hpp"
#include "Position.hpp"
//#include "Item.hpp"
//#include "Inventory.hpp"

#define DEFAULT_HEALTH			10
#define DEFAULT_STRENGTH		10
#define DEFAULT_DEXTERITY		10
#define DEFAULT_CONSTITUTION	10
#define DEFAULT_INTELLIGENCE	10
#define DEFAULT_WISDOM 			10
#define DEFAULT_CHARISMA 		10

class Character : public Observable
{
private:
	static int count;
protected:
	int id;					//id
	int health;				//health
	int strength;			//strength
	int dexterity;			//dexterity
	int constitution;		//constitution
	int intelligence;		//intelligence 
	int wisdom;				//wisdom
	int charisma;			//charisma
	Position position;		//position
	//Inventory inventory;

public:
	Character();
	Character(Position);
	Character(int, int, int, int, int, int, int);
	Character(int, int, int, int, int, int, int, Position);
	virtual ~Character();

	virtual int getId() const;
	virtual int getHealth() const;
	virtual int getStrength() const;
	virtual int getDexterity() const;
	virtual int getConstitution() const;
	virtual int getIntelligence() const;
	virtual int getWisdom() const;
	virtual int getCharisma() const;
	virtual Position getPosition() const;
	//virtual Inventory getInventory() const;
	//Item* backPack[7];
	//Item* equippedItems[7]; //! 0:Helmet; 1:Armor; 2:Shield; 3:Ring; 4:Belt; 5:Boots; 6:Weapon;
	virtual void setHealth(int);
	virtual void setStrength(int);
	virtual void setPosition(Position);

	virtual bool isDead();
	virtual void attack(Character*);

	string toString();
	friend ostream& operator<<(ostream&, Character&);
};

#endif
