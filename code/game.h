/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#ifndef _GAME_H
#define _GAME_H

#include <string>

class Cell;
class Player;
class Enemy;
class Object;
class Controller;

class Game {
private: 
	Cell** theFloor;
	const int row;
	const int column;
	int level;
	Enemy* enemies[20];
	Player* player;
	Controller* controller;

public: 
	
	Game(int row, int column);
	
	~Game();

	std::string playerAttack(std::string d);

	std::string consumePotion(std::string d);

	void generatePlayer();

	void generateStair();
	
	void generateEnemies();
	
	void generatePotions();

	void generateTreasures();

	void clearFloor();
	
	void setLevel(int n);
		
	int getLevel();
	
	Cell* getCell(int row, int column);

	Enemy** getEnemies();

	void setPlayer(Player* p);

	Player* getPlayer();

	int getRow();

	int getColumn();
	
	void notify(int row, int column, char ch);
	
	void init(Controller* ctrler);

	void initFloor();

	void initFloor(std::string floorPlan);
	
};

#endif //_GAME_H
