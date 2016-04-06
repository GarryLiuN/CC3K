/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */


#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H
#include <iostream>

class TextDisplay {
private: 
	/**
	 * row * column display
	 * theDisplay[row][column]
	 * theDisplay[25][79]
	 */
	char** theDisplay;
	
public: 
	int const row;
	int const column;
	
	/**
	 *	consume row number and column number
	 * 	constract the TextDisplay
	 */
	TextDisplay(int row, int column);
	
	/**
	 *	detor will delete all elements in theDisplay
	 */
	~TextDisplay();
	
	/**
	 *	modify theDisplay[row][column] to ch
	 */
	void notify(int row, int column, char ch);
	
	/**
	 * 	print theDisplay to out
	 */
	void print(std::ostream& out);

};

#endif //_TEXTDISPLAY_H
