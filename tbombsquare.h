// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============         *** Header of TBombSquare class ***      ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __TBOMBSQUARE_H__
#define __TBOMBSQUARE_H__
#include "square.h"

class TBombSquare : public Square  {
  public :
	// This is the one-three argument constructor for the UprightSquare class, where 
  	//		the value for locked, is defaulted to false, and the value for
  	//		type is defaulted to 'v'.
	TBombSquare( char colour, bool locked = false, char type = 't');
	// This is the default destructor for the upright square.
	~TBombSquare( );
	// This method is used to return all the Squares that need to be resolved alongside
	//		the upright Square.
	std::vector<Square *> clearSquare( );
	// This method is used to draw the unique tbomb Square
	void draw();
};

#endif