// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============    *** Implementation of LevelThree class ***    ===============
// ===============                                                  ===============
// ================================================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include "board.h"
#include "level.h"
#include "levelthree.h"
#include "square.h"
#include "basicsquare.h"
#include "lateralsquare.h"
#include "uprightsquare.h"
#include "unstablesquare.h"
#include "psychedelicsquare.h"
#include "wallsquare.h"
#include "window.h"

using namespace std;

class Board;

// This is the constructor for the LevelThree class, which should create the 
//		corresponding board objects.
LevelThree::LevelThree(int seed, bool graphical, bool bonus, int score) : 
					Level(seed, "", graphical, bonus), boardSize(10) {
	targetScore = score + 750;
	lockedSquares = boardSize * 2;
}

// This is the destructor for the levelThree class.
LevelThree::~LevelThree( ) { }

// This method is used to the Factory Method, which will create a new square
//		based on the level two parameters, that is all squares are random.
Square *LevelThree::createSquare( ) {
	Square *newSquare;
	// 1/4 chance for each colour;
	int colour = rand( ) % 4;
	char color = colour + '0';
	newSquare = new BasicSquare(color);
	return newSquare;
}

// This method is used in conjunction with the createSquare factory, to set
//		each cell in the board to be a particular board piece.
Square ***LevelThree::initializeBoard( Board *currentBoard, Xwindow *w ) {
	int boardSize = this->boardSize;
	Square ***newBoard = new Square**[boardSize];
	// Initialize Board
	for ( int row = 0; row < boardSize; row++ ) {
		newBoard[row] = new Square *[boardSize];
		for ( int column = 0; column < boardSize; column++ ) {
			if ( ( column == 1 ) || ( column == 8 ) ){
				newBoard[row][column] = new WallSquare( );
				newBoard[row][column]->setBoard(row, column, currentBoard, w);
			} else {
				// Create a new square for the cell.
				newBoard[row][column] = this->createSquare( );
				newBoard[row][column]->setBoard(row, column, currentBoard, w);
			}
		}
	}

	for ( int row = 0; row < boardSize; row++ ) {
		newBoard[row][0]->locked = true;
		newBoard[row][boardSize-1]->locked = true;
	}

	return newBoard;
}

// This is a getter for the targetScore needed to pass the level.
int LevelThree::getTargetScore( ) {
	return targetScore;
}

// This is a getter for the boardSize.
int LevelThree::getBoardSize( ) {
	return boardSize;
}
