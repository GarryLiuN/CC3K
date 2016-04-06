/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#ifndef _CELL_H
#define _CELL_H

#include "game.h"

class Object;
class Game;

class Cell {
private: 
	int row;
	int column;
	char ch;
	int chamber;
	Game* game;
	Object* object;

	// neighbour cells
 	// 0: no, 1: we, 2: so, 3: ea
 	// 4: nw, 5: ne, 6: sw, 7: se
	Cell* neighbours[8];

public: 
	Cell();
	
	~Cell();
	
	Object* getObject();

	int getRow();

	int getColumn();

	char getCh();

	int getChamber();

	Cell* getNeighbour(int n);

	Cell** getNeighbours();

	void setCell(int x, int y, char c, int cb, Game* g);
	
	void setObject(Object* obj);

	void setNeighbours();

	void notify(int row, int column, char ch);
	
};

#endif //_CELL_H
