/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */

#include "game.h"
#include "cell.h"
#include "controller.h"
#include "object.h"
#include "stair.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "treasure.h"
#include "buffdeco.h"
#include <fstream>
#include <sstream>

using namespace std;

class Stair;
class DragonHoard;

/**
 * Game implementation
 */


Game::Game(int row, int column) : row(row),column(column){
	theFloor = NULL;
	level = 0;
	for(int i = 0; i < 20; i++)
		enemies[i] = NULL;
	player = NULL;
	controller = NULL;
}

Game::~Game() {
	clearFloor();
	if(theFloor){
		for(int i = 0; i < row; i++){
			delete[] theFloor[i];
		}
		delete[] theFloor;
	}
	delete player;

}

int destStrToInt(string d){
	int dest = 0;
	if 	   (d == "no")	dest = 0;
	else if(d == "we")	dest = 1;
	else if(d == "so")	dest = 2;
	else if(d == "ea")	dest = 3;
	else if(d == "nw")	dest = 4;
	else if(d == "ne")	dest = 5;
	else if(d == "sw")	dest = 6;
	else if(d == "se")	dest = 7;
	return dest;
}
string Game::playerAttack(string d){
	int dest = destStrToInt(d);

	Cell* destination = player->getPosition()->getNeighbour(dest);
	Object* destObj = destination->getObject();

	string message = "";
	if(destObj && destObj->getType() == "enemy"){
		Enemy* e = static_cast<Enemy*>(destObj);
		message += player->Damage(e);
		// if dragon is killed delete it from its hoard.
        if(e->getRace() == "Dragon" && e->getHP() == 0){
            static_cast<Dragon*>(e)->getHoard()->deleteDragon();
        }
	}
	else{
		message += "noenemy";
	}
	return message;

}

string intToString(int n);

string Game::consumePotion(string d){
	int dest = destStrToInt(d);

	Cell* destination = player->getPosition()->getNeighbour(dest);
	Object* destObj = destination->getObject();

	string message = "";

	if(!destObj || destObj->getType() != "potion"){
		return "There is no potion on " + d +". ";
	}
	else{
		Potion* p = static_cast<Potion*>(destObj);

		if(p->getEffect() == "RH"){
			int n = 10;
			if(player->getRace() == "Drow")	n *= 1.5;
			player->heal(n);
			message += "You consumed a health pot, restored " + intToString(n) + " HP. ";

		}
		else if(p->getEffect() == "PH"){
			int n = 10;
			if(player->getRace() == "Drow")	n *= 1.5;
			player->takeDamage(n);
			message += "You consumed a poison pot, lost " + intToString(n) + " HP. ";
		}
		else if(p->getEffect() == "BA"){
			int n = 5;
			if(player->getRace() == "Drow")	n *= 1.5;
			player = new atkBuff(n, player);
			message += "You consumed a damage boost pot, gain " + intToString(n) + " Atk in this floor. ";
		}
		else if(p->getEffect() == "WA"){
			int n = 5;
			if(player->getRace() == "Drow")	n *= 1.5;
			player = new atkBuff(-n, player);
			message += "You consumed a damage wound pot, lost " + intToString(n) + " Atk in this floor. ";
		}
		else if(p->getEffect() == "BD"){
			int n = 5;
			if(player->getRace() == "Drow")	n *= 1.5;
			player = new defBuff(n, player);
			message += "You consumed a defence boost pot, gain " + intToString(n) + " Def in this floor. ";
		}
		else if(p->getEffect() == "WD"){
			int n = 5;
			if(player->getRace() == "Drow")	n *= 1.5;
			player = new defBuff(-n, player);
			message += "You consumed a defence wound pot, lost " + intToString(n) + " Def in this floor. ";
		}
		p->getPosition()->setObject(NULL);
		delete p;
		return message;
	}
}

void Game::generatePlayer(){
	int r;
	int c;
	int chamber = rand() % 5 + 1;
	Cell* cell;
	while(1){
		r = rand() % row;
		c = rand() % column;
		Cell* temp = getCell(r, c);
		if(temp && temp->getCh() == '.' && chamber == temp->getChamber()){
			cell = temp;
			break;
		}
	}
	cell->setObject(player);
	player->setPosition(cell);
	return;
}


void Game::generateStair(){
	int r;
	int c;
	Cell* cell;
	while(1){
		r = rand() % row;
		c = rand() % column;
		Cell *temp = getCell(r, c);
		if(temp && temp->getCh() == '.' && temp->getChamber() != player->getPosition()->getChamber()){
			cell = temp;
			break;
		}
	}
	Stair *stair = new Stair();
	stair->setPosition(cell);
	cell->setObject(stair);
	return;
}


void Game::generateEnemies(){
	for(int i = 0; i < 20; i++){	
		int r;
		int c;
		int chance = rand() % 18;
		Cell *cell;
		Enemy *e = NULL;
		while(1){
			r = rand() % row;
			c = rand() % column;
			Cell *temp = getCell(r, c);
			if(temp && temp->getCh() == '.' && !temp->getObject()){
				cell = temp;
				break;
			}
		}
		if(chance < 4){
			e = new Human();
		}else if(chance < 7){
			e = new Dwarf();
		}else if(chance < 12){
			e = new Halfling();
		}else if(chance < 14){
			e = new Elf();
		}else if(chance < 16){
			e = new Orc();
		}else if(chance < 18){
			e = new Merchant();
		}
		enemies[i] = e;
		cell->setObject(e);
		e->setPosition(cell);
	}

	return;
}


void Game::generatePotions(){
	for(int i = 0; i < 10; i++){	
		int r;
		int c;
		int chance = rand() % 6;
		Cell *cell;
		Potion *p = NULL;
		while(1){
			r = rand() % row;
			c = rand() % column;
			Cell *temp = getCell(r, c);
			if(temp && temp->getCh() == '.' && !temp->getObject()){
				cell = temp;
				break;
			}
		}
		
		if(chance == 0){
			p = new Potion("RH");
		}else if(chance == 1){
			p = new Potion("PH");
		}else if(chance == 2){
			p = new Potion("BA");
		}else if(chance == 3){
			p = new Potion("WA");
		}else if(chance == 4){
			p = new Potion("BD");
		}else if(chance == 5){
			p = new Potion("WD");
		}

		cell->setObject(p);
		p->setPosition(cell);
	}

	return;
}


void Game::generateTreasures(){
	for(int i = 0; i < 10; i++){	
		int r;
		int c;
		int chance = rand() % 8;
		Cell *cell;
		Treasure* t = NULL;
		while(1){
			r = rand() % row;
			c = rand() % column;
			Cell *temp = getCell(r, c);
			if(temp && temp->getCh() == '.' && !temp->getObject()){
				cell = temp;
				break;
			}
		}
		
		if(chance < 5){
			t = new NormalHoard();
		}else if(chance < 7){
			t = new SmallHoard();
		}else if(chance < 8){
			t = new DragonHoard();
			Dragon* dragon = t->getDragon();
			int dragIndx;
			Cell* dragPosition;

			while(1){
				dragIndx =rand() % 8;
				dragPosition = cell->getNeighbour(dragIndx);
				if(dragPosition && dragPosition->getCh() == '.' && !dragPosition->getObject()){
					dragon->setPosition(dragPosition);
					dragPosition->setObject(dragon);
					break;
				}
			}
		}

		cell->setObject(t);
		t->setPosition(cell);
	}

	return;
}


void Game::clearFloor(){
	if(player){
		player = player->getPlayer();
		Cell* position= player->getPosition();
		if(position)
			position->setObject(NULL);
		player->setPosition(NULL);
	}
	if(theFloor){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < column; j++){
				// check if the Object is Dragon. If yes, ignore because it will be delete when its hoard is deleted.
				if(theFloor[i][j].getObject() && 
					theFloor[i][j].getObject()->getType() == "enemy" && 
					theFloor[i][j].getObject()->getRace() == "Dragon")
				{
					continue;
				}
				delete theFloor[i][j].getObject();
				theFloor[i][j].setObject(NULL);
			}
		}
	}
	for(int i = 0; i < 20; i++)
		enemies[i] = NULL;
	return;
}


void Game::setLevel(int n){
	level = n;
	return;
}
/**
 * @return int
 */
int Game::getLevel() {
    return level;
}


Cell* Game::getCell(int row, int column){
	Cell *c = &(theFloor[row][column]);
	return c;
}

Enemy** Game::getEnemies(){
	return enemies;
}

void Game::setPlayer(Player* p){
	player = p;
	return;
}

Player* Game::getPlayer(){
	return player;
}

int Game::getRow(){
	return row;
}

int Game::getColumn(){
	return column;
}

int findChamber(int x, int y){
	if(x >= 3 && x <= 28 && y >= 3 && y <= 6){
		return 1;
	}
	if(x >= 4 && x <= 24 && y >= 15 && y <= 21){
		return 2;
	}
	if(x >= 38 && x <= 50 && y >= 10 && y <= 12){
		return 3;
	}
	if((x >= 37 && x <= 75 && y >= 19 && y <= 21) ||
	   (x >= 65 && x <= 75 && y >= 16 && y <= 18)){
		return 4;
	}
	if((x >= 39 && x <= 61 && y >= 3 && y <= 6)  ||
	   (x >= 61 && x <= 75 && y >= 7 && y <= 13) ||
	   (x >= 62 && x <= 69 && y == 5) 			 ||
	   (x >= 62 && x <= 72 && y == 6)){
		return 5;
	}
	else{
		return 0;
	}
}

void Game::notify(int row, int column, char ch){
	controller->notify(row, column, ch);
}
/**
 * @return void
 */
void Game::init(Controller* ctrler) {
	clearFloor();
	delete player;
	controller = ctrler;
	theFloor = new Cell*[row];
	for(int i = 0; i < row; i++){
		theFloor[i] = new Cell[column];
	}
	fstream fs("floor.txt");

	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			char ch;
			int chamber = findChamber(j, i);
			fs >> noskipws >> ch;
			theFloor[i][j].setCell(i, j, ch, chamber, this);
			theFloor[i][j].setNeighbours();
		}
		fs.get();
	}
	fs.close();
    return;
}


void Game::initFloor(){
	level++;
	clearFloor();
	generatePlayer();
	generateStair();
	generatePotions();
	generateTreasures();
	generateEnemies();
}


void Game::initFloor(string floorPlan){
	level++;
	clearFloor();
	stringstream ss(floorPlan);

	int enemyCount = 0;
	Dragon* drag = NULL;
	DragonHoard* dh = NULL;

	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			char c;
			ss >> noskipws >> c;
			if(c == '@'){
				theFloor[i][j].setObject(player);
				player->setPosition(&(theFloor[i][j]));
			}
			else if(c == '\\'){
				Stair* s = new Stair();
				theFloor[i][j].setObject(s);
				s->setPosition(&(theFloor[i][j]));
			}
			else if(c == 'H'){
				Human* h = new Human();

				enemies[enemyCount] = h;
				theFloor[i][j].setObject(h);
				h->setPosition(&(theFloor[i][j]));

				enemyCount++;
			}
			else if(c == 'O'){
				Orc* o = new Orc();

				enemies[enemyCount] = o;
				theFloor[i][j].setObject(o);
				o->setPosition(&(theFloor[i][j]));

				enemyCount++;
			}
			else if(c == 'L'){
				Halfling* l = new Halfling();

				enemies[enemyCount] = l;
				theFloor[i][j].setObject(l);
				l->setPosition(&(theFloor[i][j]));

				enemyCount++;
			}
			else if(c == 'M'){
				Merchant* m = new Merchant();

				enemies[enemyCount] = m;
				theFloor[i][j].setObject(m);
				m->setPosition(&(theFloor[i][j]));

				enemyCount++;
			}
			else if(c == 'E'){
				Elf* e = new Elf();

				enemies[enemyCount] = e;
				theFloor[i][j].setObject(e);
				e->setPosition(&(theFloor[i][j]));

				enemyCount++;
			}
			else if(c == 'W'){
				Dwarf* w = new Dwarf();

				enemies[enemyCount] = w;
				theFloor[i][j].setObject(w);
				w->setPosition(&(theFloor[i][j]));

				enemyCount++;
			}
			else if(c == '0'){
				Potion* p = new Potion("RH");

				theFloor[i][j].setObject(p);
				p->setPosition(&(theFloor[i][j]));
			}
			else if(c == '1'){
				Potion* p = new Potion("BA");

				theFloor[i][j].setObject(p);
				p->setPosition(&(theFloor[i][j]));
			}
			else if(c == '2'){
				Potion* p = new Potion("BD");

				theFloor[i][j].setObject(p);
				p->setPosition(&(theFloor[i][j]));
			}
			else if(c == '3'){
				Potion* p = new Potion("PH");

				theFloor[i][j].setObject(p);
				p->setPosition(&(theFloor[i][j]));
			}
			else if(c == '4'){
				Potion* p = new Potion("WA");

				theFloor[i][j].setObject(p);
				p->setPosition(&(theFloor[i][j]));
			}
			else if(c == '5'){
				Potion* p = new Potion("WD");

				theFloor[i][j].setObject(p);
				p->setPosition(&(theFloor[i][j]));
			}
			else if(c == '6'){
				NormalHoard* h = new NormalHoard();

				theFloor[i][j].setObject(h);
				h->setPosition(&(theFloor[i][j]));
			}
			else if(c == '7'){
				SmallHoard* h = new SmallHoard();

				theFloor[i][j].setObject(h);
				h->setPosition(&(theFloor[i][j]));
			}
			else if(c == '8'){
				MerchantHoard* h = new MerchantHoard();

				theFloor[i][j].setObject(h);
				h->setPosition(&(theFloor[i][j]));
			}
			else if(c == '9'){
				DragonHoard* h = new DragonHoard(drag);
				if(drag){
					drag->setHoard(h);
					drag = NULL;
				}
				else{
					dh = h;
				}
				theFloor[i][j].setObject(h);
				h->setPosition(&(theFloor[i][j]));
			}
			else if(c == 'D'){
				Dragon* d = new Dragon(dh);
				if(dh){
					dh->setDragon(d);
					dh = NULL;
				}
				else{
					drag = d;
				}
				theFloor[i][j].setObject(d);
				d->setPosition(&(theFloor[i][j]));
			}

		}
		ss.get();
	}
	return;
}
