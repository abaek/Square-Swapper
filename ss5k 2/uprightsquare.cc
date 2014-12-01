// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============  *** Implementation of UprightSquare class ***   ===============
// ===============                                                  ===============
// ================================================================================

#include <vector>
#include <cstdlib>
#include "uprightsquare.h"
#include "board.h"

using namespace std;

// This is the default constructor for the upright square.
UprightSquare::UprightSquare( char colour, bool locked, char type) : 
															Square(colour, locked, type) {}

// This is the default destructor for the upright square.
UprightSquare::~UprightSquare( ) { }

// This method is used to return all the Squares that need to be resolved alongside
//		the upright Square.
vector<Square *> UprightSquare::clearSquare( ) {
	vector<Square *> v;
	// This for loop is used to find all the squares on the board that are in the
	//		same column as the upright square.
	int col = this->c;
	Square ***board = (this->currentBoard)->theBoard;
	// Increased power resolution, which occurs when upright square involved in match of 5.
	if ( radius == 5 ) {
		// Randomly choose 4 other columns to explode
		for ( int i = 0; i < 4; i++ ) {
			int randCol = rand( ) % 10;
			for ( int row = 0; row < (this->currentBoard)->boardSize; row++ ) {
				if ( board[row][randCol]->getType( ) != 'l' ) {
					v.push_back(board[row][randCol]);
				}
			}
		}
	// Easter egg resolution, which occurs when upright square involved in match of 6+.
	} else if ( radius == 6 ) {
		// Randomly choose 10 other columns to explode
		for ( int i = 0; i < 10; i++ ) {
			int randCol = rand( ) % 10;
			for ( int row = 0; row < (this->currentBoard)->boardSize; row++ ) {
				if ( board[row][randCol]->getType( ) != 'l' ) {
					v.push_back(board[row][randCol]);
				}
			}
		}
	}
	// Resolve the lateral square like normal, that is, all squares in the same row.
	for ( int row = 0; row < (this->currentBoard)->boardSize; row++ ) {
		if ( board[row][col]->getType( ) != 'l' ) {
			v.push_back(board[row][col]);
		}
	}
	return v;
}

// This method is used to draw the unique upright Square
void UprightSquare::draw() {
	Square::draw();
    int colourNum = 5; // Yellow
    int graphicalWidth = currentBoard->windowSize;
    int boardSize = currentBoard->boardSize;
    int width = (graphicalWidth/boardSize - 6) / 3;
    int height = graphicalWidth/boardSize - 6; // Horiztonal stripe
    int posX = (graphicalWidth/boardSize) * c + (width) + 3;
    int posY = (graphicalWidth/boardSize) * r + 3;
    window->fillRectangle(posX, posY, width, height, colourNum);
}