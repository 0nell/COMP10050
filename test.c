#include <stdio.h>
#include <string.h>
#include <stdbool.h>

 char players[6][10];
//This is a temporary file to test individual functions before pushing them. feel free to use
int chooseColour(int currentPlayer, char colours[][7]);

int main()
{
    int i=0;
    int color;
   
    char colours[][7] = {{"RED"}, {"BLU"}, {"GREEN"}, {"YELLOW"}, {"PINK"}, {"ORANGE"}}; 
    

    while(i< 6){
        //Get user input of their name, o more than 10 characters for now
        
        printf("Player %d Please input your name: \n", i+1);
        fgets(players[i] ,10,stdin);
        fflush(stdin);
        //Checks whether a carriage return symbol was provided as input
        if(players[i][0] == '\n')
            break;
        
        //Get user to input their token colour
        
        color = chooseColour(i, colours);
        printf("%s", colours[color]);
        printf("\n");
        
        i++;
    }
    return i;
}



int chooseColour(int currentPlayer, char colours[][7])
{

    static int colourIndex = -1;
    int j;
    int i;
    bool valid = false;
    
    j=0;
   
    for(i=0;i<6;i++)
    {
        if(i != colourIndex)
        {
            strcpy(colours[j++], colours[i]);
        }
    }
    
    
    do
    {
    printf("Please enter which colour of token you want, %s", players[currentPlayer]);
    
    for(i=0;i<6-currentPlayer;i++)
    {
        printf("%d for %s\n", i+1, colours[i]);
    }
    
    scanf("%d", &colourIndex);
    if(colourIndex <= 6-currentPlayer && colourIndex > 0)
       valid = true;
    else
        printf("Invalid input, pleae choose a colour that is on the screen\n");
    }
    while(!valid);
    fflush(stdin);
    colourIndex--;
  
    

    return colourIndex;
}
