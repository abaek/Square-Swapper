// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============       *** Header of LateralSquare class ***      ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __LATERALSQUARE_H__
#define __LATERALSQUARE_H__
#include "square.h"

class LateralSquare : public Square  {
  public :
	// This is the one-three argument constructor for the LateralSquare class, where 
  	//		the value for locked, is defaulted to false, and the value for
  	//		type is defaulted to 'h'.
	LateralSquare( char colour, bool locked = false, char type = 'h');
	// This is the default destructor for the lateral square.
	~LateralSquare( );
	// This method is used to return all the Squares that need to be resolved alongside
	//		the lateral Square.
	std::vector<Square *> clearSquare( );
	// This method is used to draw the unique lateral Square
	void draw();
};

#endif