/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#include "buffdeco.h"

atkBuff::atkBuff(int value, Player* player) : Buff(value, player){}

atkBuff::~atkBuff(){}

// return buffed/debuffed Atk
int atkBuff::getAtk() {
	if(player->getAtk() + value < 0)
		return 0;
	else
    	return player->getAtk() + value;
}


defBuff::defBuff(int value, Player* player) : Buff(value, player){}

defBuff::~defBuff(){}

// return buffed/debuffed Def
int defBuff::getDef() {
	if(player->getDef() + value < 0)
		return 0;
	else
	return player->getDef() + value;
}
