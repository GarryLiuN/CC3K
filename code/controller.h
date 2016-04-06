/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "game.h"
#include "textdisplay.h"
#include "object.h"
#include <string>
#include <iostream>

class Game;
 

class Controller {

private: 
	Game* game;
	TextDisplay* td;

public: 
	
	Controller();
	
	~Controller();

	void mainManu();
			
	void notify(int row, int column, char ch);
	
	void printStat(std::string message);

	void createPC();

	void devMode(std::string loaded);
	
	void init();

	void newGame();

	void newFloor();

	void newFloor(std::string loaded);

	void loadGame(std::string file);

	void restart();

	void play(std::string msg, std::string loaded);

};

#endif //_CONTROLLER_H
