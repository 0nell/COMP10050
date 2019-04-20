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



/*
 * Prints a straight horisontal line across the console
 */
void printLine(){
  printf("   -------------------------------------\n");  
}

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

 
 /*
 * Checks to make sure integer input is valid and doesn't cause an infinite loop
 * 
 * Output: the user input
 */

int checkInput()
{
	fflush(stdin); // flushing the input buffer
	int container;
	char check[10];
	char c;
	fgets(check,9,stdin);		//MAKES SURE THAT INPUT OF STRINGS OR CHARACTERS DOES NOT CAUSE ERROR OF INFINITE LOOP
		c = check[0];
		container = c - '0';
		if(check[1] != '\n' && check[1] != ' ') //aka if they enter eg. 1d, 123, 33 etc
			container += 100;		//makes it so that its an invalid answer
	fflush(stdin);
	return container;
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
	int minLevel; //number of tokens on the minimum level
	
	
	for(tokens_placed=0;tokens_placed < 4;tokens_placed++)  //iterates through the number of tokens placed by each player,(each player gets to place 4 tokens)
	{
		for(person=0;person<numPlayers;person++)			//iterates through the number of players	
		{
			print_board(board);		//PRINTS THE BOARD SO PLAYER CAN VIEW IT
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

				for(i=0;i<6;i++)	
				{
					if(board[i][0].numTokens == minLevel && previous[i] != players[person].col) //if square has the least amount of tokens and the previous token is not of the same colour
					{
						choices = true;		//the exception to the lowest level rule will not be triggered
						printf("(%d) ROW %d\n", i, i); //prints the rows which can be chosen
					}
				}
				
				if(choices)	//if the exception to the lowest level rule is not triggered
				{
					choice = checkInput();
					
					if(choice < 0 || choice > 5 ||  board[choice][0].numTokens != minLevel)  //if the choice is invalid (aka not 0-5 or the square does not have the minimum number of tokesn)
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
					printf("\nSince the minimum level is full of your own colour you can place your token on any square\n"); //informs the user that there token is being placed on a higher level
					
					for(i=0;i<6;i++) //iterates through taken[]
					{
							printf("(%d) ROW %d\n", i, i); //prints the rows which can be chosen
					}
					
					choice = checkInput();
					
					if(choice < 0 || choice > 5) //if the choice is invalid(aka chhoice is not 0-5 or is not above the minlevel
					{
						printf("Choice is not valid, please enter a number shown above\n");
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
	int dice; //Holds the value of the dice roll
	int person = 0; //the current player
	char movePiece; // variable to check whether to user wants to move a piece up or down
	int i, j;
	int row, column; // holds user input of piece they want to move up or down
	int direction; // direction the user wants to move
	bool validChoice; // used to check if the choice the user made is valid
	bool finished = false; // checking if the game is finished
	bool check = true;
	bool possible = false; // checking if its possible for the user to move
	int choice; // olds the user choice
	
	srand(time(NULL)); //randomises the seed for the random number generator
	//printing game start
	printf("\n");
	printLine();
	printf("               GAME START                  \n");
	printLine();
	print_board(board);
	
	while(!finished)
	{
		printf("Game squares are represented as (row,column)\n");	//alerts user of the format of the square co-ordinates
		dice = rand()%6;		//rolling die
		printf("%s has rolled row %d\n",players[person].name, dice); //alerts user to their dice result
		
		fflush(stdin);//flushes the standard input
		printf("\nWould you like to move one your pieces up or down?\nEnter 'y' if yes\nEnter any other key if no\n");	//prompts user to enter a character and choose whether to move up/down or leave their pieces in the same rows
		scanf("%c", &movePiece);	//takes user input 
		possible = false; //resets possible to false
		
		//runs if the user wants to move up or down
		if(movePiece == 'y' || movePiece == 'Y')
		{
			printf("\nSelect which piece you would like to move\n");
			for(i=0;i<6;i++)
			{
				for(j=0;j<8;j++)
				{
					if(board[i][j].stack != NULL && board[i][j].type != OBSTACLE)	//if the square is not empty and is not an obstacle square
					{
						if(board[i][j].stack->col == players[person].col)	//if the colour token in the square is the players token
						{
							printf("(%d,%d)\n", i, j);	//prints the co-ordinates of the square which can be moved
							possible = true; // checks if it is possible to move
						}
					}
					
				}
			}
			
			//runs if it is possible to move
			if(!possible)
			{
				printf("\n\nWhelp -_- looks like you cant even move anything if you try.\nBetter luck next time\n\n");
			}
			validChoice = false;
			while(!validChoice)
			{
				printf("Enter row number\n");
				row = checkInput();
				printf("Enter column number\n");
				column = checkInput();
				
				if(row < 0 || row > 5 || column > 7 || column < 0)
				{
					printf("The location you have entered is not a square on the board, try again\n");
					continue;
				}
				else if(board[row][column].stack == NULL)
				{
					printf("This square is empty, try again\n");
					continue;
				}
				else if(board[row][column].type == OBSTACLE)
				{
					puts("This token is stuck in an obstacle and cannot yet be moved");
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
				printf("\nWould you like to move up or down\n");
				printf("(1)Up\n(2)Down\n");
				direction = checkInput();
				switch(direction)
				{
					case 1: direction = -1;
						break;
					case 2: direction = 1;
						break;
					default: direction = 6;
						break;
				}
			
				if(row+direction > 5 || row+direction < 0)
					{
						printf("Cant move there, outside the board\n");
						continue;
					}
				else
					validChoice = true;
			}

			//moving the location of the token
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
			printf("%s has moved their piece from (%d,%d) to (%d,%d)\n", players[person].name, row, column, row+direction, column);
			print_board(board);
		}
		
		possible = false;
		//checking if the move is possible
		for(j=0;j<8;j++)
		{
			if(board[dice][j].stack != NULL)
			{
				if(board[dice][j].type != OBSTACLE)
				{
					possible = true;
				}
			}
		}
		
		validChoice = false;
		
		if(!possible)
		{
			printf("\n\nSorry no move can be made on that row :((\nBetter luck next time\n\n");
		}
		else
		{
			while(!validChoice)	
				{
					printf("\nPlease choose the location of token that you want to move forward\n");
					
					for(i=0;i<8;i++)
					{
						if(board[dice][i].stack != NULL && board[dice][i].type != OBSTACLE)
						{
							printf("(%d,%d)\n", dice, i);
						}
					}
					
					printf("Please enter the column number of the selected token\n");
					choice = checkInput();
					
					if(choice < 0 || choice > 7)
					{
						puts("ERROR INVALID INPUT :choice is not a square on the board\n");
					}
					else if(board[dice][choice].stack == NULL)
					{
						puts("ERROR INVALID INPUT :square chosen is empty\n");
					}
					else if(board[dice][choice].type == OBSTACLE)
					{
						puts("ERROR INVALID INPUT :square chosen is still an obstacle square\n");
					}
					else
					{
						validChoice = true;
					}
				}
				
					//moving the location of the token
				struct token *curr = board[dice][choice+1].stack;
				board[dice][choice+1].stack = malloc(sizeof(token));
				board[dice][choice+1].stack->col = board[dice][choice].stack->col;
				board[dice][choice+1].stack->next = curr;
				
				struct token *curre = board[dice][choice].stack;
				if(curre!=NULL)
				{
					board[dice][choice].stack = curre->next;
					free(curre);
				}
				
				if((choice+1) == 8) //Checking if the piece is being moved to the final column
				{
					for(i=0;i<numPlayers;i++)
					{
						if(players[i].col == board[dice][choice+1].stack->col) // If the player is moving his piece into the last column
						{
							players[i].numTokensLastCol += 1; // Incrementing the value for the number of tokens in the last colour for the relevant user
						}
						if(players[i].numTokensLastCol == 3)	//If the player has 3 tokens in the last column then the game is over and they win
						{
							person = i;      //sets the person variable to i, so that the proper winners name is printed at the end
							finished = true; // finishing the game if the user has 3 tokens in the last column
						}
					}
				}
				
				printf("%s has moved their piece from (%d,%d) to (%d,%d)\n", players[person].name, dice, choice, dice, choice+1);
				print_board(board);
		}
			
			if(!finished) //if the game is already finished then the rest of the current loop is skipped
			{
				//Iterating through the players
				if(person < numPlayers - 1)
				{
					person++;
				}
				else
				{
					person = 0;
				}
				
				/*This next loop updates the obstacle squares to type normal if there are no tokens in the columns behind them*/
				for(j=0;j<8;j++)	//iterates trough the columns, until there a column is not empty
				{
					check = true;
					for(i=0;i<6;i++) //iterates through the rows
					{
						if(board[i][j].type == OBSTACLE) //if the square type is an obstacle, change it to normal 
						{
							board[i][j].type = NORMAL;
						}
						if(board[i][j].stack != NULL) //if there is a token in the square
						{
							check = false;   //check bool is set to false
						}
					}
					
					if(!check) //If there is a token in the column currently indexed by j then the loop breaks 
					{
						break;
					}
				}
			}
	}	
	
	printf("*********************************************************************\n");
	printf("                          GAME OVER                                  \n");
	printf("                     PLAYER %d %s WINS!!!                            \n", person+1, players[person].name);
	printf("*********************************************************************\n");
	
}



/*pop
struct token *curr = board[4][0].stack;
if(curr!=NULL){
	board[4][0].stack = curr->next;
	
	free(curr);
}
print_board(board);	*/
