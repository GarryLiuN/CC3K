/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#include "enemy.h"
#include "treasure.h"
#include "cell.h"

using namespace std;


Enemy::Enemy(int Atk, int Def, int HP, string race, char symbol, string type)
			: Character(Atk, Def, HP, race, symbol, type), act_flag(false)
	{}

Enemy::~Enemy() {}

bool Enemy::isActed(){
	return act_flag;
}

void Enemy::act(){
	act_flag = true;
}

void Enemy::actClear(){
	act_flag = false;
}

void Enemy::dropGold(){
	int chance = rand() % 2;
	Treasure* t = NULL;
	if(chance == 0){
		t = new SmallHoard();
	}
	else{
		t = new NormalHoard();
	}
	t->setPosition(position);
	position->setObject(t);
}

Human::Human() : Enemy(20, 20, 140, "Human", 'H', "enemy"){}

Human::~Human(){}

void Human::dropGold(){
	Treasure *t1 = new NormalHoard();
	Treasure *t2 = new NormalHoard();

	t1->setPosition(position);
	position->setObject(t1);

	for(int i = 0; i < 8; i++){
		Cell* destination = position->getNeighbour(i);
		if(destination && destination->getCh() == '.' && !destination->getObject()){
			t2->setPosition(destination);
			destination->setObject(t2);
			return;
		}
	}
	delete t2;
	return;
}


Dwarf::Dwarf() : Enemy(20, 30, 100, "Dwarf", 'W', "enemy"){}

Dwarf::~Dwarf(){}


Elf::Elf() : Enemy(30, 10, 140, "Elf", 'E', "enemy"){}

Elf::~Elf(){}


Orc::Orc() : Enemy(30, 25, 180, "Orc", 'O', "enemy"){}

Orc::~Orc(){}


bool Merchant::hostile = false;

Merchant::Merchant() : Enemy(70, 5, 30, "Merchant", 'M', "enemy"){}

Merchant::~Merchant(){}

void Merchant::dropGold(){
	MerchantHoard* t = new MerchantHoard();
	t->setPosition(position);
	position->setObject(t);
	return;
}

Halfling::Halfling() : Enemy(15, 20, 100, "Halfling", 'L', "enemy"){}

Halfling::~Halfling(){}


Dragon::Dragon() : Enemy(20, 20, 150, "Dragon", 'D', "enemy"), hoard(NULL){}

Dragon::Dragon(DragonHoard* hoard) : Enemy(20, 20, 150, "Dragon", 'D', "enemy"), hoard(hoard) {}

Dragon::~Dragon(){}

void Dragon::dropGold(){
	return;
}

DragonHoard* Dragon::getHoard(){
	return hoard;
}

void Dragon::setHoard(DragonHoard* hd){
	hoard = hd;
}

