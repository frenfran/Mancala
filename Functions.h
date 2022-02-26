#pragma once

#include "Globals.h"

// instructions
void instructions ();

// initialize game board
// parameters: game board
void initializeBoard (int [numRows][numCols]);

// print game board
// parameters: game board, player one's store, player two's store
void printBoard (int [numRows][numCols], int, int);

// decide whether player two will be the computer or not
// returns true if player two will be the computer; false, if not
bool selectComputer ();

// get player move
// prompts player for move
// parses player input + performs error checking
// returns player move (column number)
// parameters: game board, player number
int playerMove (int [numRows][numCols], int);

// computer move for player two
// returns computer move (column number)
// parameters: game board
int computerMove (int [numRows][numCols]);

// make move
// parameters: game board, player's store, player number, column number chosen for turn
void makeMove (int [numRows][numCols], int &, int, int);

// rotation algorithm
// parameters: game board, row number, column number, player number, number of stones, player's store
void rotationAlgorithm (int [numRows][numCols], int, int, int, int, int &);

// determine if a player gets an extra turn
// returns true if player gets an extra turn, false if not
// parameters: game board, column number chosen for turn, player number
bool extraTurn (int [numRows][numCols], int, int);

// check if game is over
// returns true if game is finished, false if not
// parameters: game board, player one's store, player two's store
bool checkGameOver (int [numRows][numCols], int &, int &);