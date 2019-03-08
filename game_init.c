/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>


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
    int colourSelected[] = {0,0,0,0,0,0};
    char colours[][6] = {{"RED"}, {"BLU"}, {"GREEN"}, {"YELLOW"}, {"PINK"}, {"ORANGE"}};

    while(i< 6){
        //Get user input of their name, o more than 10 characters for now
        printf("Player %d Please input your name: \n", i+1);
        fgets(players[i].name,10,stdin);
        //Checks whether a carriage return symbol was provided as input
        if(players[i].name[0] == '\n')
            break;
        
        //Get user to input their token colour
        printf("%s Please enter which colour of token you want", players[i].name);
        for(i=0;i<6;i++)
        {
            if(!colourSelected)
                printf(" %d for %s", i+1, colours[i]);
        }
        scanf("%d",&color);
        switch(color)
        {
            case 1: players[i].col = RED;
                colourSelected[0] = 1;
                break;
            case 2: players[i].col = BLU;
                colourSelected[1] = 1;
                break;
            case 3: players[i].col = GREEN;
                colourSelected[2] = 1;
                break;
            case 4: players[i].col = YELLOW;
                colourSelected[3] = 1;
                break;
            case 5: players[i].col = PINK;
                colourSelected[4] = 1;
                break;
            case 6: players[i].col = ORANGE;
                colourSelected[5] = 1;
                break;
            default: break;
        }
        
        i++;
    }
    return i;

}
    
   
     

