// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============        	  *** Header of Level class ***          ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <string>
#include <fstream>
#include <vector>
#include "window.h"

class Square;
class Board;

class Level {
  protected:
	int seed;
	bool graphical;
	bool bonus;

	std::string fileName; //ex: sequence2.txt
	std::string fileInput; //ex: 012332101123221231011023012021033010123
	int fileInputPos; //starts at 0 representing fileInput[0], increments everytime you create a new square
	bool fromFile;

  public:
  	// This vector is used to keep track of all the locked squares on the board.
  	int lockedSquares;
  	// This is the constructor for the Level class, which should create the 
	//		corresponding board objects.
	Level(int seed, std::string configFile, bool graphical, bool bonus);
	virtual ~Level( );
	// This method is used to the Factory Method, which will create a new square
	//		based on the level one parameters, that is all squares are random.
	virtual Square *createSquare( ) = 0;
	// This method is used in conjunction with the createSquare factory, to set
	//		each cell in the board to be a particular board piece.
	virtual Square ***initializeBoard( Board *, Xwindow *) = 0;
	// This is a getter for the targetScore needed to pass the level.
	virtual int getTargetScore( ) = 0;
	// This is a getter for the boardSize.
	virtual int getBoardSize( ) = 0;
};

#endif
