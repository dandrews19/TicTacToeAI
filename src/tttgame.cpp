#include "tttgame.h"
#include "tttgameai.h"

TicTacToeGame::TicTacToeGame()
{
    // creating a new gamestate with default consturctor
    currentState = GameState();
}


GameState TicTacToeGame::getBoard() const
{
	// returniong the board
    return currentState;
}


bool TicTacToeGame::setSquareState(unsigned short row, unsigned short col, GameState::SquareState state)
{
	
    // if out of bounds, return false
    if (row > 2 or row < 0) {
        return false;
    }
    if (col < 0 or col > 2) {
        return false;
    }
    
    // if board at row and column is empty
    // update board and return true
    if (currentState.mBoard[row][col] == GameState::Empty) {
        
        currentState.mBoard[row][col] = state;
        return true;
        
    }
    // else return false
	return false;
}

bool TicTacToeGame::setSquareState(unsigned short square, GameState::SquareState state)
{
    // if out of bounds, return false
    if (square < 1 or square > 9) {
        return false;
    }
    
    // otherwise, convert the square to rows and columns and check it with other setSquareState function
    
    if (square >= 7) {
        return setSquareState(2, square - 7, state);
    }
    else if (square >= 4) {
        return setSquareState(1, square - 4, state);
    }
    else {
        return setSquareState(0, square - 1, state);
    }
	
}

bool TicTacToeGame::checkFull() {
    
    // checking if each spot is empty, returning false if empty spot is found
    for (int i = 0; i < 3; i++) {
        for (int c = 0; c < 3; c++){
            
            if (currentState.mBoard[i][c] == GameState::Empty) {
                return false;
            }
        }
    }
    
    return true;
}

char TicTacToeGame::getWinner()
{
    char outcome = ' ';
    // check diagonals
    GameState::SquareState diag1 = currentState.mBoard[0][0];
    
    if (diag1 == currentState.mBoard[1][1] and diag1 == currentState.mBoard[2][2] and diag1 != GameState::Empty) {
        outcome = diag1;
    }
    
    GameState::SquareState diag2 = currentState.mBoard[0][2];
    
    if (diag2 == currentState.mBoard[1][1] and diag2 == currentState.mBoard[2][0] and diag2 != GameState::Empty) {
        outcome = diag2;
    }
    
    // check rows
    GameState::SquareState row1 = currentState.mBoard[0][0];
    if (row1 == currentState.mBoard[0][1] and row1 == currentState.mBoard[0][2] and row1 != GameState::Empty) {
        outcome = row1;
    }
    
    GameState::SquareState row2 = currentState.mBoard[1][0];
    if (row2 == currentState.mBoard[1][1] and row2 == currentState.mBoard[1][2] and row2 != GameState::Empty) {
        outcome = row2;
    }
    
    GameState::SquareState row3 = currentState.mBoard[2][0];
    if (row3 == currentState.mBoard[2][1] and row3 == currentState.mBoard[2][2] and row3 != GameState::Empty) {
        outcome = row3;
    }
    
    
    // check columns
    GameState::SquareState col1 = currentState.mBoard[0][0];
    if (col1 == currentState.mBoard[1][0] and col1 == currentState.mBoard[2][0] and col1 != GameState::Empty) {
        outcome = col1;
    }
    
    GameState::SquareState col2 = currentState.mBoard[0][1];
    if (col2 == currentState.mBoard[1][1] and col2 == currentState.mBoard[2][1] and col2 != GameState::Empty) {
        outcome = col2;
    }
    
    GameState::SquareState col3 = currentState.mBoard[0][2];
    if (col3 == currentState.mBoard[1][2] and col3 == currentState.mBoard[2][2] and col3 != GameState::Empty) {
        outcome = col3;
    }
    
    // checking if board is full for tie
    if (outcome == ' ' and checkFull()) {
        outcome = 'N';
    }
	// returning the outcome
	return outcome;	
}

