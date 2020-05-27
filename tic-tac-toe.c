/**************************************************************************
 * Assessment Title: ACE 2
 *
 * Number of Submitted C Files: 1
 *
 * Date: 26.10.2017
 *
 * 
 * Author: Pavel Dimitrov Dimitrov, Reg no: 201644319
 *
 *
 * Personal Statement: I confirm that this submission is all my own work.
 *
 *          (Signed) Pavel Dimitrov Dimitrov
 *
 * 
 *
 **************************************************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void user_prompt(void);
void clear_board(char board[3][3]);
void display_board(char board[3][3]);
void user_move(char board[3][3]);
void computer_move(char board[3][3]);
int detect_win(char board[3][3]);

int game_type = -1; // used to determine whether it player vs computer or player vs player
char player_names[2][100] = {"Computer", "Computer"}; // used to save player names
int player_turn = -1; // used to determine who is on turn
int computer_turn = -1; // used to check if the computer is on turn

/*
	Initializes all variables required to generate the Tic-tac-toe game, creates the game,
	allows the player or players to play the game and keeps track of players' wins.
*/
int main(void)
{
	char board[3][3] = {{'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'}};
	int game_running = 1;
	int wins[2] = {0, 0};
	char temp[2];
	int i;
	
	user_prompt();

	while(game_running)
	{
		clear_board(board);
		display_board(board);
		
		for(i = 0 ; i < 9 && detect_win(board) == 0 ; i++)
		{
			player_turn = i % 2;

			user_move(board);			
			display_board(board);
		}
		
		if(detect_win(board))
		{
			printf("Player \"%s\" wins!\n", player_names[player_turn]);
			wins[player_turn]++;
		}
		else
		{
			printf("No one wins this game!\n");
		}
		
		printf("Result so far - \"%s\" %d : %d \"%s\"\n", player_names[0], wins[0], wins[1], player_names[1]);
		
		while(1)
		{
			printf("\nDo you want to play another game? [y/n] (\'q\' for exit): ");
			scanf("%s", temp);
			
			if (!strcmp(temp, "n"))
			{
				game_running = 0;
				break;
			}	
			else if(!strcmp(temp, "y"))
				break;
			else if (!strcmp(temp, "q"))
				return 0;
			else
				printf("Invalid option!\n");
		}
	}
	
	return 0;
}

/*
	When called, this function asks for the game type (player vs computer or player vs player),
	asks for player 1's sign (X or O), asks for player 1's name 
	and, depending on game type, player 2's name.
	
	parameter: void
*/
void user_prompt(void)
{
	char temp[100];
	
	while(1)
	{
		printf("Please enter (\'q\' for exit) against who you want to play:\nu - against the user\nc - against the computer\n");
		scanf("%s", temp);
		
		if(!strcmp(temp, "u"))
		{
			game_type = 1;
			break;
		}
		else if (!strcmp(temp, "c"))
		{
			game_type = 0;
			break;
		}
		else if (!strcmp(temp, "q"))
			exit(0);
		else
			printf("Invalid option!\n");
	}
	
	int first_choice = -1;
	int second_choice = -1;
	
	while(1)
	{
		printf("\nPlease enter (\'q\' for exit) which symbol you want to play with:\nx - play with \'X\' and make the first move\no - play with \'O\' and make the second move\n");
		scanf("%s", temp);
		
		if(!strcmp(temp, "x"))
		{
			first_choice = 0;
			second_choice = 1;
			break;
		}
		else if (!strcmp(temp, "o"))
		{
			first_choice = 1;
			second_choice = 0;
			break;
		}
		else if (!strcmp(temp, "q"))
			exit(0);
		else
			printf("Invalid option!\n");
	}
	
	while(1)
	{
		printf("\nPlease enter (\'q\' for exit) Player 1 nickname: ");
		scanf("%s", player_names[first_choice]);
		
		if (!strcmp(player_names[first_choice], "q"))
			exit(0);
			
		if(!strcmp(player_names[first_choice], player_names[second_choice]))
		{
			printf("Names cannot be the same!\n");
			continue;
		}	
		
		printf("Are you sure you want to use \"%s\" as Player 1 nickname? [y/n] (\'q\' for exit): ", player_names[first_choice]);	
		scanf("%s", temp);
		
		if (!strcmp(temp, "n"))
			continue;
		else if(!strcmp(temp, "y"))
			break;
		else if (!strcmp(temp, "q"))
			exit(0);
		else
			printf("Invalid option!\n");
	}
	
	if(game_type == 1)
	{
		while(1)
		{
			printf("\nPlease enter (\'q\' for exit) Player 2 nickname: ");
			scanf("%s", player_names[second_choice]);
			
			if (!strcmp(player_names[second_choice], "q"))
				exit(0);
			
			if(!strcmp(player_names[first_choice], player_names[second_choice]))
			{
				printf("Names cannot be the same!\n");
				continue;
			}
			
			printf("Are you sure you want to use \"%s\" as Player 2 nickname? [y/n] (\'q\' for exit): ", player_names[second_choice]);	
			scanf("%s", temp);
			
			if (!strcmp(temp, "n"))
				continue;
			else if(!strcmp(temp, "y"))
				break;
			else if (!strcmp(temp, "q"))
				exit(0);
			else
				printf("Invalid option!\n");
		}
	}
	else
	{
		computer_turn = second_choice;
		srand(time(NULL));
	}
}

/*
	When called, this function clears the game board and 
	sets every field to default value '-'.
	
	parameter: board[3][3]
*/
void clear_board(char board[3][3])
{
	int r, c;
	
	for(r = 0 ; r < 3 ; r++)
	{
		for(c = 0 ; c < 3 ; c++)
		{
			board[r][c] = '-';
		}
	}
}

/*
	When called, this function prints the game board on the user's screen.
	
	parameter: board[3][3]
*/
void display_board(char board[3][3])
{
	printf("    1   2   3\n");
	printf("   -----------\n");
	printf("a | %c | %c | %c |\n", board[0][0], board[0][1], board[0][2]);
	printf("   -----------\n");
	printf("b | %c | %c | %c |\n", board[1][0], board[1][1], board[1][2]);
	printf("   -----------\n");
	printf("c | %c | %c | %c |\n", board[2][0], board[2][1], board[2][2]);
	printf("   -----------\n");
}

/*
	When called, this function shows which player is on turn,
	asks the player for a valid field and places player's sign
	on the board. If is game against the computer, it calls
	the computer_move() function whenever it is the computer's turn.
	
	parameter: board[3][3]
*/
void user_move(char board[3][3])
{
	printf("Player \"%s\" is on turn!\n", player_names[player_turn]);
	
	if(game_type == 0 && player_turn == computer_turn)
	{
		computer_move(board);
	}
	else
	{	
		char temp[2];
		
		while(1)
		{
			printf("Enter a field (e.g. \"a1\", \"b2\", \"c3\") to place \'%c\': ", player_turn == 0 ? 'X' : 'O');
			scanf("%s", temp);
				
			if(!strcmp(temp, "a1"))
			{
				if(board[0][0] == '-')
				{
					board[0][0] = player_turn == 0 ? 'X' : 'O';
					break;
				}	
				else
					printf("Invalid move! Field already filled!\n");			
			}
			else if(!strcmp(temp, "a2"))
			{
				if(board[0][1] == '-')
				{
					board[0][1] = player_turn == 0 ? 'X' : 'O';
					break;
				}
				else
					printf("Invalid move! Field already filled!\n");
			}		
			else if(!strcmp(temp, "a3"))
			{
				if(board[0][2] == '-')
				{
					board[0][2] = player_turn == 0 ? 'X' : 'O';
					break;
				}
				else
					printf("Invalid move! Field already filled!\n");
			}
			else if(!strcmp(temp, "b1"))
			{
				if(board[1][0] == '-')
				{
					board[1][0] = player_turn == 0 ? 'X' : 'O';
					break;
				}
				else
					printf("Invalid move! Field already filled!\n");
			}
			else if(!strcmp(temp, "b2"))
			{
				if(board[1][1] == '-')
				{
					board[1][1] = player_turn == 0 ? 'X' : 'O';
					break;
				}
				else
					printf("Invalid move! Field already filled!\n");
			}
			else if(!strcmp(temp, "b3"))
			{
				if(board[1][2] == '-')
				{
					board[1][2] = player_turn == 0 ? 'X' : 'O';
					break;
				}
				else
					printf("Invalid move! Field already filled!\n");
			}
			else if(!strcmp(temp, "c1"))
			{
				if(board[2][0] == '-')
				{
					board[2][0] = player_turn == 0 ? 'X' : 'O';
					break;
				}
				else
					printf("Invalid move! Field already filled!\n");
			}
			else if(!strcmp(temp, "c2"))
			{
				if(board[2][1] == '-')
				{
					board[2][1] = player_turn == 0 ? 'X' : 'O';
					break;
				}
				else
					printf("Invalid move! Field already filled!\n");
			}
			else if(!strcmp(temp, "c3"))
			{
				if(board[2][2] == '-')
				{
					board[2][2] = player_turn == 0 ? 'X' : 'O';
					break;
				}
				else
					printf("Invalid move! Field already filled!\n");
			}
			else if(!strcmp(temp, "q"))
				exit(0);
			else
				printf("Invalid move!\n");
		}
	}
}

/*
	When called, this function collects all free fields on the
	board, randomly selects one and puts the computer sign on it.
	
	parameter: board[3][3]
*/
void computer_move(char board[3][3])
{
	int free[9];
	int i = 0;
	int r, c;
	
	for(r = 0 ; r < 3 ; r++)
	{
		for(c = 0 ; c < 3 ; c++)
		{
			if(board[r][c] == '-')		
				free[i++] = r*3 + c;
		}
	}
	
	int move = rand() % i;
	
	board[free[move] / 3][free[move] % 3] = player_turn == 0 ? 'X' : 'O';
	
	printf("Player \"%s\" puts \'%c\' on field %c%d\n", player_names[player_turn], player_turn == 0 ? 'X' : 'O', ((free[move] / 3 == 0) ? 'a' : (free[move] / 3 == 1) ? 'b' : 'c'), ((free[move] % 3) + 1));
}

/*
	When called, this function checks whether there is a win on the board.
	
	parameter: board[3][3]
*/
int detect_win(char board[3][3])
{
	if(board[1][1] != '-')
	{
		if((board[0][0] == board[1][1] && board[0][0] == board[2][2]) || (board[0][2] == board[1][1] && board[0][2] == board[2][0]))
			return 1;
	}
	
	int i;
	
	for(i = 0 ; i < 3 ; i++)
	{
		if(board[i][0] != '-')
		{
			if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
				return 1;
		}
		
		if(board[0][i] != '-')
		{
			if(board[0][i] == board[1][i] && board[0][i] == board[2][i])
				return 1;
		}
	}
	
	return 0;
}
