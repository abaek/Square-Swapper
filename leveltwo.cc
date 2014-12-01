// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============      *** Implementation of LevelTwo class ***    ===============
// ===============                                                  ===============
// ================================================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include "board.h"
#include "level.h"
#include "leveltwo.h"
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

// This is the constructor for the LevelTwo class, which should create the 
//		corresponding board objects.
LevelTwo::LevelTwo(int seed, string configFile, bool graphical, bool bonus, int score) : 
					Level(seed, configFile, graphical, bonus), boardSize(10) {
	targetScore = score + 500;
	lockedSquares = (boardSize * boardSize) / 5;
}

// This is the destructor for the levelTwo class.
LevelTwo::~LevelTwo( ) { }

// This method is used to the Factory Method, which will create a new square
//		based on the level two parameters, that is all squares are random.
Square *LevelTwo::createSquare( ) {
	Square *newSquare;
	char color;
	if (fromFile) {
		// If reached end of input, start over again
		if (fileInputPos >= fileInput.length()) {
			fileInputPos = 0;
		}
		// Set colour
		color = fileInput[fileInputPos];
		fileInputPos += 1;
	} else {
		// 1/4 chance for each colour;
		int colour = rand( ) % 4;
		color = colour + '0';
	}
	newSquare = new BasicSquare(color);
	return newSquare;
}

// This method is used in conjunction with the createSquare factory, to set
//		each cell in the board to be a particular board piece.
Square ***LevelTwo::initializeBoard( Board *currentBoard, Xwindow *w  ) {
	if (fileName == "") {
		int boardSize = this->boardSize;
		int numLockedSquare = (boardSize * boardSize) / 5;
		Square ***newBoard = new Square**[boardSize];
		// Initialize Board
		for ( int row = 0; row < boardSize; row++ ) {
			newBoard[row] = new Square *[boardSize];
			for ( int column = 0; column < boardSize; column++ ) {
				// Create a new square for the cell.
				newBoard[row][column] = this->createSquare( );
				newBoard[row][column]->setBoard(row, column, currentBoard, w);
			}
		}

		// Change 20% of the board to locked squares.
		for ( int i = 0; i < numLockedSquare; i++ ) {
			while ( true ) {
				int randRow = rand( ) % 10;
				int randCol = rand( ) % 10;
				bool lock = newBoard[randRow][randCol]->locked;
				if ( !lock ) {
					// lockedSquares.push_back(newBoard[randRow][randCol]);
					newBoard[randRow][randCol]->locked = true;
					break;
				}
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
int LevelTwo::getTargetScore( ) {
	return targetScore;
}

// This is a getter for the boardSize.
int LevelTwo::getBoardSize( ) {
	return boardSize;
}
