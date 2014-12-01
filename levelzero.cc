// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============    *** Implementation of LevelZero class ***     ===============
// ===============                                                  ===============
// ================================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "level.h"
#include "levelzero.h"
#include "board.h"
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

// The default contrusctor for the levelZero class.
LevelZero::LevelZero(int seed, string configFile, bool graphical, bool bonus, int score) : 
								Level(seed, configFile, graphical, bonus), boardSize(10) { 
	targetScore = score + 200;
}

// The default destructor for the levelZero class.
LevelZero::~LevelZero() { }

// This method is used in the Factory Method, which will create a new square based on
//		the particular level that is being played on.
Square *LevelZero::createSquare( ) {
	Square *newSquare;
	char colour;
	// If reached end of input, start over again
	if (fileInputPos >= fileInput.length()) {
		fileInputPos = 0;
	}
	// Set colour
	colour = fileInput[fileInputPos];
	fileInputPos += 1;
	// Always generate basic square
	newSquare = new BasicSquare(colour);
	return newSquare;
}

// This method is used in conjunction with the createSquare factory, to set each 
//		cell in the board to be a particular board piece.
Square ***LevelZero::initializeBoard( Board * currentBoard, Xwindow *w  ) {
	Square ***newBoard = new Square **[boardSize]; 
	// Set up file stream if it exists
	ifstream file;
	if (this->fileName == "") {
		this->fileName = "sequence.txt";
	}
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
	file >> this->fileInput;
	// Reset file input pos to 0
	fileInputPos = 0;
	// Close file stream
	file.close();

	return newBoard;
}

// This is a getter for the targetScore needed to pass the level.
int LevelZero::getTargetScore( ) {
	return targetScore;
}

// This is a getter for the boardSize.
int LevelZero::getBoardSize( ) {
	return boardSize;
}