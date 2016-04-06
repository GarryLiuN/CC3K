/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#ifndef _BUFFDECO_H
#define _BUFFDECO_H

#include "buff.h"


class atkBuff: public Buff {
public: 
	atkBuff(int value, Player* player);
	~atkBuff();
	int getAtk();
};


class defBuff: public Buff {
public: 
	defBuff(int value, Player *player);
	~defBuff();
	int getDef();
};

#endif //_BUFFDECO_H
