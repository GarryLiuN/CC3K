/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng chen
 */


#include "potion.h"
#include <string>

using namespace std;

Potion::Potion(string effect) : Item('P', "potion"), effect(effect){}

Potion::~Potion(){}

string Potion::getEffect(){
	return effect;
}
