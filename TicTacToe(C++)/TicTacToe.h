// Assignment 9: TicTacToe.h
// Declaration of class TicTacToe.
// Member functions are defined in TicTacToe.cpp.
// Author: Timur Makimov
// Date: Nov 28th, 2014

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <array>

class TicTacToe 
{
private:  
   enum class Status { WIN, DRAW, CONTINUE }; // enumeration constants
           // The above line declares enum type "Status" but does
           // _NOT_ declare a data member of the class !!!
   static const int ROW = 3;
   static const int COL = 3;
   static const int EMPTY = 32;
   static const int X = 88;
   static const int O = 79;
   static const int x = 1;
   static const int o = 0;
   std::array <std::array <int, COL>, ROW> board;
  
public:
   TicTacToe(); // default constructor
   void makeMove(); // make move
   void printBoard()const; // print board
   bool validMove( const int &, const int &)const; // validate move
   bool xoMove( const int &); // x o move 
   Status gameStatus()const; // game status
   
}; // end class TicTacToe

#endif
