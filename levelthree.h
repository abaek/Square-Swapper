// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============        *** Header of LevelThree class ***        ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __LEVELTHREE_H__
#define __LEVELTHREE_H__
#include <string>
#include <vector>
#include "level.h"
#include "window.h"

class Board;

class LevelThree : public Level {
	// Field for the boardSize of the 
	int boardSize;
	int targetScore;
  public :
	// This is the constructor for the Level Three class, which should create the 
	//		corresponding board object.
	LevelThree(int seed, bool graphical, bool bonus, int score);
	// This is the destructor for the level Three class.
	~LevelThree( );
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
