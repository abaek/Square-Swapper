// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============    *** Implementation of TBombSquare class ***   ===============
// ===============                                                  ===============
// ================================================================================

#include <vector>
#include "tbombsquare.h"
#include "board.h"

using namespace std;

// This is the default constructor for the TBomb square.
TBombSquare::TBombSquare( char colour, bool locked, char type) : 
															Square(colour, locked, type) {}

// This is the default destructor for the TBomb square.
TBombSquare::~TBombSquare( ) { }

// This method is used to return all the Squares that need to be resolved alongside
//		the TBomb Square.
vector<Square *> TBombSquare::clearSquare( ) {
	vector<Square *> v;
	// This for loop is used to find all the squares on the board that are in the
	//		same column as the TBomb square.
	int thisCol = this->c;
	int thisRow = this->r;
	Square ***board = (this->currentBoard)->theBoard;
	int boardSize = (this->currentBoard)->boardSize - 1;
	// Increased power resolution, which occurs when TBomb square involved in match of 5.
	if ( radius == 5 ) {
		bool left = false;
		bool right = false;
		bool top = false;
		bool bottom = false;
		if ( this->c > 0 ) {
			left = true;
		}
		if ( (boardSize - this->c) > 0 ) {
			right = true;
		}
		if ( this->r > 0 ) {
			top = true;
		}
		if ( (boardSize - this->r) > 0 ) {
			bottom = true;
		}
		for ( int row = 0; row < (this->currentBoard)->boardSize; row++ ) {
			if ( row == thisRow ) {
				if ( top ) {
					for ( int col = 0; col < (this->currentBoard)->boardSize; col++ ) {
						if ( board[row-1][col]->getType( ) != 'l' ) {
							v.push_back(board[row-1][col]);
						}
					}
				}
				if ( bottom ) {
					for ( int col = 0; col < (this->currentBoard)->boardSize; col++ ) {
						if ( board[row+1][col]->getType( ) != 'l' ) {
							v.push_back(board[row+1][col]);
						}
					}
				}
				for ( int col = 0; col < (this->currentBoard)->boardSize; col++ ) {
					if ( board[row][col]->getType( ) != 'l' ) {
						v.push_back(board[row][col]);
					}
				}
			} else {
				if ( left ) {
					if ( board[row][thisCol-1]->getType( ) != 'l' ) {
						v.push_back(board[row][thisCol-1]);
					}
				}
				if ( right ) {
					if ( board[row][thisCol+1]->getType( ) != 'l' ) {
						v.push_back(board[row][thisCol+1]);
					}
				}
				if ( board[row][thisCol-1]->getType( ) != 'l' ) {
					v.push_back(board[row][thisCol-1]);
				}
			}
		}
	// Easter egg resolution, which occurs when tbombsquare involved in match of 6+.
	} else if ( radius == 6 ) {
		// Blow up two layers on the border.
		for ( int row = 0; row < (this->currentBoard)->boardSize; row++ ) {
			if ( ( row == thisRow ) || ( row == 0 ) || ( row == 1 ) || ( row == boardSize ) || ( row == (boardSize - 1) ) ){
				for ( int col = 0; col < (this->currentBoard)->boardSize; col++ ) {
					if ( board[row][col]->getType( ) != 'l' ) {
						v.push_back(board[row][col]);
					}
				}
			} else {
				if ( board[row][thisCol]->getType( ) != 'l' ) {
					v.push_back(board[row][thisCol]);
				}
				if ( board[row][0]->getType( ) != 'l' ) {
					v.push_back(board[row][0]);
				}
				if ( board[row][1]->getType( ) != 'l' ) {
					v.push_back(board[row][1]);
				}
				if ( board[row][boardSize]->getType( ) != 'l' ) {
					v.push_back(board[row][boardSize]);
				}
				if ( board[row][boardSize-1]->getType( ) != 'l' ) {
					v.push_back(board[row][boardSize-1]);
				}
			}
		}

	} else {
		// The square resolved in a match of 4 or less, and the tbomb explodes all squares
		//	   in the same column and row as the tbomb.
		for ( int row = 0; row < (this->currentBoard)->boardSize; row++ ) {
			if ( row == thisRow ) {
				for ( int col = 0; col < (this->currentBoard)->boardSize; col++ ) {
					if ( board[row][col]->getType( ) != 'l' ) {
						v.push_back(board[row][col]);
					}
				}
			} else if ( board[row][thisCol]->getType( ) != 'l' ) {
				v.push_back(board[row][thisCol]);
			}
		}
	}
	return v;
}

// This method is used to draw the unique tbomb Square
void TBombSquare::draw() {
	Square::draw();
    
    int colourNum = 5; // Yellow
    int graphicalWidth = currentBoard->windowSize;
    int boardSize = currentBoard->boardSize;
    
    // Horizontal stripe
    int width = graphicalWidth/boardSize - 6;
    int height = (graphicalWidth/boardSize - 6) / 3; // Horiztonal stripe
    int posX = (graphicalWidth/boardSize) * c + 3;
    int posY = (graphicalWidth/boardSize) * r + ( height ) + 3;
    window->fillRectangle(posX, posY, width, height, colourNum);

    // Vertical stripe
    width = (graphicalWidth/boardSize - 6) / 3;
    height = graphicalWidth/boardSize - 6; // Horiztonal stripe
    posX = (graphicalWidth/boardSize) * c + ( width ) + 3;
    posY = (graphicalWidth/boardSize) * r + 3;
    window->fillRectangle(posX, posY, width, height, colourNum);



}