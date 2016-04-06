/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */

#include "cell.h"
#include "object.h"
#include <iostream>

using namespace std;
/**
 * Object implementation
 */

/**
 *	constructor consumes symbol: char, type: char and set position to NULL
 */
Object::Object(char symbol, string type) : symbol(symbol), type(type){
	position = NULL;
}


/**
 *	pure virtual desctructor
 */
Object::~Object() {}

string Object::getRace() {
	return "";
}
/**
 * return Object symbol
 */
char Object::getSymbol() {
    return symbol;
}

/**
 * return Object type
 */
string Object::getType() {
    return type;
}

/**
 * return Object position
 */
Cell* Object::getPosition() {
    return position;
}

/*
 *	set Object position to parameter pos 
 */
void Object::setPosition(Cell* pos) {
	position = pos;
    return;
}
