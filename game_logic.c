/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLUE) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){
       
        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");  
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
{
	int tokens_placed; //each player gets 4 tokens
	int person;			//counts through the players
	int previous[6];			//value in the locations previous[0-5] correspond to rows 0-5 and contain the colourindex previosuly placed in that row
	int choice, i;				//choice contains the users choice of row to place their token, i is used as a counter
	bool valid = false;	//valid checks whether a choice is valid and on the list
	bool valid2 = false;
	char colours[][7] = {{"RED"}, {"BLUE"}, {"GREEN"}, {"YELLOW"}, {"PINK"}, {"ORANGE"}}; //colours corresponding to colourindex
	bool choices;	//used to check whether the exception to the lowest level rule is needed
	int tokens = 0;	//used to count how many tokens have been placed
	char check[10]; // used to ensure that input is valid
	char c;
	int minLevel; //number of tokens on the minimum level
	
	for(tokens_placed=0;tokens_placed < 4;tokens_placed++)  	
	{
		for(person=0;person<numPlayers;person++)				
		{
			printf("Please enter the number row you would like to place your token in %s\n", players[person].name);
			valid = false;	
			
			//this loop iterates through the first column to find the minimum level of tokens, that is the square with the lest amount of tokens
			minLevel = board[0][0].numTokens;
			for(i=0;i<6;i++)
			{
				if(minLevel > board[i][0].numTokens)
					minLevel = board[i][0].numTokens;
			}
			while(!valid)			//iterates until a valid choice is given
			{
				valid2 = false;		
				choices = false;	

				for(i=0;i<6;i++)	{
				if(board[i][0].numTokens == minLevel && previous[i] != players[person].col) //if square has the least amount of tokens and the previous token is not of the same colour
				{
					choices = true;		//the exception to the lowest level rule will not be triggered
					printf("(%d) ROW %d\n", i, i); //prints the rows which can be chosen
				}
				}
				
				if(choices)	//if the exception to the lowest level rule is not triggered
				{
					fgets(check,9,stdin);		//MAKES SURE THAT INPUT OF STRINGS OR CHARACTERS DOES NOT CAUSE ERROR OF INFINITE LOOP
					c = check[0];
					choice = c - '0';
					if(check[1] != '\n' && check[1] != ' ') //aka if they enter eg. 1d, 123, 33 etc
					{
						choice += 100;		//makes it so that its an invalid answer
					}
					
					
					if(choice < 0 || choice > 6 ||  board[choice][0].numTokens != minLevel)  //if the choice is invalid (aka not 0-5 or the square does not have the minimum number of tokesn)
					{
						printf("Choice is not valid, please enter a number shown above2\n");
					}
					else if(previous[choice] == players[person].col) //if the choice points to a location where the previous is the same as the user who is currently choosing's token
					{
						printf("You cannot place a token there as the previous token is the same colour\n");
					}
					else				//is a valid choice
					{
						valid2 = true; 	//valid2 is set to true
					}
				}
				else if (!choices) //if the exception to the rule is triggered a person can place their token only a location where taken[] is equal to one and is a location where the previous token is not the same colour
				{
					printf("\nPlacing token on a higher level as you cannot place it on your your own token\n"); //informs the user that there token is being placed on a higher level
					
					for(i=0;i<6;i++) //iterates through taken[]
					{
						if(board[i][0].numTokens > minLevel && previous[i] != players[person].col)//If the number of tokens on that square is higher than the minimum level and the previous token is not of the same colour
						{
							printf("(%d) ROW %d\n", i, i); //prints the rows which can be chosen
						}
					}
					
					fgets(check,9,stdin);		//MAKES SURE THAT INPUT OF STRINGS OR CHARACTERS DOES NOT CAUSE ERROR OF INFINITE LOOP
					c = check[0];
					choice = c - '0';
					if(check[1] != '\n' && check[1] != ' ') //aka if they enter eg. 1d, 123, 33 etc
					{
						choice += 100;		//makes it so that its an invalid answer
					}
					
					if(choice < 0 || choice > 6 ||  board[i][0].numTokens == minLevel) //if the choice is invalid(aka chhoice is not 0-5 or is not above the minlevel
					{
						printf("Choice is not valid, please enter a number shown above\n");
					}
					else if(previous[choice] == players[person].col) //if the choice points to a location where the previous is the same as the user who is currently choosing's token
					{
						printf("You cannot place a token there as the previous token is the same colour\n");
					}
					else
					{
						valid2 = true;
					}
				}
					
				if(valid2)
				{					
					printf("%s token placed in row %d\n", colours[players[person].col], choice); //tells user which row/colour it was placed in
	
					board[choice][0].numTokens++;	//increases the number of tokens in the square
					
					previous[choice] = players[person].col;		//sets the previous array at that location to the colourindex of the token placed there

					//this creates a new node on the token placed on this particular square, the newly placed token is now on top of the stack
					struct token *curr = board[choice][0].stack;
					board[choice][0].stack = malloc(sizeof(token));
					board[choice][0].stack->col = players[person].col;
					board[choice][0].stack->next = curr;  

					print_board(board);						//PRINTS THE BOARD SO PLAYER CAN VIEW IT
					valid = true;							//exits loop as valid choice entered
					tokens++;								//COUNTS THE AMOUNT OF TOKENS PLACED
					printf("%d tokens placed\n", tokens);	//PRINTS THE AMOUNT OF TOKENS PLACED
				}
			}
				
					
		}
	}
					
}



/* 
 *  * Manages the logic of the game
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players 
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
{
	int dice;
	int person = 0;
	char movePiece;
	int i, j;
	int row, column;
	int direction;
	bool validChoice;
	
	srand(time(NULL));
	printf("\n");
	printLine();
	printf("               GAME START                  \n");
	printLine();

	print_board(board);
	printf("Game squares are represented as (row,column)\n");
	dice = rand()%6+1;
	printf("%s has rolled %d\n",players[person].name, dice);
	
	
	printf("Would you like to move one your pieces up or down?(Y/N)\n");
	scanf("%c", &movePiece);
	if(movePiece == 'y' || movePiece == 'Y')
	{
		printf("Select which piece you would like to move\n");
		for(i=0;i<6;i++)
		{
			for(j=0;j<9;j++)
			{
				if(board[i][j].stack != NULL)
				{
					if(board[i][j].stack->col == players[person].col)
					{
						printf("(%d,%d)\n", i, j);
					}
				}
				
			}
		}
		
		validChoice = false;
		while(!validChoice)
		{
			printf("Enter row number\n");
			scanf("%d", &row);
			printf("Enter column number\n");
			scanf("%d", &column);

			if(board[row][column].stack != NULL)
				{
					printf("This square is empty, try again\n");
					continue;
				}

			else if(board[row][column].stack->col != players[person].col)
				{
					printf("Your token is not on top of this square\n");
					continue;
				}
			else
				validChoice = true;
		}
			validChoice = false;

		while(!validChoice)	
		{
			printf("Would you like to move up or down\n");
			printf("(1)Up\n(2)Down\n");
			scanf("%d", &direction);
			switch(direction)
			{
				case 1: direction = -1;
					break;
				case 2: direction = 1;
					break;
				default: direction = 6;
					break;
			}
		
			if(i+direction > 5 || i+direction < 0)
				continue;
			else
				validChoice = true;
		}


		struct token *curr = board[row+direction][column].stack;
		board[row+direction][column].stack = malloc(sizeof(token));
		board[row+direction][column].stack->col = players[person].col;
		board[row+direction][column].stack->next = curr;  
		
		struct token *curre = board[row][column].stack;
		if(curre!=NULL)
		{
			board[row][column].stack = curre->next;
			free(curre);
		}
		printf("%s has moved a piece from (%d,%d) to (%d,%d)", players[person].name, row, column, row+direction, column);
		print_board(board);
	}
}


int diceRoll()
{
	return rand()%6+1;
}

/*pop
struct token *curr = board[4][0].stack;
if(curr!=NULL){
	board[4][0].stack = curr->next;
	
	free(curr);
}
print_board(board);	*/