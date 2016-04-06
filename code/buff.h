/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#ifndef _BUFF_H
#define _BUFF_H

#include "player.h"
#include <string>


class Buff : public Player {
protected: 
	int value;
	Player* player;

public: 

	Buff(int n, Player* player);

	virtual ~Buff() = 0;
	
	char getSymbol();
	
	std::string getType();
	
	Cell* getPosition();
	
	void setPosition(Cell* pos);
	
	void setAtk(int n);

	void setDef(int n);
	
	void setHP(int n);
	
	virtual int getAtk();
	
	virtual int getDef();
	
	int getHP();
	
	std::string getRace();
	
	std::string move(int d);

	void takeDamage(int n);
		
	int getMaxHP();
	
	int getGold();
	
	void addGold(int n);

	Player* getPlayer();
	
	void heal(int n);

	std::string playerMove(std::string d);

};

#endif //_BUFF_H
