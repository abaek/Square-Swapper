// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============  *** Implementation of UnstableSquare class ***  ===============
// ===============                                                  ===============
// ================================================================================

#include <vector>
#include "unstablesquare.h"
#include "board.h"

using namespace std;

// This is the default constructor for the unstable square.
UnstableSquare::UnstableSquare( char colour, bool locked, char type) : 
												Square(colour, locked, type) {}

// This is the default destructor for the upright square.
UnstableSquare::~UnstableSquare( ) { }

// This method is used to return all the Squares that need to be resolved alongside
//		the unstable Square.
std::vector<Square *> UnstableSquare::clearSquare( ) {
	vector<Square *> v;
	// This while loop is to find all the squares surrounding the unstable square.
	Square ***board = (this->currentBoard)->theBoard;
	int boardSize = (this->currentBoard)->boardSize - 1; //9

	// The bomb should blow up in a heart shape. (Mini heart bomb)
	//      0   1   2   3   4   5   6   7   8   9
	//  0  ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
	//  1  ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
	//  2  ___ ___ ___ ___ xxx ___ xxx ___ ___ ___
	//  3  ___ ___ ___ xxx xxx xxx xxx xxx ___ ___
	//  4  ___ ___ ___ xxx xxx BOM xxx xxx ___ ___
	//  5  ___ ___ ___ ___ xxx xxx xxx ___ ___ ___
	//  6  ___ ___ ___ ___ ___ xxx ___ ___ ___ ___
	//  7  ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
	//  8  ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
	//  9  ___ ___ ___ ___ ___ ___ ___ ___ ___ ___

	if ( radius == 5 ) {

		// The following code is used for the mini heart bomb!
		int row = this->r;
		int col = this->c;
		// These variables are used to set up the area in which the bomb should blow.
		int leftwidth = this->c;
		int rightwidth = boardSize - this->c;
		int topwidth = this->r;
		int bottomwidth = boardSize - this->r;
		if ( leftwidth > 2 ) {
			leftwidth = 2;
		}
		if ( rightwidth > 2 ) {
			rightwidth = 2;
		}
		if ( topwidth > 2 ) {
			topwidth = 2;
		}
		if ( bottomwidth > 2 ) {
			bottomwidth = 2;
		}
		// Now it is time to resolve the explosion.
		// Check the row two rows above the bomb.
		if ( ( topwidth >= 2 ) && ( leftwidth >= 1 ) ) {
			if ( board[row-2][col-1]->getType( ) != 'l' ) {
				v.push_back(board[row-2][col-1]);
			}
		}
		if ( ( topwidth >= 2 ) && ( rightwidth >= 1) ) {
			if ( board[row-2][col+1]->getType( ) != 'l' ) {
				v.push_back(board[row-2][col+1]);
			}
		}
		// Check the row above the bomb.
		if ( topwidth >= 1 ) {
			for ( int i = (col - leftwidth); i <= (col + rightwidth); i++ ) {
					if ( board[row-1][i]->getType( ) != 'l' ) {
						v.push_back(board[row-1][i]);
					}
			}
		}
		// Check the row with the bomb.
		for ( int i = (col - leftwidth); i <= (col + rightwidth); i++ ) {
			if ( board[row][i]->getType( ) != 'l' ) {
				v.push_back(board[row][i]);
			}
		}
		// Check the row under the bomb
		if ( bottomwidth >= 1 ) {
			int left = leftwidth;
			if ( leftwidth > 1 ) {
				left = 1;
			}
			int right = rightwidth;
			if ( rightwidth > 1 ) {
				right = 1;
			}
			for ( int i = (this->c - left); i <= (this->c + right); i++ ) {
				if ( board[row+1][i]->getType( ) != 'l' ) {
					v.push_back(board[row+1][i]);
				}
			}
		}
		// Check the row two rows under the bomb
		if ( bottomwidth == 2 ) {
			if ( board[row+2][col]->getType( ) != 'l' ) {
				v.push_back(board[row+2][col]);
			}
		}

	// The bomb should blow up in a heart shape. (Heart bomb)
	//      0   1   2   3   4   5   6   7   8   9
	//  0  ___ ___ ___ ___ ___ ___ ___ ___ ___ ___
	//  1  ___ ___ ___ xxx ___ ___ ___ xxx ___ ___
	//  2  ___ ___ xxx xxx xxx ___ xxx xxx xxx ___
	//  3  ___ xxx xxx xxx xxx xxx xxx xxx xxx xxx
	//  4  ___ xxx xxx xxx xxx xxx xxx xxx xxx xxx
	//  5  ___ xxx xxx xxx xxx BOM xxx xxx xxx xxx
	//  6  ___ ___ xxx xxx xxx xxx xxx xxx xxx ___
	//  7  ___ ___ ___ xxx xxx xxx xxx xxx ___ ___
	//  8  ___ ___ ___ ___ xxx xxx xxx ___ ___ ___
	//  9  ___ ___ ___ ___ ___ xxx ___ ___ ___ ___
	} else if ( radius == 6 ) {
		// The following code is used for the heart bomb!
		int row = this->r;
		int col = this->c;
		// These variables are used to set up the area in which the bomb should blow.
		int leftwidth = this->c;
		int rightwidth = boardSize - this->c;
		int topwidth = this->r;
		int bottomwidth = boardSize - this->r;
		if ( leftwidth > 4 ) {
			leftwidth = 4;
		}
		if ( rightwidth > 4 ) {
		 	rightwidth = 4;
		}
		if ( topwidth > 4 ) {
			topwidth = 4;
		}
		if ( bottomwidth > 4 ) {
			bottomwidth = 4;
		}
		// Now it is time to resolve the explosion.
		// Check the row four rows above the bomb.
		if ( ( topwidth == 4 ) && ( leftwidth >= 2 ) ) {
			if ( board[row-4][col-2]->getType( ) != 'l' ) {
				v.push_back(board[row-4][col-2]);
			}
		}
		if ( ( topwidth == 4 ) && ( rightwidth >= 2) ) {
			if ( board[row-4][col+2]->getType( ) != 'l' ) {
				v.push_back(board[row-4][col+2]);
		 	}
		}
		// Check the row three rows above the bomb.
		if ( topwidth >= 3 ) {
		 	int left = leftwidth;
		 	if ( leftwidth > 3 ) {
		 		left = 3;
		 	}
		 	int right = rightwidth;
		 	if ( rightwidth > 3 ) {
		 		right = 3;
		 	}
		 	for ( int i = (this->c - left); i <= (this->c + right); i++ ) {
				if ( board[row-3][i]->getType( ) != 'l' ) {
					v.push_back(board[row-3][i]);
				}
			}
		}
		// Check the row two rows above the bomb
		if ( topwidth >= 2 ) {
		 	for ( int i = (this->c - leftwidth); i <= (this->c + rightwidth); i++ ) {
		 		if ( board[row-2][i]->getType( ) != 'l' ) {
		 			v.push_back(board[row-2][i]);
		 		}
		 	}
		}
		// Check the row above the bomb
		if ( topwidth >= 1 ) {
		 	for ( int i = (this->c - leftwidth); i <= (this->c + rightwidth); i++ ) {
		 		if ( board[row-1][i]->getType( ) != 'l' ) {
		 			v.push_back(board[row-1][i]);
		 		}
		 	}
		}
		// Check the row with the bomb.
		for ( int i = (this->c - leftwidth); i <= (this->c + rightwidth); i++ ) {
		 		if ( board[row][i]->getType( ) != 'l' ) {
		 			v.push_back(board[row][i]);
		 		}
		}
		// Check the row under the bomb
		if ( bottomwidth >= 1 ) {
		 	int left = leftwidth;
		 	if ( leftwidth > 3 ) {
		 		left = 3;
		 	}
		 	int right = rightwidth;
			if ( rightwidth > 3 ) {
		 		right = 3;
		 	}
		 	for ( int i = (this->c - left); i <= (this->c + right); i++ ) {
		 		if ( board[row+1][i]->getType( ) != 'l' ) {
		 			v.push_back(board[row+1][i]);
		 		}
		 	}
		}
		// Check the row two rows under the bomb
		if ( bottomwidth >= 2 ) {
			int left = leftwidth;
		 	if ( leftwidth > 2 ) {
		 		left = 2;
		 	}
		 	int right = rightwidth;
		 	if ( rightwidth > 2 ) {
		 		right = 2;
		 	}
		 	for ( int i = (this->c - left); i <= (this->c + right); i++ ) {
		 		if ( board[row+2][i]->getType( ) != 'l' ) {
		 			v.push_back(board[row+2][i]);
		 		}
		 	}
		}
		// Check the row three rows under the bomb
		if ( bottomwidth >= 3 ) {
		 	int left = leftwidth;
		 	if ( leftwidth > 1 ) {
		 		left = 1;
		 	}
		 	int right = rightwidth;
			if ( rightwidth > 1 ) {
				right = 1;
			}
			for ( int i = (this->c - left); i <= (this->c + right); i++ ) {
				if ( board[row+3][i]->getType( ) != 'l' ) {
					v.push_back(board[row+3][i]);
				}
			}
		}
		
		// Check the row four rows under the bomb
		if ( bottomwidth == 4 ) {
		 	if ( board[row+4][col]->getType( ) != 'l' ) {
		 		v.push_back(board[row+4][col]);
			}
		}

	} else {
		// Need to check edge cases on location of unstable square.
		int leftedge = ((this->c) - (radius / 2));
		int rightedge = ((this->c) + (radius / 2));
		int topedge = ((this->r) - (radius / 2));
		int bottomedge = ((this->r) + (radius / 2));
		if ( radius == 3 ) {
			if ( this->c == 0 ) {
				leftedge = this->c;
			} else if ( this->c == boardSize) {
				rightedge = boardSize;
			}
			if ( this->r == 0 ) {
				topedge = 0;
			} else if ( this->r == boardSize) {
				bottomedge = boardSize;
			}
		} else if ( radius == 4 ) {
			if ( this->c <= 1 ) {
				leftedge = 0;
			} else if ( (this->c + 1) >= boardSize) {
				rightedge = boardSize;
			} 
			if ( this->r <= 1 ) {
				topedge = 0;
			} else if ( (this->r + 1) >= boardSize) {
				bottomedge = boardSize;
			}
		}

		for ( int row = topedge; row <= bottomedge; row++ ) {
			for ( int col = leftedge; col <= rightedge; col++ ) {
				if ( board[row][col]->getType( ) != 'l' ) {
					v.push_back(board[row][col]);
				}
			}
		}
	}
	return v;
}

// This method is used to draw the unique unstable Square
void UnstableSquare::draw() {
	Square::draw();
    int colourNum = 5; // Yellow
    int graphicalWidth = currentBoard->windowSize;
    int boardSize = currentBoard->boardSize;
    int width = (graphicalWidth/boardSize - 2) / 3;
    int height = (graphicalWidth/boardSize - 2) / 3;
    int posX = (graphicalWidth/boardSize) * c + ( width ) + 1;
    int posY = (graphicalWidth/boardSize) * r + ( height ) + 1;
    window->fillRectangle(posX, posY, width, height, colourNum);

    colourNum = colour - '0'; // Current colour
    width = (graphicalWidth/boardSize - 2) / 5;
    height = (graphicalWidth/boardSize - 2) / 5;
    posX = (graphicalWidth/boardSize) * c + ( width * 2 ) + 5;
    posY = (graphicalWidth/boardSize) * r + ( height * 2 ) + 5;
    window->fillRectangle(posX, posY, width, height, colourNum);
}
