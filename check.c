#include <stdio.h>
#include <stdbool.h>

int main(void)
{
	int choice;
	char c;
	char check[10];
	bool done = false;
	
	while(!done)
	{
	printf("please enter\n");
	fgets(check,9,stdin);
	
	printf("///////////////%c//////////", check[1]);
	c = check[0];
	
	choice = c - '0';
	printf("%c\n", c);
	printf("%d", choice);
	done = true;
	}
	return 0;
}