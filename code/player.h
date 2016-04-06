/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#ifndef _PLAYER_H
#define _PLAYER_H

#include "character.h"
#include <string>


class Player: public Character {
protected: 
	const int MAX_HP;
	int gold;

public: 
	
	// constructor
	Player(int MAX_HP, int gold, int Atk, int Def, int HP, std::string race, char symbol, std::string type);
	
	// pure virtual method to make the class abstract
	virtual ~Player() = 0;
	
	// return player's MAX_HP
	virtual int getMaxHP();

	// return player's gold
	virtual int getGold();

	// add n gold to Player holding gold
	virtual void addGold(int n);
	
	// get the Player pointer for the decorator Buff
	virtual Player* getPlayer();
	
	/**
	 *	heal Player n amount of HP
	 *	HP can't exceed MAX_HP
	 */
	virtual void heal(int n);

	// used for convert move input string d to int and call Character::move(int n)
	virtual std::string playerMove(std::string d);
};

// Shade: 120 HP, 25 Atk, 25 Def
class Shade : public Player{
	public:
		Shade();
		~Shade();
};

// Drow: 150 HP, 25 Atk, 15 Def, magnified potion effect by 1.5
class Drow : public Player{
	public:
		Drow();
		~Drow();
};

// Vamprie: 50 HP, 25 Atk, 25 Def, heal 5 HP every successful attack and no MAX_HP
class Vampire : public Player{
	public:
		Vampire();
		~Vampire();
		void heal(int n);
};

// Troll: 120 HP, 25 Atk, 15 Def, regain 5 HP every turn
class Troll : public Player{
	public:
		Troll();
		~Troll();
};

// Goblin: 110 HP, 15 Atk, 20 Def, get 5 gold every kill
class Goblin : public Player{
	public:
		Goblin();
		~Goblin();
};


#endif //_PLAYER_H
