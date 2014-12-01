// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============         *** Header of LevelOne class ***        ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __LEVELONE_H__
#define __LEVELONE_H__
#include <string>
#include "level.h"
#include "window.h"

class Board;

class LevelOne : public Level {
	int boardSize;
	int targetScore;
	int squaresCreated;
	// This method is used in conjunction with the createSquare method, by creating
	//		a special square with the given colour.
	Square *createSpecial(char colour);
  public:
	// This is the constructor for the Level One class, which should create the 
	//		corresponding level object.
	LevelOne(int seed, std::string configFile, bool graphical, bool bonus, int score);
	// This is the destructor for the level One class.
	~LevelOne( );
	// This method is used to the Factory Method, which will create a new square
	//		based on the level one parameters, that is all squares are random.
	Square *createSquare( );
	// This method is used in conjunction with the createSquare factory, to set
	//		each cell in the board to be a particular board piece.
	Square ***initializeBoard( Board * , Xwindow *w );
	// This is a getter for the targetScore needed to pass the level.
	int getTargetScore( );
	// This is a getter for the boardSize.
	int getBoardSize( );
};

#endif