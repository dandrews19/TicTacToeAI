// You can use this for the std::min / std::max functions
#include <algorithm>
#include "tttgameai.h"
#include "tttgame.h"

bool IsGameOver(const GameState& state)
{
    float score = GetScore(state);
    int emptyCounter;
    // if GetScore returns -1 or 1, there is a winner and the game is owner
    if (score == 1.0 or score == -1.0) {
        return true;
    }
    else {
        // otherwise check for empty slots, if there are the game isn't over
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state.mBoard[i][j] == GameState::Empty) {
                    return false;
                }
            }
        }
        // if theres no empty spots, and no winner, the game is a tie and its over
        return true;
    }
}

void GenStates(GTNode* root, bool xPlayer)
{
	// initializing player turn variable
    GameState::SquareState playerTurn;
    
    // setting player turn based on parameter
    if (xPlayer) {
        playerTurn = GameState::X;
    }
    else {
        playerTurn = GameState::O;
    }
        // creating a new node whenever theres an empty spot on the board
        for (int i = 0; i < 3; i++) {
            for (int h = 0; h < 3; h++) {
                
                if (root->mState.mBoard[i][h] == GameState::Empty) {
                    // creating new node pointer
                    GTNode* newNode = new GTNode();
                    
                    newNode->mState = root->mState;
                    // assigning empty space to player turn
                    newNode ->mState.mBoard[i][h] = playerTurn;
                    //adding new node to children vector
                    root->mChildren.push_back(newNode);
                    // recursively calling gen states to generate child nodes for each state
                    GenStates(newNode, !xPlayer);
                    
                }
            }
        }
        
}

float GetScore(const GameState& state)
{
    char outcome = ' ';
    // check diagonals
    GameState currentState = state;
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
    if (outcome == ' ') {
        outcome = 'N';
    }
    // returning the outcome
    if (outcome == 'X') {
        return -1.0;
    }
    else if (outcome == 'O') {
        return 1.0;
    }
    else {
        return 0.0;	// TODO: Fix this!
    }
}

float MinPlayer(const GTNode* node)
{
//	1. If the node is a leaf node, return it’s score
    if (node->mChildren.size() == 0) {
        
        return GetScore(node->mState);
    }
    
//    2. Otherwise return the smallest maximum score of all the child nodes (that
//    means calling the MaxPlayer function on all the children)
    else {
        std::vector<float> scores;
        
        // calling minPlayer on all the children and storing result in in vector
        for (int i = 0; i < node->mChildren.size(); i++) {
            
            scores.push_back(MaxPlayer(node->mChildren[i]));
            
        }
        // initializng min to the first element
        float min = scores[0];
        // checking the rest of the elements to see if they're smallerer than the first, and keeps updating min until loop is over
        for (int i = 1; i < scores.size(); i++) {
            if (scores[i] < min) {
                min = scores[i];
            }
        }
        
        return min;
    }
}

float MaxPlayer(const GTNode* node)
{
    
//    1. If the node is a leaf node, return its score
    
    if (node->mChildren.size() == 0) {
        
        return GetScore(node->mState);
    }
//    2. Otherwise return the largest minimum score of all the child nodes (that
//    means calling the MinPlayer function on all the children)
    else  {
        std::vector<float> scores;
        
        // calling minPlayer on all the children and storing result in in vector
        for (int i = 0; i < node->mChildren.size(); i++) {
            
            scores.push_back(MinPlayer(node->mChildren[i]));
            
        }
        // initializng max to the first element
        float max = scores[0];
        // checking the rest of the elements to see if they're bigger than the first, and keeps updating max until loop is over
        for (int i = 1; i < scores.size(); i++) {
            if (scores[i] > max) {
                max = scores[i];
            }
        }
        
        return max;
    }
}

const GTNode* MinimaxDecide(const GTNode* root)
{
//    • Starting with a given (or “root”) node – this will be the “current
    // setting max to be less than any possible return
    float max = -2.0;
    
    int maxIndex;
    
//    state” of the game
//    • Go through each child node of the root
    for (int i = 0; i < root->mChildren.size(); i++) {
        
        float temp = MinPlayer(root->mChildren[i]);
       // – Find the node with the largest MinPlayer score
        if (temp > max) {
            max = temp;
            
            maxIndex = i;
        }
        
    }
//
//    • Make the move to yield the state found above

    
	return root->mChildren[maxIndex];
}



unsigned pickMove(const GameState& board)
{

    // create new node
    GTNode* newNode = new GTNode();
    // copy board to new node
    newNode->mState = board;
    // generate states for the new board
    GenStates(newNode, false);
    
    // minimax decide
    const GTNode* miniMaxNode = new GTNode();
    // decide the next move
    miniMaxNode = MinimaxDecide(newNode);
    
    
    
    
    // create helper function to figure out which square to pick
    
    unsigned move = boardDifference(newNode, miniMaxNode);
    
    
    
    
    
	return move;
}


unsigned boardDifference(const GTNode* original, const GTNode* miniMaxNode) {
    
    // initializng ints that will hold which row and column are different
    int diffRow;
    int diffCol;
    
    // looping thru each position, looking for difference
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            
            if (original->mState.mBoard[i][j] != miniMaxNode->mState.mBoard[i][j]) {
                // if difference is found, assign diffRow and diffCol accordingly
                
                diffRow = i;
                diffCol = j;
            }
            
        }
    }
    // determining number 1-9 based on row and column number
    if (diffRow == 0) {
        return diffCol + 1;
    }
    
    else if (diffRow == 1) {
        return diffCol + 4;
    }
    
    else {
        return diffCol + 7;
    }
}

