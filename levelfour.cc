// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============     *** Implementation of LevelFour class ***    ===============
// ===============                                                  ===============
// ================================================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include "board.h"
#include "level.h"
#include "levelfour.h"
#include "square.h"
#include "basicsquare.h"
#include "lateralsquare.h"
#include "uprightsquare.h"
#include "unstablesquare.h"
#include "psychedelicsquare.h"
#include "tbombsquare.h"
#include "wallsquare.h"
#include "window.h"

using namespace std;

class Board;

// This is the constructor for the LevelFour class, which should create the 
//		corresponding board objects.
LevelFour::LevelFour(int seed, bool graphical, bool bonus, int score) : 
					Level(seed, "", graphical, bonus), boardSize(15) {
	targetScore = score + 1000;
	if ( (boardSize % 2) == 1 ) {
		lockedSquares = (boardSize * 2) - 1;
	} else {
		lockedSquares = (boardSize - 2) * 2;
	}
}

// This is the destructor for the LevelFour class.
LevelFour::~LevelFour( ) { }

// This method is used in conjunction with the createSquare method, by creating
//		a special square with the given colour.
Square *LevelFour::createSpecial(char colour){
	Square *newSquare = NULL;
	int randomNum;
	// Determine probability of getting each type based on bonus feature.
	if ( bonus ) {
		randomNum = rand( ) % 5;
	} else {
		randomNum = rand( ) % 4;
	}
	// 1/5 chance of getting a upright square.
	if ( randomNum == 0 ) {
		newSquare = new UprightSquare(colour);
	// 1/5 chance of getting a lateral square.
	} else if ( randomNum == 1 ) {
		newSquare = new LateralSquare(colour);
	// 1/5 chance of getting an unstable square.
	} else if ( randomNum == 2 ) {
		newSquare = new UnstableSquare(colour);
	// 1/5 chance of getting a psychedelic square.
	} else if ( randomNum == 3 ) {
		newSquare = new PsychedelicSquare(colour);
	} else if ( randomNum == 4 ) {
		newSquare = new TBombSquare(colour);
	}

	return newSquare;
}

// This method is used to the Factory Method, which will create a new square
//		based on the level two parameters, that is all squares are random.
Square *LevelFour::createSquare( ) {
	Square *newSquare;
	// 1/4 chance for each colour;
	int colour = rand( ) % 4;
	char color = colour + '0';
	// 1/8 chance for a special square to appear.
	int special = rand( ) % 8;
	if ( special == 0 ) {
		newSquare = createSpecial(color);
	} else {
		newSquare = new BasicSquare(color);
	}
	return newSquare;
}

// This method is used in conjunction with the createSquare factory, to set
//		each cell in the board to be a particular board piece.
Square ***LevelFour::initializeBoard( Board *currentBoard, Xwindow *w ) {
	int boardSize = this->boardSize;
	Square ***newBoard = new Square**[boardSize];
	// Initialize Board
	for ( int row = 0; row < boardSize; row++ ) {
		newBoard[row] = new Square *[boardSize];
		for ( int column = 0; column < boardSize; column++ ) {
			if ( row == 0 ) {
				if (( column == 1 ) || ( column == (boardSize - 2) )) {
					newBoard[row][column] = new WallSquare( );
					newBoard[row][column]->setBoard(row, column, currentBoard, w);
				} else {
					// Create a new square for the cell.
					newBoard[row][column] = this->createSquare( );
					newBoard[row][column]->setBoard(row, column, currentBoard, w);
				}
			} else if ( row == (boardSize-1) ) {
				if (( column == (boardSize - 2) ) || ( column == 1 )) {
					newBoard[row][column] = new WallSquare( );
					newBoard[row][column]->setBoard(row, column, currentBoard, w);					
				} else {
					// Create a new square for the cell.
					newBoard[row][column] = this->createSquare( );
					newBoard[row][column]->setBoard(row, column, currentBoard, w);
				}
			} else {
				if (( column == (row + 1) ) || ( column == (row - 1) )
					|| ( column == (boardSize-row) ) || ( column == (boardSize-row-2) )) {
					newBoard[row][column] = new WallSquare( );
					newBoard[row][column]->setBoard(row, column, currentBoard, w);					
				} else {
					// Create a new square for the cell.
					newBoard[row][column] = this->createSquare( );
					newBoard[row][column]->setBoard(row, column, currentBoard, w);
				}
			}
		}
	}

	// Set all squares on the diagonal to locked.
	for ( int row = 0; row < boardSize; row++ ) {
		newBoard[row][row]->locked = true;
		newBoard[row][boardSize-row-1]->locked = true;
	}

	return newBoard;
}

// This is a getter for the targetScore needed to pass the level.
int LevelFour::getTargetScore( ) {
	return targetScore;
}

// This is a getter for the boardSize.
int LevelFour::getBoardSize( ) {
	return boardSize;
}