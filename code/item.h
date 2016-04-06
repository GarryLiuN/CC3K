/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#ifndef _ITEM_H
#define _ITEM_H

#include "object.h"
#include <string>


class Item: public Object {
public: 
	
	Item(char symbol, std::string type);
	
	~Item();
};

#endif //_ITEM_H
