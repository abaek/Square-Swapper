// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============         *** Header of LevelZero class ***        ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __LEVELZERO_H__
#define __LEVELZERO_H__
#include <string>
#include "level.h"
#include "window.h"

class Square;
class Board;

class LevelZero : public Level {
	// Field for the boardSize of the level
	int boardSize; // 10
	// Field for the score required to pass the level.
	int targetScore;

	
  public:
  	// This is the constructor for the Level Zero class, which should create the 
	//		corresponding level object.
	LevelZero(int seed, std::string configFile, bool graphical, bool bonus, int score);
	// This is the destructor for the Level Zero class.
	~LevelZero();
	// This method is used in the Factory Method, which will create a new square based on
	//		the particular level that is being played on.
	Square *createSquare( );
	// This method is used in conjunction with the createSquare factory, to set each 
	//		cell in the board to be a particular board piece.
	Square ***initializeBoard( Board *currentBoard, Xwindow *w );
	// This is a getter for the targetScore needed to pass the level.
	int getTargetScore( );
	// This is a getter for the boardSize.
	int getBoardSize( );
};

#endif