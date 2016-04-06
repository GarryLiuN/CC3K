/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#include "player.h"
#include "enemy.h"
#include "cell.h"

using namespace std;


Player::Player(int MAX_HP, int gold, int Atk, int Def, int HP, string race, char symbol, string type)
			: Character(Atk, Def, HP, race, symbol, type), MAX_HP(MAX_HP), gold(gold)
			{}

// pure virtual destractor to make class abstract
Player::~Player() {}

// return Player MAX_HP
int Player::getMaxHP() {
    return MAX_HP;
}

// return Player gold
int Player::getGold() {
    return gold;
}

// add n gold to Player gold
void Player::addGold(int n){
	gold += n;
	return;
}


//	return the Player
Player* Player::getPlayer() {
    return this;
}

/**
 *	heal Player n amount of HP
 *	HP can't exceed MAX_HP
 */
void Player::heal(int n) {
	HP += n;
	if (HP > MAX_HP)
		HP = MAX_HP;
    return;
}

// move method for player. 
// convert d to int and call Character::move(int d)
/**
 * move mthod
 * for d:int
 * 0: no, 1: we, 2: so, 3: ea
 * 4: nw, 5: ne, 6: sw, 7: se
 */
std::string Player::playerMove(string d){
	string message = "";
	if 	   (d == "no")	message += move(0);
	else if(d == "we")	message += move(1);
	else if(d == "so")	message += move(2);
	else if(d == "ea")	message += move(3);
	else if(d == "nw")	message += move(4);
	else if(d == "ne")	message += move(5);
	else if(d == "sw")	message += move(6);
	else if(d == "se")	message += move(7);

	return message;
}


// implementation for Shade
Shade::Shade() : Player(125, 0, 25, 25, 125, "Shade", '@', "player") {};

Shade::~Shade(){}



// implementation for Drow
Drow::Drow() : Player(150, 0, 25, 15, 150, "Drow", '@', "player") {};

Drow::~Drow(){}


// implementation for Vampire
Vampire::Vampire() : Player(0, 0, 25, 25, 50, "Vampire", '@', "player") {};

Vampire::~Vampire(){}

// override Heal method since Vampire has no maximum HP
void Vampire::heal(int n){
	HP += n;
}




// implmentation for Troll
Troll::Troll() : Player(120, 0, 25, 15, 120, "Troll", '@', "player") {};

Troll::~Troll(){}


// implementation for Goblin
Goblin::Goblin() : Player(110, 0, 15, 20, 110, "Goblin", '@', "player") {};

Goblin::~Goblin(){}
