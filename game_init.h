/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newfile.h
 * Author: lpasqua
 *
 * Created on 06 March 2019, 12:18
 */

//number of rows of the board
#define NUM_ROWS 6
//number of columns of the board
#define NUM_COLUMNS 9




//types of squares
enum stype{
    NORMAL, OBSTACLE };

//colors of tokens
enum color {
    RED, BLUE, GREEN, YELLOW, PINK, ORANGE
};

//defines a token. 
//Note each token can be associated with a color
typedef struct token{
   enum color col; 
    //pointer to the next token on the stack
   struct token *next; 
}token;

//Defines a square of the board.
typedef struct square{
    //A square can be a NORMAL or an OBSTACLE square
     enum stype type;
     //the stack of tokens that can be placed on the board square
     token  * stack;
     //Number of tokens on this square
     int numTokens;   


}square;



/*
 * You need to fill this data structure
 * with the information about the player
 * such as a name and a color.
 */
typedef struct player{
     //The name of the player
    char name[10];
    //Colour of the player
    enum color col;

    int numTokensLastCol;
}player; 


/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]);

/*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 *
 */
int initialize_players(player players[]);

/*
*   This function allows the user to choose which colour they would 
*   Like their token to be
*
*   Input: the current player number(staring from 0), an array of the available colours, the player name
*   Output: The index of the chosen colour in the colours array
*/

int chooseColour(int currentPlayer, char colours[][7], char player[]);


/*
 * Checks to make sure integer input is valid and doesn't cause an infinite loop
 * 
 * Output: the user input
 */

int checkInput();



