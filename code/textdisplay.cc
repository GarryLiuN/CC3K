/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#include "textdisplay.h"
#include <iostream>

using namespace std;

/**
 *	consume row number and column number
 * 	constract the TextDisplay
 */
TextDisplay::TextDisplay(int row, int column) : row(row), column(column) {
	theDisplay = new char* [row];
	for(int i = 0; i < row; i++){
		theDisplay[i] = new char [column];
		for(int j = 0; j < column; j++)
			theDisplay[i][j] = ' ';
	}
}

/**
 *	detor will delete all elements in theDisplay
 */
TextDisplay::~TextDisplay() {
	for(int i = 0; i < row; i++){
		delete [] theDisplay[i];
	}
	delete[] theDisplay;
	theDisplay = NULL;
}

/**
 *	modify theDisplay[row][column] to ch
 */
void TextDisplay::notify(int row, int column, char ch) {
	theDisplay[row][column] = ch;
    return;
}

/**
 * 	print theDisplay to out
 */
void TextDisplay::print(ostream& out) {
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++)
			out << theDisplay[i][j];
		out << endl;
	}
	return;
}
