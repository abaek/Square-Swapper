// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============         *** Header of WallSquare class ***       ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __WALLSQUARE_H__
#define __WALLSQUARE_H__
#include "square.h"
#include <vector>

class WallSquare : public Square  {
  public :
  	// This is the one-three argument constructor for the WallSquare class, where 
  	//		the value for locked, is defaulted to true, and the value for
  	//		type is defaulted to 'l'.
	WallSquare( char colour = 'l', bool locked = true, char type = 'l');
	// This is the default destructor for the wall square.
	~WallSquare( );
	// This method is used to return all the Squares that need to be resolved alongside
	//		the Wall Square.
	std::vector<Square *> clearSquare( );
	// This method is used to draw the unique Wall Square
	void draw();

};

#endif