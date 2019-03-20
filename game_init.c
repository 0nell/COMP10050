/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){
   
    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4) 
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL;
        }
    }
}
    
    
 /*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[])
{

    int i=0;
    int colour;
    int count;
	
    char colours[][7] = {{"RED"}, {"BLUE"}, {"GREEN"}, {"YELLOW"}, {"PINK"}, {"ORANGE"}}; 
    

    while(i< 6)
    {
        //Get user input of their name, o more than 10 characters for now
        printf("Player %d Please input your name: \n", i+1);
        fgets(players[i].name,10,stdin);
		
        //Checks whether a carriage return symbol was provided as input
        if(players[i].name[0] == '\n')
            break;
        
		//removes the newline at the end of the name input
		for(count=0;count<10;count++)
		{
			if(players[i].name[count] == '\n')
			{
				players[i].name[count] = '\0';
			}
		}

        //return the chosen colour into a variable
        colour = chooseColour(i, colours, players[i].name);

        //compare the chosen colour to the different options then assign the colour to the player's token
        if(strcmp(colours[colour], "RED") == 0)
            players[i].col = RED;
        else if (strcmp(colours[colour], "BLUE") == 0)
            players[i].col = BLUE;
        else if (strcmp(colours[colour], "GREEN") == 0)
            players[i].col = GREEN;
        else if (strcmp(colours[colour], "YELLOW") == 0)
            players[i].col = YELLOW;
        else if (strcmp(colours[colour], "PINK") == 0)
            players[i].col = PINK;
        else if (strcmp(colours[colour], "ORANGE") == 0) 
            players[i].col = ORANGE;
        else
            printf("Error has occured in assigning colour to player, %s\n", players[i].name);

        printf("%s has been chosen\n\n", colours[colour]);
                
        i++;
    }
    return i;

}


/*
*   This function allows the user to choose which colour they would 
*   Like their token to be
*
*   Input: the current player number(staring from 0), an array of the available colours, the player name
*   Output: The index of the chosen colour in the colours array
*/

int chooseColour(int currentPlayer, char colours[][7], char player[])
{
    //this function moves the unselected colour o the start of the array
    
    //int of the last selected colour
    static int colourIndex = -1;
    int i;
    int j = 0;
    bool valid = false;
    int numOfChoices = 6-currentPlayer;
   
    //Moving all unchosen colours to the front of the array
    for(i=0;i<6;i++)
    {
        //if the colour was selected las time the function was called, it is moved to the back of the array
        if(i != colourIndex)
        {
            strcpy(colours[j++], colours[i]);
        }
    }
    
    do
    {
        printf("\nPlease enter which number of the colour of token you want, %s\n", player);
        
        //Printing options of colours to the player.
        //Only the non chosen colours(at the front of the array) are printed
        for(i=0;i<numOfChoices;i++)
        {
            printf("(%d) %s\n", i+1, colours[i]);
        }
        
        scanf("%d", &colourIndex);
        //Checking for valid input
        if(colourIndex <= numOfChoices && colourIndex > 0)
        valid = true;
        else
            printf("Invalid input, pleae choose a colour that is on the screen\n");
    }
    while(!valid);
    fflush(stdin);
    //decremented because arrays start at 0
    colourIndex--;

    // return the index of the selected colour
    return colourIndex;
}
    
   


