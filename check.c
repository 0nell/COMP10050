#include <stdio.h>

int main(void)
{
	int choice;
	char c;
	char check[10];
	printf("please enter\n");
	fgets(check,9,stdin);
	
	c = check[0];
	
	choice = c - '0';
	printf("%c\n", c);
	printf("%d", choice);
	return 0;
}