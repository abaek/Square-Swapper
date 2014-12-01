// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============  *** Implementation of LateralSquare class ***   ===============
// ===============                                                  ===============
// ================================================================================

#include <vector>
#include <cstdlib>
#include "lateralsquare.h"
#include "board.h"

using namespace std;

// This is the default constructor for the lateral square.
LateralSquare::LateralSquare( char colour, bool locked, char type) : 
											Square(colour, locked, type) {}

// This is the default destructor for the lateral square.
LateralSquare::~LateralSquare( ) { }

// This method is used to return all the Squares that need to be resolved alongside
//		the lateral Square.
vector<Square *> LateralSquare::clearSquare( ) {
	vector<Square *> v;
	// This for loop is used to find all the squares on the board that are in the
	//		same row as the lateral square.
	int row = this->r;
	Square ***board = (this->currentBoard)->theBoard;
	// Increased power resolution, which occurs when lateral square involved in match of 5.
	if ( radius == 5 ) {
		// Randomly choose 4 other row to explode
		for ( int i = 0; i < 4; i++ ) {
			int randRow = rand( ) % 10;
			for ( int col = 0; col < (this->currentBoard)->boardSize; col++ ) {
				if ( board[randRow][col]->getType( ) != 'l' ) {
					v.push_back(board[randRow][col]);
				}
			}
		}
	// Easter egg resolution, which occurs when lateral square involved in match of 6+
	} else if ( radius == 6 ) {
		// Randomly choose 10 other rows to explode
		for ( int i = 0; i < 10; i++ ) {
			int randRow = rand( ) % 10;
			for ( int col = 0; col < (this->currentBoard)->boardSize; col++ ) {
				if ( board[randRow][col]->getType( ) != 'l' ) {
					v.push_back(board[randRow][col]);
				}
			}
		}
	}
	// Resolve the lateral square like normal.
	for ( int col = 0; col < (this->currentBoard)->boardSize; col++ ) {
		if ( board[row][col]->getType( ) != 'l' ) {
			v.push_back(board[row][col]);
		}
	}
	return v;
}

// This method is used to draw the unique lateral Square
void LateralSquare::draw() {
	Square::draw();
    int colourNum = 5; // Yellow
    int graphicalWidth = currentBoard->windowSize;
    int boardSize = currentBoard->boardSize;
    int width = graphicalWidth/boardSize - 6;
    int height = (graphicalWidth/boardSize - 6) / 3; // Horiztonal stripe
    int posX = (graphicalWidth/boardSize) * c + 3;
    int posY = (graphicalWidth/boardSize) * r + ( height ) + 3;
    window->fillRectangle(posX, posY, width, height, colourNum);
}



