/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#ifndef _OBJECT_H
#define _OBJECT_H

#include <string>

class Cell;

class Object {

protected: 
	const char symbol;
	const std::string type;
	Cell* position;

public: 
	
	Object(char symbol, std::string type);
	
	virtual ~Object() = 0;

	virtual std::string getRace();
	
	virtual char getSymbol();
	
	virtual std::string getType();
	
	virtual Cell* getPosition();
	
	virtual void setPosition(Cell* pos);
};

#endif //_OBJECT_H
