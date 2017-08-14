// Assignment 9: TicTacToe.cpp
// Implementation of class TicTacToe.
// Author: Timur Makimov
// Date: Nov 28th, 2014

#include <iostream>
#include "TicTacToe.h" // include definiton of class TicTacToe
using namespace std;

TicTacToe::TicTacToe()
{
	//Initialize empty board
	for (auto & rows : board)
	{
		for (auto & cols : rows)
		{
			cols = EMPTY;
		}
	}
}

//Makes move for X or O
void TicTacToe::makeMove() 
{
	printBoard();
	while (!xoMove(x) && !xoMove(o)){}
}

//Returns true if either X or O wins or if draw. Otherwise returns false
bool TicTacToe::xoMove(const int & val)
{
	int row, col;
	
		if (val == x)
		{
			cout << "\nPlayer X enter move: ";
			cin >> row >> col;
			while (validMove(row, col) == false)
			{
				cout << "\nPlayer X enter move: ";
				cin >> row >> col;
			}
			board[row][col] = X;
			printBoard();
		}

		else 
		{
			cout << "Player O enter move: ";
			cin >> row >> col;
			while (!validMove(row, col))
			{
				cout << "Player O enter move: " << endl;
				cin >> row >> col;
			}
			board[row][col] = O;
			printBoard();
		}

		if (gameStatus() == Status::CONTINUE)
		{
			return false;
		}
		else 
		{
			return true;
		}
}

//Validates if inputs are in the range of the board
bool TicTacToe::validMove(const int & row, const int & col)const
{
	if ((row < 0 || row > 2) || (col < 0 || col > 2) || (board[row][col] != EMPTY))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//Returns WIN, DRAW of CONTINUE based on the inputs
TicTacToe::Status TicTacToe::gameStatus()const
{
	for (int i = 0; i < 3; i++)//Check for a win
	{
		if ((board[i][0] == X && board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
			(board[0][i] == X && board[0][i] == board[1][i] && board[1][i] == board[2][i]) ||
			(board[0][0] == X && board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
			(board[0][2] == X && board[0][2] == board[1][1] && board[1][1] == board[2][0]))
		{
			cout << "Player X wins!" << endl; 
			return Status::WIN;	
		}

		else if ((board[i][0] == O && board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
			(board[0][i] == O && board[0][i] == board[1][i] && board[1][i] == board[2][i]) ||
			(board[0][0] == O && board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
			(board[0][2] == O && board[0][2] == board[1][1] && board[1][1] == board[2][0]))
		{
			cout << "Player O wins!" << endl;
			return Status::WIN;
		}
		//Check for a draw
		else if ((board[i][0] != EMPTY && board[0][i] != EMPTY && board[0][0] != EMPTY && 
			board[0][2] != EMPTY && board[2][0] != EMPTY) &&
			(board[i][0] != board[i][1] || board[i][0] != board[i][2]) &&
			(board[0][i] != board[1][i] || board[0][i] != board[2][i]) &&
			(board[0][0] != board[1][1] || board[1][1] != board[2][2]) &&
			(board[0][2] != board[1][1] || board[0][2] != board[2][0]))
		{
			cout << "Game is a draw." << endl;
			return Status::DRAW;
		}
	}
	//Continue if neither WIN or DRAW
	return Status::CONTINUE;
}

//Prints board
void TicTacToe::printBoard()const
{
	cout << "\n     0     1     2"<< endl;
	cout << endl;

	cout << "      |     |     " << endl;
	cout << "0  " << static_cast<char>(board[0][0]) << "  |  " << static_cast<char>(board[0][1]) << "  |  " << static_cast<char>(board[0][2]) << endl;

	cout << " _____|_____|_____" << endl;
	cout << "      |     |     " << endl;

	cout << "1  " << static_cast<char>(board[1][0]) << "  |  " << static_cast<char>(board[1][1]) << "  |  " << static_cast<char>(board[1][2]) << endl;

	cout << " _____|_____|_____" << endl;
	cout << "      |     |     " << endl;

	cout << "2  " << static_cast<char>(board[2][0]) << "  |  " << static_cast<char>(board[2][1]) << "  |  " << static_cast<char>(board[2][2]) << endl;

	cout << "      |     |     " << endl << endl;

}