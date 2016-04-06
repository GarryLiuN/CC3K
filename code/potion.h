/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#ifndef _POTION_H
#define _POTION_H

#include <string>
#include "item.h"

class Potion : public Item {
private:
	std::string effect;
public:
	Potion(std::string effect);
	~Potion();
	std::string getEffect();
};

#endif //_POTION_H
