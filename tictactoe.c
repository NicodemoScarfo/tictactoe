/*
* 	A simple tictactoe game made to demonstrate the author's basic C capabilities, clean code tendancies, and general wit.
*	
* 	Author: Nicodemo Scarfo
*/

#include<stdio.h>
#include <stdbool.h>

//The default tictactoe game is 3 by 3, but this program allows for other square dimensions as well.
int dimension = 3;

//The game board is represented by an array of integers where 0 is O, 1 is X, and 2 is a Blank Space
//The maximum dimension is 10 by 10.
int board[10][10];

bool gameOn = true;
int turnNumber = 1;

//set the part of the gameboard we are going to use to all blank spaces
void initializeBoard()
{
	int row; int col;

	for (row = 0; row < dimension ;row++)
	{
		for(col = 0; col < dimension; col++)
		{
			board[row][col] = 2;
		}
	}
}

//This function is called once for each players turn and it runs through the basic logic of making a move.
//If the user inputs a move properly (as in "3 2" or "1 1"), and there is not already a piece occupying that space,
//then their piece is placed. If they try to place on a spot that is taken or that is outside of the board, they will
//be prompted to start again.
void turn(int whoseTurn) //input is 0 for O's turn, 1 for X's turn
{
	//represents the user's selected coordinates
	int varX = 0;
	int varY = 0;
	
	do{
		if (whoseTurn == 0)
		{
			printf("O, make your move. \n");
		}
		else 
		{
			printf("X, make your move. \n");
		}

	} while(scanf("%d %d", &varX, &varY) != 2);
	
	//users input coordinates starting count at '1', but the gameboard array starts count at 0
	varX--; varY--;

	if (varY >= dimension || varX >= dimension || board[varY][varX] != 2 || varY < 0 || varX < 0)
	{
		printf("Invalid move! Try again.\n");
		turn(whoseTurn);
	}
	else //valid input
	{
		if (whoseTurn == 0)
			board[varY][varX] = 0;
		else
			board[varY][varX] = 1;
	}
}

//Prints the board along with gridlines to the command line
void printBoard()
{
	int row; int col;

	//print horizontal axis label
	printf("| ");
	int count;
	for (count = 1; count <= dimension; count++)
	{
		printf("|%d", count);
	}
	printf("|\n");

	
	for (row = 0; row < dimension;row++)
	{
		int label = row + 1;
		//print vertical axis label
		printf("|%d", label);
		for(col = 0; col < dimension; col++)
		{

			int thisSpace = board[row][col];
			if (thisSpace == 0)
			{ 
				printf("|O");
			}
			else if (thisSpace == 1)
			{	
				printf("|X");
			}
			else
			{
				printf("| ");
			}
		}
		printf("|\n");	}
}

int winCheck() //returns 0 if O wins, 1 if X wins, 2 if nobody wins
{
	int row; int col;

	//check rows for a horizontal victory
	for (row = 0; row < dimension; row++)
	{
		int check1 = 1;
		int first = board[row][0];
		if (first == 2)
			break;

		for (col = 0; col < dimension && check1 == 1; col++)
		{
			if (board[row][col] != first) 
			{
				check1 = 0;
			}
		}
		if (check1)
		{
			return first;
		}
	}

	//check cols for a vertical victory
	for (col = 0; col < dimension; col++)
	{
		int check2 = 1;
		int first = board[0][col];
		if (first == 2)
			break;

		for (row = 0; row < dimension && check2 == 1; row++)
		{
			if (board[row][col] != first) 
			{
				check2 = 0;
			}
		}
		if (check2)
		{
			return first;
		}
	}

	//check the two diagnals for victory
	int check3 = 1; //rename
	int check4 = 1;
	int first_down = board[0][0];
	int first_up = board[dimension-1][0];
	
	//Check "downward diagnal"
	int count;
	for (count = 0; count < dimension && check3 == 1; count++)
	{
		int this = board[count][count];
		if (this == 2) 
			check3 = 0;

		if(board[count][count] != first_down)
			check3 = 0;
	}
	//Check "upward diagnal"
	for(count = 0; count < dimension && check4 == 1; count++)
	{
		int this = board[dimension - count - 1][count];
		if (this == 2)
			check4 = 0;

		if(board[dimension - count - 1][count] != first_up)
			check4 = 0;
	}

	if (check3)
	{
		return first_down;
	}

	else if(check4)
	{
		return first_up;
	}
		
	else
		return 2; //no winner yet
}

//A basic tictactoe game with variable dimension.
int main()
{
	printf("Hello and welcome to the tictactoe game. I am your host, Nicodemo.\n");
	printf("How large of a board would you like? ");
	scanf(" %d", &dimension);
	printf("X and O will now play a %d by %d game of Tic Tac Toe.\n", dimension, dimension);	
	printf("A valid move is of the form: X Y\n");

	initializeBoard();
	
	while (gameOn)
	{
		printf("Turn number: %d \n", turnNumber);
		printBoard();
		turn(0);
		printBoard();

		if (winCheck() != 2)
		{
			printf("GAME OVER\n");
			gameOn = false;
			break;
		}


		turn(1);
		printBoard();

		if (winCheck() != 2)
		{
			printf("GAME OVER\n");
			gameOn = false;
			break;
		}

		turnNumber++;
	}

	printf("Well, it looks like we have a winner. Thanks for playing!\n");
}
