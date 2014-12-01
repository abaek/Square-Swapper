// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============       *** Header of UprightSquare class ***      ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __UPRIGHTSQUARE_H__
#define __UPRIGHTSQUARE_H__
#include "square.h"

class UprightSquare : public Square  {
  public :
	// This is the one-three argument constructor for the UprightSquare class, where 
  	//		the value for locked, is defaulted to false, and the value for
  	//		type is defaulted to 'v'.
	UprightSquare( char colour, bool locked = false, char type = 'v');
	// This is the default destructor for the upright square.
	~UprightSquare( );
	// This method is used to return all the Squares that need to be resolved alongside
	//		the upright Square.
	std::vector<Square *> clearSquare( );
	// This method is used to draw the unique upright Square
	void draw();
};

#endif