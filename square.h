// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============           *** Header of Square class ***         ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __SQUARE_H__
#define __SQUARE_H__
#include <iostream>
#include <vector>
#include "window.h"

class Board;

class Square {
	// The type of the square
	char type;
protected:
	Xwindow *window;
	// The current colour of the square
	char colour;
	// The length of the match in which the square was involved in.
	int radius;
	// The counter for the number of different colours the squares can be.
	int colourCount;


public:
	// The co-ordinates of the cell
	int r, c;
	// The boolean for whether the state is locked.
    bool locked;
    // A pointer to the current board that the Square lives on.
	Board *currentBoard;
	// This is the default constructor for a square.
	Square(char colour, bool locked, char type, int radius = 3, int colourCount = 4);


	// This is the default destructor for a square.
	virtual ~Square( );
	// This is the unique destructor, that will be used to determine how the square
	//		should be cleared based on what type of Square it is.
	virtual std::vector<Square *> clearSquare( ) = 0;

	// Move Square
	void moveSquare(int r, int c);

	// Getter for the private field colour
	char getColour( );
	
	// Getter for the private field type;
	char getType( );

	// Setter for the r, c, and board field.
	void setBoard(int row, int col, Board *b, Xwindow *w);

	// Set c and r
	void setPosition(int row, int col);

	// Setter for the radius field.
	void setRadius(int n);

	// Draw to graphical
	virtual void draw( );

	// This method is used to determine if the current square is further left or above then the other square.
	bool operator<(const Square& s) const ;
		
};

#endif
