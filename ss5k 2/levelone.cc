// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============      *** Implementation of LevelOne class ***    ===============
// ===============                                                  ===============
// ================================================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include "level.h"
#include "board.h"
#include "levelone.h"
#include "square.h"
#include "basicsquare.h"
#include "lateralsquare.h"
#include "uprightsquare.h"
#include "unstablesquare.h"
#include "psychedelicsquare.h"
#include "tbombsquare.h"
#include "window.h"

using namespace std;

class Board;

// This is the constructor for the LevelOne class.
LevelOne::LevelOne(int seed, string configFile, bool graphical, bool bonus, int score) : 
					Level(seed, configFile, graphical, bonus), boardSize(10), squaresCreated(1) {
	targetScore = score + 300;
}

// This is the destructor for the levelOne class.
LevelOne::~LevelOne( ) { }

// This method is used in conjunction with the createSquare method, by creating
//		a special square with the given colour.
Square *LevelOne::createSpecial(char colour){
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
//		based on the level one parameters, that is all squares are random.
Square *LevelOne::createSquare( ){
	Square *newSquare;
	int colour;
	char color;
	// Read from file
	if (fromFile) {
		// If reached end of input, start over again
		if (fileInputPos >= fileInput.length()) {
			fileInputPos = 0;
		}
		// Set colour
		color = fileInput[fileInputPos];
		fileInputPos += 1;
	} 
	// Use random
	else {
		// These if statements are to determine what colour the square should be.
		int randomNum = rand( ) % 6;
		// 1/3 chance of green
		if ( randomNum < 2 ) {
			colour = 2;
		// 1/3 chance of blue
		} else if ( randomNum < 4 ) {
			colour = 3;
		// 1/6 chance of white
		} else if ( randomNum < 5 ) {
			colour = 0;
		// 1/6 chance of red
		} else {
			colour = 1;
		}
		
		color = colour + '0';
	}
	
	// This if statement is used to determine whether the square should be special.
	squaresCreated = squaresCreated % 5;
	if ( squaresCreated == 0 ) {
		newSquare = createSpecial(color);
	} else {
		newSquare = new BasicSquare(color);
	}
	squaresCreated++;
	return newSquare;
}

// This method is used in conjunction with the createSquare factory, to set
//		each cell in the board to be a particular board piece.
Square ***LevelOne::initializeBoard( Board *currentBoard, Xwindow *w  ){
	if (fileName == "") {
		int boardSize = this->boardSize;
		Square ***newBoard = new Square**[boardSize];
		// Initialize Board
		for ( int row = 0; row < boardSize; row++ ) {
			newBoard[row] = new Square *[boardSize];
			for ( int column = 0; column < boardSize; column++ ) {
				// Create a new square for the cell
				newBoard[row][column] = this->createSquare( );
				newBoard[row][column]->setBoard(row, column, currentBoard, w);
			}
		}

		return newBoard;
	} else {
		Square ***newBoard = new Square **[boardSize]; 
		// Set up file stream if it exists
		ifstream file;
		file.open((this->fileName).c_str( ));
		
		//initialize board
		for ( int row = 0; row < boardSize; row++ ) {
			newBoard[row] = new Square*[boardSize];
			for ( int column = 0; column < boardSize; column++ ) {
				// Get initialization from file
				string squareStr;
				file >> squareStr;
				// Check if locked
				bool locked;
				if (squareStr[0] == 'l') {
					locked = true;
				} else {
					locked = false;
				}
				// Check if special
				char special;
				//Not special represented by empty string
				if (squareStr[1] == '_') {
					special = '_';
				} else {
					special = squareStr[1];
				}
				// Check colour
				int colour = squareStr[2];

				//set new square;
				if ( special == '_' ) {
					newBoard[row][column] = new BasicSquare(colour, locked, special);
				} else if ( special == 'h' ) {
					newBoard[row][column] = new LateralSquare(colour, locked, special);
				} else if ( special == 'v' ) {
					newBoard[row][column] = new UprightSquare(colour, locked, special);
				} else if ( special == 'b' ) {
					newBoard[row][column] = new UnstableSquare(colour, locked, special);
				} else if ( special == 'p' ) {
					newBoard[row][column] = new PsychedelicSquare(colour, locked, special);
				} else if ( special == 't' ) {
					newBoard[row][column] = new TBombSquare(colour, locked, special);
				}
				newBoard[row][column]->setBoard(row, column, currentBoard, w);
			}
		}
		
		// Set input for new square
		if (file >> this->fileInput) {
			fromFile = true;
			// Reset file input pos to 0
			fileInputPos = 0;
		} else {
			fromFile = false;
		}
		
		
		// Close file stream
		file.close();

		return newBoard;
	}
	
}

// This is a getter for the targetScore needed to pass the level.
int LevelOne::getTargetScore( ) {
	return targetScore;
}

// This is a getter for the boardSize.
int LevelOne::getBoardSize( ){
	return boardSize;
}
