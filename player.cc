// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============     *** Implementation of Player class ***       ===============
// ===============                                                  ===============
// ================================================================================

#include <iostream>
#include <string>
#include "player.h"
#include "board.h"
#include "level.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"

using namespace std;
	
// This is the default constructor for a new player.
Player::Player( ) : seed(0), configFile(""), level(0), graphical(true), bonus(false),
				totalLevels(2), currentBoard(NULL), currentLevel(NULL), score(0), name("") { }

// This is the default destructor for a player.
Player::~Player( ) {
	// This delete statement should also delete the board, and all resulting squares.
	delete currentBoard;
}

// This is the setter method for the seed field.
void Player::setSeed(int seed) {
	this->seed = seed;
}
	
// This is the setter method for the configFile field.
void Player::setConfigFile(string configFile) {
	this->configFile = configFile;
}
	
// This is the setter method for the level field, for the -startlevel option.
void Player::setLevel(int level) {
	if ( level > totalLevels ) {
		this->level = totalLevels;
	} else {
		this->level = level;
	}
}
	
// This is the setter method for the level field, for the levelup command.
void Player::levelUp() {
	configFile = "";
	// Hit upper bound on levels
	if (this->level < totalLevels) {
		this->level += 1;
	} else {
		cout << "New levels coming soon!" << endl;
	}
}

// This is the setter method for the level field, for the leveldown command.
void Player::levelDown() {
	configFile = "";
	if (this->level > 0) {
		this->level -= 1;
	} else {
		cout << "Already on level 0" << endl;
	}
}

// This is the setter method for the graphical field, for the -text option.
void Player::setGraphical(bool cmd) {
	this->graphical = cmd;
}

// This is the setter method for the bonus field, for the -nobonus option.
void Player::setBonus(bool cmd) {
	this->bonus = cmd;
	this->totalLevels = 4;
}

// This method is used to start the game, based on the seed, configFile, and level
//		fields inside the Player object.
void Player::restart( ) {
		
	//Delete the currentBoard & currentLevel
	if (currentBoard != NULL) {
		// board deletes the level
		delete currentBoard;
		currentLevel = NULL;
	}


	// Create the new Level using the proper settings
	bool scramble = true;
	if ( level == 0 ) {
		currentLevel = new LevelZero(seed, configFile, graphical, bonus, score);
		scramble = false;
	} else if ( level == 1 ) {
		currentLevel = new LevelOne(seed, configFile, graphical, bonus, score);
	} else if ( level == 2 ) {
		currentLevel = new LevelTwo(seed, configFile, graphical, bonus, score);
	} else if ( level == 3 ) {
		currentLevel = new LevelThree(seed, graphical, bonus, score);
	} else if ( level == 4 ) {
		currentLevel = new LevelFour(seed, graphical, bonus, score);
	}

	if (configFile != "") {
		scramble = false;
	}

	// Set the new board based on the new Level
	currentBoard = new Board(this->currentLevel, graphical, bonus);
	currentBoard->initializeGrid( );

	// On levels other than one, scramble the board after the board is created.
	if ( scramble ) {
		scramble = currentBoard->scramble( );
	}
	
	// If the board is not scrambled still, the destroy the old board and create a new one.
	if ( !scramble ) {
		this->restart( );
	}

	// If the game is played with graphical, then print the graphical display.
	if ( graphical ) {
	    printGraphical();
	}
}

// This method is used to execute the swap method on the board, where (x,y) are
//		co-ordinates of the square and the direction represents which cell is 
//		being swapped. (0 for north, 1 for south, 2 for west, and 3 for east).
void Player::swap(int x, int y, int direction){
	// Swap the pieces
	currentBoard->swap(x, y, direction);

	// Returns the points scored for the latest swap
	int pointsForSwap = currentBoard->getLatestPoints();
	score += pointsForSwap;
	
	// Check whether score has reached objective
	if ((score >= currentLevel->getTargetScore()) && (currentLevel->lockedSquares == 0)) {
		cout << "Level up!" << endl;
		int newLevel = this->level + 1;
		cout << "Loading level" << newLevel << endl;
		configFile = "";
		this->levelUp();
		this->restart();
	}

}
	
// This method is used to execute the hint method on the board, which should
//		print out a valid move (x,y,z) to the standard output.
void Player::hint( ) {
	// The hint method inside level should call the hint method on the board, which
	//	   will then cout a valid move on the board.
	int *coords = currentBoard->hint( );
	if ( coords[0] != -1 ) {
		cout << "A valid move with (x,y,z) co-ordinates are: "; 
		cout << "x: " << coords[0] << " y: " << coords[1] << " z: " << coords[2] << endl;
	} else {
		cout << "There are no more valid moves on the current board." << endl;
	}
	delete coords;
}
	
// This method is used to check whether or not there are any valids moves left
//		on the board.
bool Player::validScramble( ) {
	// One possible implementation is to check if there is a valid hint, and if not
	//	   then we can return that there is or is not a valid scramble.
	return currentBoard->noMovesLeft( );
}

bool Player::matchExists( ) {
	return currentBoard->matchExists( );
}
	
// This method is called if there are no valid moves, and calls the scramble
//		method on the board, mixing up all the current squares.
void Player::scramble( ) {
	bool scramble = false;
	// The scramble method inside level should call the scramble method on the board,
	//     which will actually mix up all the squares on the board. That is, the board
	//     should have the exact same squares as prior to shuffling.
	scramble = currentBoard->scramble( );
	if ( !scramble ) {
		this->scramble( );
	}
}

// This method is used to print the board.
void Player::printBoard( ) {
	cout << "Level:            " << level << endl;
    cout << "Score:            " << score << endl;
    cout << "Score to Level:   " << currentLevel->getTargetScore( ) << endl;

    // If the game is played in graphical version, then print the appropriate score along with the display.
    if (currentBoard->graphical) {
    	currentBoard->drawScore(score);
    	currentBoard->drawScoreToLevel(currentLevel->getTargetScore( ));
    }

    // Check if there are locked squares.
    if ( currentLevel->lockedSquares != 0) {
	    cout << "Locked remaining: " << currentLevel->lockedSquares << endl;
    }

	cout << *currentBoard;
}

// This method is called to print the graphical of the board.
void Player::printGraphical() {
	if (graphical) {
		currentBoard->drawBoard();
	}	
}

// This method is used as a helper for print graphical, and is used to draw each square.
void Player::drawBorder(int colour, int x, int y) {
	currentBoard->drawBorder(colour, x, y);
}


