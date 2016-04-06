/*	
 *	CC3K - 2015 Fall
 *	cc3k.cc
 *	created by Nian Liu and Jiancheng Chen
 */
 

#include "controller.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]){
	srand(time(NULL));
	Controller c;
	c.init();
	if(argc <= 1){
		c.mainManu();
	}
	else{
		string saveFile = argv[1];
		cout << saveFile << endl;
		c.loadGame(saveFile);
	}

}
