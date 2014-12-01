// ================================================================================
// ===============                                                  ===============
// ===============                Square Swapper 5000               ===============
// ===============              Andy Baek & William Lam             ===============
// ===============         *** Implementation of main.cc ***        ===============
// ===============                                                  ===============
// ================================================================================

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <ncurses.h>

#include "player.h"
#include "board.h"
#include "level.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "window.h"
#include "square.h"
#include "basicsquare.h"
#include "lateralsquare.h"
#include "uprightsquare.h"
#include "unstablesquare.h"
#include "psychedelicsquare.h"

using namespace std;

// Used for using keyboard
bool curses_started = false;

void endCurses() {
  if (curses_started && !isendwin())
     endwin();
}


void startCurses() {
  if (curses_started) {
     refresh();
  }
  else {
     initscr();
     cbreak();
     noecho();
     intrflush(stdscr, false);
     keypad(stdscr, true);
     atexit(endCurses);
     curses_started = true;
  }
}

int main (int argc, char *argv[]) {

	// The default commands in the game
	string swap = "swap";
	string hint = "hint";
	string scramble = "scramble";
	string levelup = "levelup";
	string leveldown = "leveldown";
	string restart = "restart";
	string keyboard = "keyboard";
	string help = "help";
	string renam = "rename";

	bool bonusOn = false;
	bool graphical = true;
	Player *user = new Player( );

	// Inside the user class, there should be a method that is called to initialize
	// the board based on whether the board is initialized from a file or by
	// random generator.
	
	// This if statement initiates if the program has started with some option.	
	if ( argc > 1 ) {
		vector<string> all_args;
		// Find all options passed into the program.
		for ( int i = 0; i < argc; i++ ) {
			all_args.push_back(argv[i]);
		}
		// Execute the appropriate command for each option passed in.
		for ( int i = 0; i < argc; i++ ) {
			string arg = all_args[i];
			// This command line option is to declare that the game is to be played with only the
			//		text display.
			if ( arg == "-text" ) {	
				graphical = false;
				user->setGraphical(false);
				cout << "Starting text only version" << endl;
			// This command line option is to declare that the game is to be played with all bonus
			//		features turned off.
			} else if ( arg == "-bonus" ) {
				user->setBonus(true);
				bonusOn = true;
				cout << "Bonus features turned on :D" << endl;
			// This command line option sets the seed for the randomized aspect of the board.
			} else if ( arg == "-seed" ) {
				int n;
				istringstream ss(all_args[++i]);
				ss >> n;
				user->setSeed(n);
				cout << "Using seed: " << n << endl;
			// This command line option tells the program that the board is to be initialized
			//		from the given file.
			} else if ( arg == "-scriptfile" ) {
				string fileName = all_args[++i];
				cout << "Using file: " << fileName << endl;
				user->setConfigFile(fileName);
			// This command line option that starts the game on a particular level.	
			} else if ( arg == "-startlevel" ) {
				int n;
				istringstream ss(all_args[++i]);
				ss >> n;
				cout << "Starting level " << n << endl;
				user->setLevel(n);
			// This command line option is to provide usage information for the game, and immediately terminate.
			} else if ( arg == "-help" ) {
				cout << "---------------------------------------------------" << endl;
				cout << "Usage:		" << all_args[0] << " [-option] [argument]" << endl;
				cout << "Options:	" << "-text 		 runs the program in text-only mode." << endl;
				cout << "			" << "-nobonus		 runs the program with no bonus features." << endl;
				cout << "			" << "-seed xxx 	 sets the randum number generator's seed to xxx." << endl;
				cout << "			" << "-scripfile xxx uses xxx for this level's initial board configuration." << endl;
				cout << "			" << "-startlevel x  starts the game on level n." << endl;
				cout << "Example: 	" << all_args[0] << "-scriptfile checkLockedCells -startlevel 2" << endl;
				cout << "Should start the game at level 2 and read in the initial " << endl;
				cout << "configuration of the board from the file checkLockedCells." << endl;
				cout << "---------------------------------------------------" << endl;
				return 0;
			} 
		}
	}

	// Introduction to the game
	cout << "*******************************" << endl;
	cout << "Welcome to Square Swapper 5000!" << endl;
	cout << "-------------------------------" << endl;
	cout << "Please enter your username: " << endl;
	string name;
	cin >> name;
	user->name = name;
	cout << "Have fun " << user->name << "!" << endl;
	cout << "-------------------------------" << endl;
	cout << "For a list of commands, input help at anytime." << endl;
	cout << "-------------------------------" << endl;

	// Create the board based on configuration of the player.
	user->restart( );

	// See the board once the game begins.
	user->printBoard( );
	// Now it is time to start playing the game.
	string str;
	string cmd;
	while (getline (cin, str)) {
		istringstream ss(str);
		ss >> cmd;
		// This if statement is used for the rename command which is going to change the command
		//		name used to play the game.
		if ( cmd == renam ) {
			string cmdName;
			string newName;
			ss >> cmdName >> newName;
			if ( cmdName == swap ) {
				swap = newName;
			} else if ( cmdName == hint ) {
				hint = newName;
			} else if ( cmdName == scramble ) {
				scramble = newName;
			} else if ( cmdName == levelup ) {
				levelup = newName;
			} else if ( cmdName == leveldown ) {
				leveldown = newName;
			} else if ( cmdName == restart ) {
				restart = newName;
			} else if ( cmdName == keyboard ) {
				keyboard = newName;
			} else if ( cmdName == help ) {
				help = newName;
			} else if ( cmdName == renam ) {
				renam = newName;
			}
		// This if statement is for the swap command. Given by "swap x y z", this command
		//		swaps the square at the (x,y) co-ordinate with the square in the z direction
		//		 (0 for north, 1 for south, 2 for west, and 3 for east).
		} else if ( cmd == swap ) {
			int x, y, direction;
			ss >> x >> y >> direction;		
			user->swap(x, y, direction);

			user->printBoard( );
		// This if statement is for the hint command, which cout's a valid move (x,y,z)
		//		that would lead to a match.
		} else if ( cmd == hint ) {
			user->hint( );
			user->printBoard( );
		// This if statement is for the scramble command, that is only available if no moves
		//		are possible, and this command reshuffles the squares on the board.
		} else if ( cmd == scramble ) {
			bool valid = true;
			// This if statement is to ensure that the board has no more valid moves prior
			//		to the scramble command being called.
			valid = user->validScramble( );
			if ( valid ) {
				user->scramble( );
				user->printGraphical();
				user->printBoard( );
			} else {
				cout << "Not a valid scramble situation" << endl;
			}
		// This if statement is for the levelup command, which increase the difficulty level 
		//		of the game by one. If there is no higher level, the command has no effect.
		} else if ( cmd == levelup ) {
			user->levelUp();
			user->restart( );
			user->printBoard( );
		// This if statement is for the leveldown command, which decreases the difficulty level
		//		of the game by one. If there is no lower level, the command has no effect.
		} else if ( cmd == leveldown ) {
			user->levelDown();
			user->restart( );
			user->printBoard( );
		// This if statement is for the restart command, which clears the board and starts a
		//		new game at the same level.
		} else if ( cmd == restart ) {
			user->restart( );
			user->printBoard( );
		} else if ( cmd == help ) {
			cout << "------------------------------------------------------------------------" << endl;
			cout << "Commands: (without brackets)" << endl;
			cout << "- [swap x y z] swaps thesquare at the (x,y) co-ordinate with the square " << endl;
			cout << "  in the z direction (0 for north, 1 for south, 2 for west, 3 for east)." << endl;
			cout << "- [hint] returns a valid move (x, y, z) that would lead to a match." << endl;
			cout << "- [scramble] is available only if no moves are possible, and will " << endl;
			cout <<	"  reshuffle the squares on the board." << endl;
			cout << "- [levelup] increases the difficulty level of the game by one." << endl;
			cout << "- [leveldown] decreases the difficultly level of the game by one." << endl;
			cout << "- [restart] clears the board and starts a new game at the same level." << endl;
			cout << "- [keyboard] initiates the keyboard control scheme for the graphical display." << endl;
			cout << "------------------------------------------------------------------------" << endl;
		} else if (cmd == keyboard && bonusOn ) {
			if ( graphical ) {
				cout << "Move around with arrow keys" << endl;
				cout << "Press space then a direction to swap" << endl;
				cout << "Press q to quit keyboard mode" << endl;
				bool lastSpace = false;
				startCurses();
				int x = 0;
				int y = 0;
				user->drawBorder(7, x, y);
				while (true) {
					int key = getch();
					// Quit
					if (key == 113) {
						break;
					}
					// Space
					else if (key == 32) {
						lastSpace = true;
					}
					// Swap
					else if (lastSpace) {
						// Up
						if (key == 259) {
							user->swap(x, y, 0);
							user->printBoard( );
							lastSpace = false;
						} 
						// Down
						else if (key == 258) {
							user->swap(x, y, 1);
							user->printBoard( );
							lastSpace = false;
						}
						// Left
						else if (key == 260) {
							user->swap(x, y, 2);
							user->printBoard( );
							lastSpace = false;
						}
						// Right
						else if (key == 261) {
							user->swap(x, y, 3);
							user->printBoard( );
							lastSpace = false;
						}
						// Space (cancel)
						else if (key == 32) {
							lastSpace = false;
						}
					}
					// Move around
					else {
						int newX = x;
						int newY = y;
						// Up
						if (key == 259) {
							newX--;
						} 
						// Down
						else if (key == 258) {
							newX++;
						}
						// Left
						else if (key == 260) {
							newY--;
						}
						// Right
						else if (key == 261) {
							newY++;
						}
						// If not towards edge
						if (!(newX < 0 || newX > 9 || newY < 0 || newY > 9)) {
							// Remove old border
							user->drawBorder(4, x, y); // 4 = black
							// Add new border
							x = newX;
							y = newY;
							user->drawBorder(7, x, y);// 7 = yellow

						}
					}
				}
				endCurses();
			} else {
				cout << "Cannot enter keyboard mode without graphical" << endl;
			}
			
		}

	}

	// The game has now ended, and all memory needs to be freed.
	delete user;

}
