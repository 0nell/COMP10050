/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <string.h>


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
    int color;
    
    char colours[][7] = {{"RED"}, {"BLU"}, {"GREEN"}, {"YELLOW"}, {"PINK"}, {"ORANGE"}}; 
    

    while(i< 6)
    {
        //Get user input of their name, o more than 10 characters for now
        printf("Player %d Please input your name: \n", i+1);
        fgets(players[i].name,10,stdin);
        //Checks whether a carriage return symbol was provided as input
        if(players[i].name[0] == '\n')
            break;
        
        //return the chosen colour into a variable
        
        color = chooseColour(i, colours, players[i].name);
        
        //compare the chosen colour to the different options then assign the colour to the player's token
        if(strcmp(colours[color], "RED") == 0)
            players[i].col = RED;
        else if (strcmp(colours[color], "BLU") == 0)
            players[i].col = BLU;
        else if (strcmp(colours[color], "GREEN") == 0)
            players[i].col = GREEN;
        else if (strcmp(colours[color], "YELLOW") == 0)
            players[i].col = YELLOW;
        else if (strcmp(colours[color], "PINK") == 0)
            players[i].col = PINK;
        else if (strcmp(colours[color], "ORANGE") == 0) 
            players[i].col = ORANGE;

        printf("%s has been chosen\n", colours[color]);
                
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
    //Index of whether or not the colour has been selected. Static so changes are saved
    static int colourSelected[] = {0,0,0,0,0,0};
    static int colourIndex;
    int j;
    int i;
    int valid = 0;
    
    j=0;
   
    //Moving all unchosen colours to the front of the array
    for(i=0;i<6;i++)
    {
        if(!colourSelected[i])
        {
            strcpy(colours[j++], colours[i]);
        }
    }
    //resetting the chosen index because the list has been shuffled
    colourSelected[colourIndex] = 0;
    
    do
    {
    printf("Please enter which colour of token you want, %s", player);
    
    i=0;
    //Printing options of colours to the player.
    //Only the non chosen colours are printed
    for(i=0;i<6-currentPlayer;i++)
    {
        printf("%d for %s\n", i+1, colours[i]);
    }
    
    scanf("%d", &colourIndex);
    //Checking for valid input
    if(colourIndex <= 6-currentPlayer && colourIndex > 0)
       valid = 1;
    else
        printf("Invalid input, pleae choose a colour that is on the screen\n");
    }
    while(!valid);
    fflush(stdin);
    //decremented because arrays start at 0
    colourIndex--;
    //updating the chosen index
    colourSelected[colourIndex] = 1;
    

    return colourIndex;
}
    
   
     

