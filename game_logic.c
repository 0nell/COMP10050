/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <stdbool.h>

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
	int taken[6] = {0,0,0,0,0,0};		//value set to 0 if that point on the level is free and 1 if it is taken
	int previous[6];			//value in the locations previous[0-5] correspond to rows 0-5 and contain the colourindex previosuly placed in that row
	int choice, i;				//choice contains the users choice of row to place their token, i is used as a counter
	bool valid = false;			//valid checks whether a choice is valid and on the list
	bool reset = false;			//reset resets the taken array after the level becomes full
	char colours[][7] = {{"RED"}, {"BLUE"}, {"GREEN"}, {"YELLOW"}, {"PINK"}, {"ORANGE"}}; //colours corresponding to colourindex
	token * storage[6][4];	//VERY IMPORTANT, THIS STORES THE STACKS OF TOKENS (TOKEN POINTERS)
	char a;	//USED TO PRINT THE TOKENS IN THE DEBUG PROCESS
	int complete = 0; //THE AMOUNT OF COMPLETE LEVELS OF TOKENS
	
	for(tokens_placed=0;tokens_placed < 4;tokens_placed++)  	//iterates through the tokens placed (4 times)
	{
		for(person=0;person<numPlayers;person++)	//iterates through the players
		{
			printf("Please enter the number row you would like to place your token in %s\n", players[person].name);
			valid = false;	//resets valid bool to false
			
			while(!valid)	//iterates until a valid choice is given
			{
				int full = 0;	//used to check whether taken[] contais all 1's
				reset = false;	//resets reset bool to false
				
				for(i=0;i<6;i++)	//iterates through taken[]
				{
					if(taken[i] == 1) //each time 1 is the value, full iterates
					{
						full++;
					}
				}
				
				if(full == 6) //if every value in taken[] is 1
				{
					complete++; //AMOUNT OF COMPLETE LEVELS ITERATED BY 1
					reset = true; //reset is set to true
				}
				
				for(i=0;i<6;i++) //iterates through taken[]
				{
					if(reset) //if reset is set to true
					{
						taken[i] = 0; //each value in taken is set to 0
					}
					
					if(taken[i] == 0 && previous[i] != players[person].tkn.col) //if the value at that level is free and the previous token is not of the same colour
					{
						printf("(%d) ROW %d\n", i, i); //prints the rows which can be chosen
					}
				}
				
				scanf("%d", &choice); //takes input of  the users choice
				
				if(choice < 0 || choice > 6 || taken[choice] == 1) //if the choice is invalid
				{
					printf("Choice is not valid, please enter a number shown above\n");
				}
				else if(previous[choice] == players[person].tkn.col) //if the choice points to a location where the previous is the same as the user who is currently choosing's token
				{
					printf("You cannot place a token there as the previous token is the same colour\n");
				}
				else //valid choice
				{
					printf("%s token placed in row %d\n", colours[players[person].tkn.col], choice); //tells user which row/colour it was placed in
					taken[choice] = 1;		//taken array at that location set to 1, at current level this spacce is now taken
					previous[choice] = players[person].tkn.col;		//sets the previous array at that location to the colourindex of the token placed there
					
					if(board[choice][0].stack == NULL)
					{
						printf("1\n"); //THIS WAS JUST T SEE WHICH OPTION WAS RUN IN THE DEBUG PROCESS
						board[choice][0].stack = &players[person].tkn; //ITEM SHOWN IN THE BOARD POINTER IS SET TO THE TOKEN OF THE PLAYER WHO CHOSE IT
						storage[choice][0] = &players[person].tkn; //TOKEN ADDED TO THE BOTTOM OF THE STACK
					}
					
					else if(board[choice][0].stack != NULL)
					{
						printf("2\n");   //THIS WAS JUST TO SEE WHICH OPTION WAS RUN IN THE DEBUG PROCESS
						
						for(i=complete;i>0;i--) //MOVES THE ITEMS IN THE STACK UP ONE FOR A NEW THING TO BE PUSHED AT THE BOTTOM
						{
							storage[choice][i] = storage[choice][i-1]; 
						}
						
						board[choice][0].stack = &players[person].tkn; //ITEM SHOWN IN THE BOARD POINTER IS SET TO THE TOKEN OF THE PLAYER WHO CHOSE IT
						storage[choice][0] = &players[person].tkn;	   //TOKEN ADDED TO THE BOTTOM OF THE STACK
						
						for(i=0;i<complete+1;i++)					//SIMPLY DESIGN DEBUG FEATURE TO VIEW THE STACK AFTER PLACEMENT OF NEW TOKEN
						{
							a = print_token(storage[choice][i]);
							printf("%c\n", a);
						}
					}
					/******************************************************************************************************************
							ASK ABOUT THE NO CHOICE BUT TO STACK GREEN ON GREEN BASIC DESIGN FLAW OF THE GAME
					*******************************************************************************************************************/
					print_board(board);	//PRINTS THE BOARD SO PLAYER CAN VIEW IT
					valid = true;			//exits loop as valid choice entered
				}
			}
		}
	}
}	


/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    //TO BE IMPLEMENTED
}



