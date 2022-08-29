#include <string>
#include <sstream>

#include "gwindow.h"

#include "tttgamedata.h"
#include "tttgame.h"
#include "tttgameai.h"

// Keeps track of who's move it is
enum UiState {
	XMove,
	OMove
};

// Function: drawBoard
// Purpose: Generates a string to display to the terminal
//		that depicts the current game state
// Input: A game state representing a game board
// Returns: A string ready to display to the GTerminal
std::string drawBoard(const GameState& gb)
{
	std::ostringstream finalOut;
	std::string indent = "\t   ";

	// Make some space above the board
	for (int i = 0; i < 5; i++)
	{
		finalOut << "\n";
	}


	for (int i = 0; i < 3; i++)
	{
		// Indent each row
		finalOut << indent;
		for (int j = 0; j < 3; j++)
		{
			// Draw square
			switch (gb.mBoard[i][j])
			{
			case GameState::Empty:
				// The square is empty, display the number
				finalOut << " " << i * 3 + j + 1 << " ";
				break;
			case GameState::X:
				finalOut << " X ";
				break;
			case GameState::O:
				finalOut << " O ";
				break;
			}

			// Draw column dividers
			if (j == 0 || j == 1)
			{
				finalOut << "|";
			}
			else
			{
				finalOut << "\n";
			}
		}

		// Draw row dividers
		if (i == 0 || i == 1)
		{
			finalOut << indent << "-----------\n";
		}
		else
		{
			finalOut << "\n\n";
		}
	}

	return finalOut.str();
}

int main(int argc, const char* argv[])
{
	// Wait time might need to be changed later
	unsigned waitTime = 100;
	GTerminal term(400, 400);
	term.showCursor(false);

	TicTacToeGame tttg;

	int choice = 1;
	UiState whosMove = XMove;

	while (true)
	{
		unsigned short moveSquare = 0;

		// Empty the screen
		term.clear();

		// Draw the board
		std::stringstream screen;
		screen << drawBoard(tttg.getBoard());

		// Check for winner
		if (tttg.getWinner() == 'X')
		{
			// X wins!
			screen << "\n\n___________________________________\n";
			screen << "!!!!!!!!!!!!! X WINS !!!!!!!!!!!!!\n\n\n";
			term.appendText(screen.str());
			pause(waitTime * 10);
			return 0;
		}
		else if (tttg.getWinner() == 'O')
		{
			// O wins
			screen << "\n\n___________________________________\n";
			screen << "!!!!!!!!!!!!! O WINS !!!!!!!!!!!!!\n\n\n";
			term.appendText(screen.str());
			pause(waitTime * 10);
			return 0;
		}
		else if (tttg.getWinner() == 'N')
		{
			screen << "\n\n___________________________________\n";
			screen << "!!!!!!!!!!!! TIE GAME !!!!!!!!!!!!\n\n\n";
			term.appendText(screen.str());
			pause(waitTime * 10);
			return 0;
		}

		screen << "\n\n___________________________________\n";

		// Get the key press from the terminal
		while (term.hasEvents())
		{
			GEvent e = term.getEvent();
			if (e.Type == EventType::KeyDown)
			{
				int key = e.Event.Key.Code;

				// 0 quits the game
				if (key == '0')
				{
					return 0;
				}
				// Calculate the number pressed
				if (key >= '1' && key <= '9')
				{
					moveSquare = key - '0';
				}
				// Ignore everything else
			}
		}

		
		if (whosMove == XMove)
		{
			// Wait for the user to pick an option
			screen << "X's move... ";
		}
		else
		{
			// Let the AI pick an option
			moveSquare = pickMove(tttg.getBoard());
			screen << "O's move... ";
		}

		if (moveSquare != 0)
		{
			// Display the player's choice
			screen << moveSquare;
		}

		// Display the player's choice
		screen << std::endl;
		term.appendText(screen.str());

		pause(waitTime);

		if (moveSquare != 0)
		{
			if (whosMove == XMove)
			{
				// Assign X's move
				if (tttg.setSquareState(moveSquare, GameState::X))
				{
					whosMove = OMove;
				}
			}
			else
			{
				// Assign O's move
				if (tttg.setSquareState(moveSquare, GameState::O))
				{
					whosMove = XMove;
				}
			}
		}
	}

	// Pause for a bit before the game ends
	pause(2 * waitTime);
	return 0;
}
