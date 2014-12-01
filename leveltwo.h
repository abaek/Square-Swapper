// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============         *** Header of LevelTwo class ***        ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __LEVELTWO_H__
#define __LEVELTWO_H__
#include <string>
#include <vector>
#include "level.h"
#include "window.h"

class Board;

class LevelTwo : public Level {
	// Field for the boardSize of levelTwo. Set to 10.
	int boardSize;
	// Field for the score needed to move to the next level.
	int targetScore;
  public :
	// This is the constructor for the Level Two class, which should create the 
	//		corresponding board object.
	LevelTwo(int seed, std::string configFile, bool graphical, bool bonus, int score);
	// This is the destructor for the level Two class.
	~LevelTwo( );
	// This method is used to the Factory Method, which will create a new square
	//		based on the level two parameters, that is all squares are random.
	Square *createSquare( );
	// This method is used in conjunction with the createSquare factory, to set
	//		each cell in the board to be a particular board piece.
	Square ***initializeBoard( Board *, Xwindow *w );
	// This is a getter for the targetScore needed to pass the level.
	int getTargetScore( );
	// This is a getter for the boardSize.
	int getBoardSize( );
};

#endif