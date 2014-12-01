// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============   *** Implementation of BasicSquare class ***    ===============
// ===============                                                  ===============
// ================================================================================

#include <vector>
#include "basicsquare.h"

using namespace std;

class Board;

// This is the default constructor for the basic square.
BasicSquare::BasicSquare( char colour, bool locked, char type) : 
											Square(colour, locked, type) {}

// This is the default destructor for the basic square.
BasicSquare::~BasicSquare( ) { }

// This method is used to return all the Squares that need to be resolved alongside
//		the Basic Square.
vector<Square *>BasicSquare::clearSquare( ) {
	vector<Square *> v;
	v.push_back(this);
	return v;
}

