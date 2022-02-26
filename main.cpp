#include <iostream>
using namespace std;

#include "Functions.h"
#include "Globals.h"

int main (void) {
    cout << "COLLECTION OF CLASSIC GAMES" << endl << endl << "Welcome to..." << endl << "MANCALA" << endl << endl; // header
    int playerOneStore = 0; // number of stones in player one's store
    int playerTwoStore = 0; // number of stones in player two's store
    int board[numRows][numCols]; // gameboard (excluding stores)
    
    // instructions
    instructions();
    
    // initialize and print board
    cout << "Here is the board..." << endl;
    initializeBoard (board);
    printBoard (board, playerOneStore, playerTwoStore);
    
    bool playerTwoComputer = selectComputer (); // select whether player two will be the computer or not
    
    bool gameOver = false;
    while (!gameOver) {
        bool playerOneDone = false;
        while (!playerOneDone) {
            int colNum = playerMove (board, 1) - 1; // get player one's move
            
            playerOneDone = (!extraTurn (board, colNum, 1)); // check if player one gets an extra turn
            
            makeMove (board, playerOneStore, 1, colNum); // execute player one's move
            
            // check if game is over
            if (checkGameOver (board, playerOneStore, playerTwoStore)) {
                if (playerOneStore > playerTwoStore)
                    cout << "Game over! Player one wins!" << endl;
                else if (playerTwoStore > playerOneStore)
                    cout << "Game over! Player two wins!" << endl;
                else
                    cout << "Game over! Tie!" << endl;
                    
                gameOver = true;
            }
            
            printBoard (board, playerOneStore, playerTwoStore); // print board
            
            if (gameOver)
                return 0;
        }
        
        bool playerTwoDone = false;
        while (!playerTwoDone) {
            int colNum;
            if (!playerTwoComputer)
                colNum = playerMove(board, 2) - 1; // get player two's move
            else // player two is computer
                colNum = computerMove (board);
            
            playerTwoDone = (!extraTurn (board, colNum, 2)); // check if player two gets an extra turn
            
            if (playerTwoComputer)
                cout << "Computer makes move at column: " << colNum + 1 << endl;
            
            makeMove (board, playerTwoStore, 2, colNum); // player two's move
            
            // check if game is over
            if (checkGameOver (board, playerOneStore, playerTwoStore)) {
                if (playerOneStore > playerTwoStore)
                    cout << "Game over! Player one wins!" << endl;
                else if (playerTwoStore > playerOneStore)
                    cout << "Game over! Player two wins!" << endl;
                else
                    cout << "Game over! Tie!" << endl;
                    
                gameOver = true;
            }
            
            printBoard (board, playerOneStore, playerTwoStore);
            
            if (gameOver)
                return 0;
        }
    }
}