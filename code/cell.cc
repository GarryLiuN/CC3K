/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#include "cell.h"
#include "object.h"
#include <iostream>

using namespace std;

/**
 * Cell implementation
 */

Cell::Cell(){
	row = 0;
	column = 0;
	ch = '0';
	chamber = 0;
	game = NULL;
	//set all neighbour to null
	object = NULL;
	for(int i = 0; i < 8; i++)
		neighbours[i] = NULL;
}

Cell::~Cell() {}

void Cell::setCell(int x, int y, char c, int cb, Game* g){
	row = x;
	column = y;
	ch = c;
	chamber = cb;
	game = g;
	notify(row, column, ch);
}

// return the object occupies the cell. Null if it is not occupied
Object* Cell::getObject() {
    return object;
}

int Cell::getRow(){
	return row;
}

int Cell::getColumn(){
	return column;
}

char Cell::getCh(){
	return ch;
}

int Cell::getChamber(){
	return chamber;
}

Cell* Cell::getNeighbour(int n){
	return neighbours[n];
}

Cell** Cell::getNeighbours(){
	return neighbours;
}

// set the object when some Object occupies the cell
// set it to NULL if the the Object leaves
void Cell::setObject(Object* obj) {
	object = obj;
	if(object == NULL){
		notify(row, column, ch);
	}
	else if(object){
		notify(row, column, object->getSymbol());
	}
    return;
}

// setNeighbours
void Cell::setNeighbours(){
	if(row == 0 || row == 24 || column == 0 || column == 79){
		return;

	}
	// middle cells
	else{
		neighbours[0] = game->getCell(row - 1, 	column    );
		neighbours[1] = game->getCell(row, 		column - 1);
		neighbours[2] = game->getCell(row + 1, 	column    );
		neighbours[3] = game->getCell(row, 		column + 1);
		neighbours[4] = game->getCell(row - 1, 	column - 1);
		neighbours[5] = game->getCell(row - 1,  column + 1);
		neighbours[6] = game->getCell(row + 1, 	column - 1);
		neighbours[7] = game->getCell(row + 1, 	column + 1);	
	}
	return;
}

void Cell::notify(int row, int column, char ch){
	game->notify(row, column, ch);
}

