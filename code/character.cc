/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#include "character.h"
#include "cell.h"
#include "enemy.h"
#include "player.h"
#include "treasure.h"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

Character::Character(int Atk, int Def, int HP, string race, char symbol, string type) : Object(symbol, type), Atk(Atk), Def(Def), HP(HP), race(race) {
}

Character::~Character() {}

/**
 *  set Character Atk to n
 */
void Character::setAtk(int n) {
    Atk = n;
    return;
}

/**
 *  set Character Def to n
 */
void Character::setDef(int n) {
    Def = n;
    return;
}

/**
 *  set Character HP to n
 */
void Character::setHP(int n) {
    HP = n;
    return;
}

/**
 * return Character Atk
 */
int Character::getAtk() {
    return Atk;
}

/**
 * return Character Def
 */
int Character::getDef() {
    return Def;
}

/**
 * return Character HP
 */
int Character::getHP() {
    return HP;
}

/**
 * return Character Race
 */
string Character::getRace() {
    return race;
}


/**
 * move mthod
 * for d:int
 * 0: no, 1: we, 2: so, 3: ea
 * 4: nw, 5: ne, 6: sw, 7: se
 */
std::string Character::move(int d) {
    Cell* current = position;
    Cell* destination = position->getNeighbour(d);
    char destCh = destination->getCh();

    Object* destObj = destination->getObject();
    string message = "";

    if(type != "player" && (destCh != '.' || destObj)){
        return "nomove";
    }
    else if(type == "player" && (destCh == '-' || destCh == '|' || destCh == ' ')){
        return "You can't move to ";
    }
    else if(destObj && destObj->getType() == "stair"){
        return "nextFloor";
    }
    else if(destObj && destObj->getType() == "potion"){
        return "You cant't move to there. There is a mysterious potion on ";
    }
    else if(destObj && destObj->getType() == "treasure"){
        if(static_cast<Treasure*>(destObj)->getDragon()){
            return "A dragon is guarding its hoard. You can't take the treasure on ";
        }
        else{
            Player* player = static_cast<Player*>(this);
            int value = static_cast<Treasure*>(destObj)->getValue();
            player->addGold(value);
            stringstream ss;
            ss << value;
            delete destObj;
            message += ss.str();
        }
    }
    else if(destObj){
        return "A " + destObj->getRace() + " blocked the way. You can't move to ";
    }
    else if(type == "player"){
        message += "You moved to ";
    }

    setPosition(destination);
    current->setObject(NULL);
    destination->setObject(this);
    return message;
}

/**
 *  reduce Character HP by n. HP can not drop under 0
 */
void Character::takeDamage(int n){
    HP -= n;

    // if HP drops under 0, set it to 0
    if (HP < 0) HP = 0;
    return;
}

string intToString(int n);

/**
 * this will delt damage to defender
 * return true if successfully attack, false if miss
 */
string Character::Damage(Character* defender) {
    // get Attacker and Defender type and race;
    string atkType = getType();
    string atkRace = getRace();
    string defType = defender->getType();
    string defRace = defender->getRace();

    // state attacker and defender. "You" if it is player, race if it is enemy
    string atkr = (atkType == "player" ? "You" : atkRace);
    string defr = (defType == "player" ? "You" : defRace);

    // combat outcome message
    string message = "";

    bool attacked = false;

    // get Attacker Atk and Defender Def
    double Atk = getAtk();
    double Def = defender->getDef();

    // dmg will be delt to defender
    int dmg;

    // HP after take dmg;
    int hp;

    atk__:
    // use random number to check if miss
    // only apply to case that defender is player or Halfling
    if(defType == "player" || defRace == "Halfling"){
        int chance = rand() % 2;
        if(chance == 0) {
            // generate miss attack message
            message += atkr + " attacked " + defr + " but missed. ";
            goto endatk__;
        }
    }

    // calculate dmg
    dmg = ceil((100 / (100 + Def)) * Atk);

    // effect when Orc attack Goblin will magnified dmg by 1.5
    if(atkRace == "Orc" && defRace == "Goblin")
        dmg = ceil(dmg * 1.5);


    // reduce defender HP
    defender->takeDamage(dmg);


    // get HP after taking dmg;
    hp = defender->getHP();


    // generate attack message
    message = atkr + " attacked " + defr + ", delt " + intToString(dmg) + " dmg" + "(" + intToString(hp) + "). ";
    if(hp == 0){
        message += defr + (defType == "player" ? " are " : " is ") + "dead. ";
    }

    // effect for Vampire. Heal 5HP upon attacking or lost 5HP upon attacking dwarf
    if(atkRace == "Vampire"){
        // attack Drawf will cause lost 5 HP
        if(defRace == "Dwarf"){
            takeDamage(5);
            message += "Dwarf's blood is poisonous. Lost 5 HP. ";
        }
        // attack other races will gain 5 HP
        else{
            heal(5);
            message += "Drained 5 HP from " + defRace + ". ";
        }
    }

    // Merchant become hostile after being attacked
    if(defRace == "Merchant"){
        Merchant::hostile = true;
    }
    
    endatk__:
    if(atkRace == "Elf" && defRace != "Drow" && !attacked){
        attacked = true;
        goto atk__;
    }

    return message;
}

void Character::heal(int n){
    return;
}
