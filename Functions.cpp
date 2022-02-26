#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "Functions.h"
#include "Globals.h"


// instructions for how to play the game
void instructions () {
    cout << "\t\t\t\t\t\t\t\t\t\t\t************" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tINSTRUCTIONS" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t************" << endl << endl;
    
    // need to write
    cout << "The objective of the game is to deposit as many stones into your store" << endl;
    cout << "Player one's store is at the right of the board while player two's store is at the left" << endl;
    cout << "When it's your turn, enter the column number of the pit in which you'd like to make your move" << endl;
    cout << "For example, you may enter: 4" << endl << endl;
    
    cout << "All of the stones at the chosen pit will be removed and deposited one by one in a counter clockwise fashion in each pit that follows" << endl;
    cout << "If your store is encountered, one stone will be dropped into it but if the opponent's store is encountered, no stone will be deposited" << endl;
    cout << "If the last stone ends up being deposited in your store, you get an extra turn" << endl;
    cout << "If the last stone ends up being deposited in an empty pit on your side, you deposit that stone plus all of the stones in the pit directly opposite to the empty pit on the opponent's side into your store" << endl << endl;
    
    cout << "The game ends when either player has no more stones on their side of the board" << endl;
    cout << "Any remaining stones on the opponent's side of the board is deposited into their store" << endl;
    cout << "The player with the most stones in their store at the end of the game wins" << endl;
}

// initialize board
void initializeBoard (int array [numRows][numCols]) {
    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < numCols; j++)
            array[i][j] = 4;
}

// print board
void printBoard (int array[numRows][numCols], int playerOneStore, int playerTwoStore) {
    cout << endl << "           Player Two" << endl << endl;
    
    cout << "    ";
    for (int i = 0; i < numCols; i++)
        cout << "  " << i+1 << " ";
    cout << endl;
    
    for (int i = 0; i < (numCols + 2) * 4 + 1; i++)
        cout << "-";
    cout << endl;
        
    cout << "|   | ";
    for (int i = 0; i < numCols; i++) {
        cout << array[0][i]; 
        
        if (array[0][i] < 10)
            cout << " ";
        cout << "| ";
    }
    cout << "  |" << endl;
    
    cout << "| " << playerTwoStore; 
    if (playerTwoStore < 10)
        cout << " ";
    cout << "|";
    
    for (int i = 0; i < numCols * 4 - 1; i++)
        cout << "-";
    cout << "| " << playerOneStore;
    if (playerOneStore < 10)
        cout << " ";
    cout << "|" << endl;
    
    cout << "|   | ";
    for (int i = 0; i < numCols; i++) {
        cout << array[1][i];
        
        if (array[1][i] < 10)
            cout << " ";
        cout << "| ";
    }
    cout << "  |" << endl;
    
    for (int i = 0; i < (numCols + 2) * 4 + 1; i++)
        cout << "-";
    cout << endl;
    
    cout << endl << "           Player One" << endl << endl;
}

// determine if player two will be the computer
bool selectComputer () {
    while (true) {
        cout << "Would you like player two to be the computer? ";
        string line;
        string yesNo;
        getline (cin, line);
        stringstream lineStream (line);
        lineStream >> yesNo;
        
        for (int i = 0; i < (int) yesNo.length(); i++) // turn input into lower case
            yesNo[i] = tolower (yesNo[i]);
        
        if (lineStream.fail())
            cout << "Error, please try again" << endl;
        else if (yesNo == "y" || yesNo == "yes")
            return true;
        else if (yesNo == "n" || yesNo == "no")
            return false;
        else
            cout << "Error, please try again" << endl;
    }
}

// get move from player
int playerMove (int array[numRows][numCols], int playerNum) {
    int colNum;
    
    bool moveValid = false;
    while (!moveValid) {
        if (playerNum == 1)
            cout << "Player one, ";
        else
            cout << "Player two, ";
        
        cout << "enter your move: ";
        string line;
        getline (cin, line);
        stringstream lineStream (line);
        lineStream >> colNum;
        
        if (lineStream.fail())
            cout << "Error: invalid input. Please try again" << endl;
        else if (colNum < 1 || colNum > numCols)
            cout << "Error: move is out of bounds. Please try again" << endl;
        else if (playerNum == 1 && array[1][colNum - 1] == 0)
            cout << "Error: there are no stones in this square. Please try again" << endl;
        else if (playerNum == 2 && array[0][colNum - 1] == 0)
            cout << "Error: there are no stones in this square. Please try again" << endl;
        else
            moveValid = true;
    }
    
    return colNum;
}

// get move from computer
int computerMove (int array[numRows][numCols]) {
    int colNum = 0;
    bool moveSet = false;
    
    // first check if any moves will make the last stone drop in the store (effectively giving the computer an extra turn)
    for (int i = 0; i < numCols; i++) {
        if (array[0][i] == i+1) {
            colNum = i;
            moveSet = true;
            break;
        }
    }
            
    // check if there are empty pits on player's side + if player can capture computer's stones in pit opposite to the empty pit
    if (!moveSet) {
        int potentialLoss = 0; // represents number of stones at a certain position the computer would have lost
        for (int i = 0; i < numCols; i++) {
            if (array[1][i] == 0 && array[0][i] != 0) {
                
                for (int j = 0; j < i; j++) { // analyze numbers before the pit with zero stones
                    if (array[1][j] == i - j) {
                        if (array[0][i] > potentialLoss) {
                            potentialLoss = array[0][i]; // determine potential loss at this position
                            colNum = i;
                            moveSet = true;
                        }
                    }
                        
                    for (int k = numRows * numCols + 1; k < numRows * numCols * 4; k += numRows * numCols + 1) { // check for multiples that loop back to the same position
                        if (array[1][j] - k == i - j) {
                            if (array[0][i] > potentialLoss) {
                                potentialLoss = array[0][i]; // determine potential loss at this position
                                colNum = i;
                                moveSet = true;
                            }
                        }
                    }
                }
                
                for (int j = numCols - 1; j > i; j--) { // analyze numbers after the pit with zero stones (in case player can loop around board)
                    if ((numRows * numCols) - j + 1 + i == array[1][j]) {
                        if (array[0][i] > potentialLoss) {
                            potentialLoss = array[0][i];
                            colNum =  i;
                            moveSet = true;
                        }
                    }
                }
            }
            
            for (int k = numRows * numCols + 1; k < numRows * numCols * 4;  k+= numRows * numCols + 1) { // check if any position can loop back to itself (effectively landing in a pit with zero stones)
                if (array[1][i] == k) {
                    if (array[0][i] > potentialLoss) {
                        potentialLoss = array[0][i];
                        colNum = i;
                        moveSet = true;
                    }
                }
            }
        }
    }
    
    // check if there are empty pits on computer's side + if computer can capture player's stones in pit opposite to empty pit
    if (!moveSet) {
        int potentialWin = -1; // represents number of stones at a a certain position the computer would have won
        for (int i = 0; i < numCols; i++) {
            if (array[0][i] == 0) {
                
                for (int j = numCols - 1; j > i; j--) { // analyze numbers to the right of the pit with zero stones
                    if (array[0][j] == j  - i) {
                        if (array[1][i] > potentialWin) {
                            potentialWin = array[1][i]; // determine potential win at this position
                            colNum = j;
                            moveSet = true;
                        }
                    }
                    
                    for (int k = numRows * numCols + 1; k < numRows * numCols * 4; k += numRows * numCols + 1) { // check for multiples that loop back
                        if (array[0][j] - k == j - i) {
                            if (array[1][i] > potentialWin) {
                                potentialWin = array[1][i]; // determine potential win at this position
                                colNum = j;
                                moveSet = true;
                            }
                        }
                    }
                }
                
                for (int j = 0; j < i; j++) { // analyze numbers to the left of the pit with zero stones (in case computer can loop around board)
                    if ((numRows * numCols) - i + 1 + j == array[0][j]) {
                        if (array[1][i] + 1 > potentialWin) { // add one to the potential win as a result of looping
                            potentialWin = array[1][i];
                            colNum = j;
                            moveSet = true;
                        }
                    }
                }
            }
            
            for (int k = numRows * numCols + 1; k < numRows * numCols * 4;  k += numRows * numCols + 1) { // check if any position can loop back to itself (effectively landing in a pit with zero stones)
                if (array[0][i] == k) {
                    if (array[1][i] + 1 > potentialWin) { // add one to the potential win as a result of looping
                        potentialWin = array[1][i];
                        colNum = i;
                        moveSet = true;
                    }
                }
            }
        }
    }
    
    // start hoarding if less than two-thirds of the total number of stones remain on the board
    if (!moveSet) {
        int stonesLeft = 0; // represents the total number of stones left on the board
        for (int i = 0; i < numCols; i++)
            for (int j = 0; j < numRows; j++)
                stonesLeft += array[i][j];
        
        if (stonesLeft < 2 * ((numRows * numCols * 4) / 3)) {
            int smallestValue = numRows * numCols;
            
            for (int i = 0; i < numCols; i++) { // find position on board with the smallest number of stones
                if (array[0][i] != 0 && array[0][i] < smallestValue) {
                    colNum = i;
                    smallestValue = array[0][i];
                }
            }
                    
            moveSet = true;
        }
    }
    
    // default case: play move closest to left edge of board
    if (!moveSet) {
        for (int i = 0; i < numCols; i++) {
            if (array[0][i] != 0) {
                colNum = i;
                break;
            }
        }
    }
    
    return colNum;
}

// make move
void makeMove (int array[numRows][numCols], int & playerStore, int playerNum, int colNum) {
    int rowNum;
    int numStones;
    
    if (playerNum == 1) // player one's move
        rowNum = 1;
    else // player two's move
        rowNum = 0;
    
    numStones = array[rowNum][colNum]; // get the total number of stones from player move's position
    array[rowNum][colNum] = 0; // all stones are removed from player move's position
    
    // start turn at the next square
    if (playerNum == 1) {
        if (colNum + 1 < numCols) // next square is still in the same row
            colNum++;
        else { // next square is in the other row
            rowNum = 0;
            
            playerStore ++; // place one stone in player's store first
            numStones --;
        }
    }
    else {
        if (colNum - 1 >= 0) // next square is still in the same row
            colNum--;
        else { // next square is in the other row
            rowNum = 1;
            
            playerStore ++; // place one stone in player's store first
            numStones --;
        }
    }
        
    rotationAlgorithm (array, rowNum, colNum, playerNum, numStones, playerStore);
}

// rotation algorithm
void rotationAlgorithm (int array[numRows][numCols], int rowNum, int colNum, int playerNum, int numStones, int & playerStore) {
    bool rotationFinished = false;
    while (rotationFinished == false) {
        if (rowNum == 1) { // we are in the bottom row
            for (int i = colNum; i < numCols; i++) {
                if (numStones == 0) { // turn is finished
                    rotationFinished = true;
                    return;
                }
                
                array[rowNum][i] ++;
                numStones --;
                colNum = i;
                
                if (numStones == 0 && playerNum == 1 && array[rowNum][colNum] == 1) { // player's last stone landed in empty pit on their own side 
                        playerStore += array[rowNum][colNum] + array[0][colNum]; // add number of stones in pit and number of stones in opposite pit to player's store
                        
                        // set both pits to zero stones
                        array[rowNum][colNum] = 0;
                        array[0][colNum] = 0;
                        
                        return;
                }
            }
            
            if (playerNum == 1 && numStones > 0) { // deposit one stone in player one's store
                playerStore ++;
                numStones --;
            }
            
            rowNum = 0; // move to top row
        }
        
        else { // we are in the top row
            for (int i = colNum; i >= 0; i--) {
                if (numStones == 0) { // turn is finished
                    rotationFinished = true;
                    return;
                }
                
                array[rowNum][i] ++;
                numStones --;
                colNum = i;
                
                if (numStones == 0 && playerNum == 2 && array[rowNum][colNum] == 1) { // player's last stone landed in empty pit on their own side 
                        playerStore += array[rowNum][colNum] + array[1][colNum]; // add number of stones in pit and number of stones in opposite pit to player's store
                        
                        // set both pits to zero stones
                        array[rowNum][colNum] = 0;
                        array[1][colNum] = 0;
                        
                        return;
                }
            }
            
            if (playerNum == 2 && numStones > 0) { // deposit one stone in player two's store
                playerStore++;
                numStones --;
            }
            
            rowNum = 1; // move to bottom row
        }
    }
}

// determine if a player gets an extra turn
bool extraTurn (int array[numRows][numCols], int colNum, int playerNumber) {
    if (playerNumber == 1) { // checking for player one
        if (numCols - colNum == array[1][colNum]) // if number of stones at player's move equals distance from position to player's store, last stone lands in the store 
            return true;

        for (int k = numCols * numRows + 1; k < numCols * numRows * 4; k += numCols * numRows + 1) // check for multiples
            if (numCols - colNum == array[1][colNum] - k)
                return true;
    }
    
    else { // checking for player two
        if (colNum + 1 == array[0][colNum]) // if number of stones at player's move equals distance from position to player's store, last stone lands in the store 
            return true;

        for (int k = numCols * numRows + 1; k < numCols * numRows * 4; k += numCols * numRows + 1) // check for multiples
            if (colNum + 1 == array[0][colNum] - k)
                return true;
    }
    
    return false;
}

// check if game is over
bool checkGameOver (int array[numRows][numCols], int & playerOneStore, int & playerTwoStore) {
    int numStonesLeft = 0;
    for (int i = 0; i < numCols; i++)
        numStonesLeft += array[0][i];
    if (numStonesLeft == 0) { // player two has no more stones on their side
        for (int i = 0; i < numCols; i++) {
            playerOneStore += array[1][i]; // give all remaining stones on player one's side to player one's store
            array[1][i] = 0;
        }
            
        return true;
    }
    
    numStonesLeft = 0;
    for (int i = 0; i < numCols; i++)
        numStonesLeft += array[1][i];
    if (numStonesLeft == 0) { // player one has no more stones on their side
        for (int i = 0; i < numCols; i++) {
            playerTwoStore += array[0][i]; // give all remaining stones on player two's side to player two's store
            array[0][i] = 0;
        }
            
        return true;
    }
    
    return false; // game has not yet ended
}