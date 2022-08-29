#pragma once

struct GameState
{
	// state of each square in game
	enum SquareState { Empty, X = 'X', O = 'O' };
	// Grid of spaces
	SquareState mBoard[3][3];
};
