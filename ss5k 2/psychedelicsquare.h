// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============    *** Header of PsychedelicSquare class ***     ===============
// ===============                                                  ===============
// ================================================================================

#ifndef __PHSYCHEDELICSQUARE_H__
#define __PHSYCHEDELICSQUARE_H__
#include "square.h"

class PsychedelicSquare : public Square  {
  public :
	// This is the one-three argument constructor for the PsychedelicSquare class, where 
  	//		the value for locked, is defaulted to false, and the value for
  	//		type is defaulted to 'p'.
	PsychedelicSquare( char colour, bool locked = false, char type = 'p');
	// This is the default destructor for the Psychedelic square.
	~PsychedelicSquare( );
	// This method is used to return all the Squares that need to be resolved alongside
	//		the psychedelic Square.
	std::vector<Square *> clearSquare( );
	// This method is used to draw the unique psychedelic Square
	void draw();
};

#endif