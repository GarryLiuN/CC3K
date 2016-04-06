/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#include "buff.h"

using namespace std;

Buff::Buff(int n, Player* player) : Player(0, 0, 0, 0, 0, "", '0', ""), value(n), player(player){}

// pure virtual method to make class abstract
Buff::~Buff(){}

char Buff::getSymbol() {
    return player->getSymbol();
}


string Buff::getType() {
    return player->getType();
}


Cell* Buff::getPosition() {
    return player->getPosition();
}


void Buff::setPosition(Cell* pos) {
    player->setPosition(pos);
    return;
}


void Buff::setAtk(int n) {
    player->setAtk(n);
    return;
}


void Buff::setDef(int n) {
    player->setDef(n);
    return;
}


void Buff::setHP(int n) {
    player->setHP(n);
    return;
}


int Buff::getAtk() {
    return player->getAtk();
}


int Buff::getDef() {
    return player->getDef();
}


int Buff::getHP() {
    return player->getHP();
}


string Buff::getRace() {
    return player->getRace();
}


string Buff::move(int d) {
    return player->move(d);
}


void Buff::takeDamage(int n){
    player->takeDamage(n);
    return;
}


int Buff::getMaxHP() {
    return player->getMaxHP();
}


int Buff::getGold() {
    return player->getGold();
}

void Buff::addGold(int n){
    player->addGold(n);
    return;
}

// in order to remove all buff decorator and return the origional unbuffed Player
Player* Buff::getPlayer() {
    Player* p = player->getPlayer();
    delete this;
    return p;
}


void Buff::heal(int n) {
    return player->heal(n);
}


string Buff::playerMove(string d) {
    return player->playerMove(d);
}

