// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============      *** Header of UnstableSquare class ***      ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __UNSTABLESQUARE_H__
#define __UNSTABLESQUARE_H__
#include "square.h"

class UnstableSquare : public Square  {
  public :
	// This is the one-three argument constructor for the UnstableSquare class, where 
  	//		the value for locked, is defaulted to false, and the value for
  	//		type is defaulted to 'b'.
	UnstableSquare( char colour, bool locked = false, char type = 'b');
	// This is the default destructor for the unstable square.
	~UnstableSquare( );
	// This method is used to return all the Squares that need to be resolved alongside
	//		the unstable Square.
	std::vector<Square *> clearSquare( );
	// This method is used to draw the unique unstable Square
	void draw();
};

#endif