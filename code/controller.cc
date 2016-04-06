/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#include "controller.h"
#include "player.h"
#include "cell.h"
#include "enemy.h"
#include "buff.h"
#include "buffdeco.h"
#include "treasure.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

/**
 * Controller implementation
 */


Controller::Controller() {
	game = new Game(25, 79);
	td = new TextDisplay(25, 79);
}

Controller::~Controller() {
	delete game;
	delete td;
}

void Controller::mainManu(){

    string command = "new";
    fstream fs("mainmanu.txt");
    cout << fs.rdbuf() << endl;
    fs.close();

    if(cout.fail()){
       cout.clear();
        fstream fsOnFail("mainmanuOnFail.txt");
        cout << fs.rdbuf() << endl;
        fsOnFail.close();
    }
    cout << endl << "Do you want to start a new game or load save?  ";
    cin >> command;
    if(command == "load"){
        string file;
        cin >> file;
        loadGame(file);
    }
    else if(command == "exit"){
        exit(1);
    }
    else{
        newGame();
    }
}

void printOldman(string line1, string line2, string line3){
    // load old man ACSII pic
    fstream fs("oldman.txt");
    string man[20];

    for (int i = 0; i < 20; i++){
        getline(fs, man[i]);
    }
    fs.close();

    for(int i = 0; i < 10; i++){
        cout << man[i] << endl;
    }
    cout << man[10] << setw(25) << left << line1 << "|" << endl;;
    cout << man[11] << setw(25) << line2 << "|" << endl;;
    cout << man[12] << setw(25) << line3 << "|" << endl;;
    for(int i = 13; i < 20; i++){
        cout << man[i] << endl;
    }
    return;
}


void Controller::notify(int row, int column, char ch) {
	td->notify(row, column, ch);
    return;
}


string intToString(int n){
    stringstream ss;
    ss << n;
    return ss.str();
}

/**
 * 	print out player state
 */
void Controller::printStat(string message) {
	Player* player = game->getPlayer();
	// get floor number
	string floor = intToString(game->getLevel());

    string race = "N/A";
    string gold = "0";
    string HP = "0";
    string MAX_HP = "0";
    string Atk = "0";
    string Def = "0";

    if(player){
    	//	get player stat and convert to sting
    	race = player->getRace( );
    	gold = intToString(player->getGold());
    	HP = intToString(player->getHP());
    	MAX_HP = ((player->getRace() == "Vampire") ? "???" : intToString(player->getMaxHP()));
        Atk = intToString(player->getAtk());
        Def = intToString(player->getDef());
    }

    // print state
    cout << setw(50) << left << "Race: " + race + "   Gold: " + gold << "Floor: " + floor << endl;
    cout << "HP: " << HP << "/" << MAX_HP << endl;
    cout << "Atk: " << Atk << endl;
    cout << "Def: " << Def << endl;
    cout << "Action: " + message << endl;
    return;
}


void Controller::init() {
    game->init(this);
    return;
}

void Controller::createPC(){

    td->print(cout);
    printStat("");
    string line1 = "Welcome to the Dungeon!";
    string line2 = "Tell me who you are." ;
    string line3 = "";

    delete game->getPlayer();

    while(1){
        printOldman(line1, line2, line3);
        cout << "Choose your race: (s)hade, (d)row, (v)ampire, (t)roll, (g)oblin" << endl;
        char c;
        cin >> c;
        Player* p = NULL;
        if(cin.eof()){
            exit(0);
        }
        if(c == 's'){
            printOldman("A Shade!", "HP 120, Atk 25, Def 25.", "Not a special one...");
            p = new Shade();
        }
        else if(c == 'd'){
            printOldman("Drow! A dark elf.", "HP 150, Atk 25, Def 15.", "Magnify potion power!");
            p = new Drow();
        }
        else if(c == 'v'){
            printOldman("A Vampire, huh?", "HP 50, Atk 25, Def 25.", "Drain enemy's health!");
            p = new Vampire();  
        }
        else if(c == 't'){
            printOldman("Troll! strong one", "HP 120, Atk 25, Def 15.", "You can Heal yourself!");
            p = new Troll();    
        }   
        else if(c == 'g'){
            printOldman("A sneaky sneaky Goblin!", "HP 110, Atk 15, Def 20.", "Steal gold upon killing!");
            p = new Goblin();   
        }   
        else{
            line1 = "That's not the answer!";
            continue;
        }

        cout << "Are you sure about your decision? [y/n]" << endl;
        cin >> c;
        if(c == 'n'){
            line1 = "Then tell me who you are.";
            delete p;
            p = NULL;
            continue;
        } 
        else if (c == 'y'){
            printOldman("Good Luck, brave one!", "You may enter the Dungeon.", "Try not to get killed..");
            cout << "Enter anything to continue" << endl;
            cin.ignore();
            cin.get();
            game->setPlayer(p);
            break;
        }
        else{
            line1 = "That's not the answer!";
            continue;
        }
    }
}


void Controller::devMode(string loaded){
        cout << "Enter dev mode." << endl;
        cout << "Possible commands:" << endl;
        cout << "   addGold [n] : add n gold to player character's account" << endl;
        cout << "   setDef  [n] : set player character Def to n" << endl;
        cout << "   setAtk  [n] : set player character Atk to n" << endl;
        cout << "   setHP   [n] : set player character HP to n (may exceed MAX_HP)" << endl;
        cout << "   heal    [n] : heal player character n HP" << endl;
        cout << "   atkBuff [n] : add an Atk Buff/Debuff n to player character" << endl;
        cout << "   defBuff [n] : add a Def Buff/Debuff n to player character" << endl;
        cout << "   coord       : print player character's coordination [row] [column]" << endl;
        cout << "   chamber     : print player's current chamber" << endl;
        cout << "   nextFloor   : immediately enter next floor" << endl;
        cout << "   devend      : quit dev mode" << endl;
        cout << "   merHost [b] : make merchants hostile or friendly. " << endl;
        cout << "   move [d] [n]: move to [d] [n] steps" << endl;
    while(1){
        string cmd;
        cin >> cmd;
        if(cin.fail()){ 
            cin.clear();
            cin.ignore();
            return;
        }
        if(cmd == "devend")    return;
        if(cmd == "addGold"){
            int n;
            cin >> n;
            game->getPlayer()->addGold(n);
            cout << "Gold: " << game->getPlayer()->getGold() << endl;
        }
        else if(cmd == "setAtk"){
            int n;
            cin >> n;
            game->getPlayer()->setAtk(n);
            cout << "Atk is now " << n << endl;
        }
        else if(cmd == "setDef"){
            int n;
            cin >> n;
            game->getPlayer()->setDef(n);
            cout << "Def is now " << n << endl;
        }
        else if(cmd == "setHP"){
            int n;
            cin >> n;
            game->getPlayer()->setHP(n);
            cout << "HP is now " << n << " (if exceeds MAX_HP, will be set to MAX_HP upon next heal)" << endl;
        }
        else if(cmd == "heal"){
            int n;
            cin >> n;
            game->getPlayer()->heal(n);
            cout << "HP is now " << game->getPlayer()->getHP() << endl;
        }
        else if(cmd == "coord"){
            Cell* c = game->getPlayer()->getPosition();
            cout << c->getRow() << " " << c->getColumn() << endl;
        }
        else if(cmd == "chamber"){
            Cell *c = game->getPlayer()->getPosition();
            cout << c->getChamber() << endl;
        }
        else if(cmd == "merHost"){
            string s;
            cin >> s;
            if(s == "t"){
                Merchant::hostile = true;
                cout << "Merchants are now hostile." << endl;
            }
            else if(s == "f"){
                Merchant::hostile = false;
                cout << "Merchants are now friendly." << endl;
            }
        }
        else if(cmd == "atkBuff"){
            int n;
            cin >> n;
            game->setPlayer(new atkBuff(n, game->getPlayer()));
            cout << "Atk is now buffed to " << game->getPlayer()->getAtk() << endl;
        }
        else if(cmd == "defBuff"){
            int n;
            cin >> n;
            game->setPlayer(new defBuff(n, game->getPlayer()));
            cout << "Def is now buffed to " << game->getPlayer()->getAtk() << endl;
        }
        else if(cmd == "nextFloor"){
            if(game->getLevel() == 5){
                cout << "Can't go deeper, it is the last floor." << endl;
            }
            else{
                if(loaded == "")
                    newFloor();
                else
                    newFloor(loaded);
                cout << "Moved to floor " << game->getLevel() << endl;
            }
        }
        else if(cmd == "move"){
            string d;
            int n;
            cin >> d;
            cin >> n;
            while(n > 0){
                game->getPlayer()->playerMove(d);
                n--;
            }
            td->print(cout);
        }

    }
}

void Controller::newGame() {
    Merchant::hostile = false;
    game->setLevel(0);
    game->clearFloor();
    createPC();
    game->initFloor();
    play("You entered the dungeon.", "");
    return;
}

void Controller::newFloor(){
    game->initFloor();
    return;
}

void Controller::newFloor(string loaded){
    fstream fs(loaded.c_str());
    while(fs.fail()){
        cout << "File doesn't exist. Enter the correct file name." << endl;
        string s;
        cin >> s;
        fs.close();
        fs.clear();
        fs.open(s.c_str());

    }
    int level = game->getLevel();    
    int row = game->getRow();

    string s;
    string floor = "";

    for(int i = 0; i < row * level; i++){
        getline(fs, s);
    }

    for(int i = 0; i < row; i++){
        getline(fs, s);
        floor += s + "\n";
    }
    game->initFloor(floor);
    return;
}

void Controller::loadGame(string file) {
    Merchant::hostile = false;
    game->setLevel(0);
    game->clearFloor();
    createPC();
    newFloor(file);
    play("Game loaded.", file);
    return;
}

void Controller::restart(){
    game->setLevel(0);
    game->clearFloor();
    createPC();
    game->initFloor();
}


void Controller::play(string msg, string loaded){
    string message = msg;
    bool dead = false;

    while(1){
        bool dragAtk = false;
        Player* player = game->getPlayer();
        td->print(cout);
        printStat(message);
        message = "";

        if(dead){
            dead = false;
            printOldman("What a waste..", "Another dead explorer.", "Sigh....");
            cout << "You are Dead! Do you want to start a new game? [y/n]" << endl;
            string s;
            cin >> s;
            if(s == "y"){
                restart();
                continue;
            }
            else{
                mainManu();
                return;
            }
        }

        cmd__:
        string command;

        cin >> command;

        if(cin.eof() || command == "q"){
            return;
        }
        else if(command == "r"){
            dead = false;
            loaded = "";
            restart();
            message += "You entered the dungeon. ";
            continue;
        }
        else if(command == "manu"){
            cout << "Are you sure you want to go to main manu? You will lose unsaved progress.[y/n]  ";
            string s;
            cin >> s;
            if(s == "y"){
                mainManu();
                return;
            }
            else goto cmd__;
        }
        else if(command == "dev"){
            devMode(loaded);
            message = "Dev commands activated!";
            continue;
        }
        else if(command == "stay"){
            message += "You stood still. ";
        }
        else if(command == "nw" || command == "no" || command == "ne" || 
                command == "we" || command == "ea" ||
                command == "sw" || command == "so" || command == "se"){

            string move_msg = player->playerMove(command);
        
            if(move_msg == "nextFloor"){
                if(game->getLevel() == 5){
                    printOldman("You havedefeated the", "Chambers! You are a", "true hero!");
                    cout << "Congrats, you survived the dungeon! " << endl;
                    int score = player->getRace() == "Shade" ? 
                                player->getGold() * 1.5      :
                                player->getGold();
                    cout << "Your score is " << score << ". ";
                    cout << "Do you want to start a new game? [y/n]   ";
                    string s;
                    cin >> s;
                    if(s == "y"){
                        dead = false;
                        loaded = "";
                        restart();
                        message += "You entered the dungeon. ";
                        continue;
                    }
                    else{
                        mainManu();
                        return;
                    }
                }
                message += "You entered the deeper floor. ";
                if(loaded == "")
                    newFloor();
                else
                    newFloor(loaded);
                continue;
            }
            else if(isdigit(move_msg[0])){
                message += "You moved to " + command + ". Found " + move_msg + " golds. ";
            }
            else if(move_msg != "You moved to "){
                message += move_msg + command +". ";
                continue;
            }
            else{
                message += move_msg + command + ". ";
            }
        }
        else if(command == "a"){
            string s;
            cin >> s;
            string atk_msg = game->playerAttack(s);
            if(atk_msg == "noenemy"){
                message += "There is no enemy on " + s + ". ";
                continue;
            }
            else{
                message += atk_msg;
            }
        }
        else if(command == "u"){
            string s;
            cin >> s;
            message += game->consumePotion(s);
        }
        else{
            message += "Invalid input!";
            continue;
        }

        if(player->getHP() == 0){
            dead = true;
            continue;
        }

        Cell** neighbours = player->getPosition()->getNeighbours();
        Enemy** enemies = game->getEnemies();

        // check if enemy is dead. If yes, delete the enemy and drop golds
        for(int i = 0; i < 20; i++){
            Enemy* e = enemies[i];
            if(e && e->getHP() == 0){
                if(player->getRace() == "Goblin")
                    player->addGold(5);
                enemies[i]->dropGold();
                enemies[i]->setPosition(NULL);
                delete enemies[i];
                enemies[i] = NULL;
            }
        }


        // the neighbour enemies will attack player
        for(int i = 0; i < 8; i++){
            Object* obj = neighbours[i]->getObject();
            Enemy *e = NULL;
            if(obj && obj->getType() == "enemy"){                    
                e = static_cast<Enemy*>(obj);
                if(obj->getRace() == "Dragon")
                    e->actClear();
            }
            else if(obj && 
                    obj->getType() == "treasure" &&
                    static_cast<Treasure*>(obj)->getSize() == "Dragon")
            {
                e = static_cast<DragonHoard*>(obj)->getDragon();
                if(e)
                    e->actClear();
            }

            if(e){
                if(e->getRace() == "Merchant" && !Merchant::hostile){
                    message += "A friendly Merchant is there. ";
                    continue;
                }
                if(!(e->isActed())){
                    if(e->getRace() == "Dragon" && dragAtk)
                        continue;
                    else if(e->getRace() == "Dragon")
                        dragAtk = true;
                    message += e->Damage(player);
                    e->act();
                    if(player->getHP() == 0){
                        dead = true;
                        continue;
                    }
                }
            }
        }

        // move all enemies
        for(int i = 0; i < 20; i++){
            if(enemies[i]){
                if(!enemies[i]->isActed()){
                    int count = 0;
                    emy_move__:
                    int move = rand() % 4;
                    string mv_msg = enemies[i]->move(move);
                    count++;
                    if(mv_msg == "nomove" && count != 8)
                        goto emy_move__;
                }
                enemies[i]->actClear();
            }
        }

        if(!dead && player->getRace() == "Troll" && player->getHP() != player->getMaxHP()){
            player->heal(5);
            message += "Healed yourself 5 HP. ";
        }
    }
}
