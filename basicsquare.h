// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============        *** Header of BasicSquare class ***       ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __BASICSQUARE_H__
#define __BASICSQUARE_H__
#include "square.h"

#include <vector>

class Board;

class BasicSquare : public Square  {
  public :
  	// This is the one-three argument constructor for the BasicSquare class, where 
  	//		the value for locked, is defaulted to false, and the value for
  	//		type is defaulted to '_'.
	BasicSquare( char colour, bool locked = false, char type = '_');
	// This is the default destructor for the basic square.
	~BasicSquare( );
	// This method is used to return all the Squares that need to be resolved alongside
	//		the Basic Square.
	std::vector<Square *> clearSquare( );
};

#endif