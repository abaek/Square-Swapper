// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============    *** Implementation of WallSquare class ***    ===============
// ===============                                                  ===============
// ================================================================================

#include <vector>
#include "wallsquare.h"
#include "board.h"

using namespace std;

// This is the default constructor for the Wall square.
WallSquare::WallSquare( char colour, bool locked, char type) : Square(colour, locked, type) {}

// This is the default destructor for the Wall square.
WallSquare::~WallSquare( ) { }

// This method is used to return all the Squares that need to be resolved alongside
//		the Wall Square, which is always no squares.
vector<Square *>WallSquare::clearSquare( ) {
	vector<Square *> v;
	return v;
}

// This method is used to draw the unique Wall Square
void WallSquare::draw() {
	int colourNum = 4; // Black
    int graphicalWidth = currentBoard->windowSize;
    int boardSize = currentBoard->boardSize;
    int width = graphicalWidth/boardSize - 6;
    int height = graphicalWidth/boardSize - 6;
    int posX = (graphicalWidth/boardSize) * c + 3;
    int posY = (graphicalWidth/boardSize) * r + 3;
    window->fillRectangle(posX, posY, width, height, colourNum);
}