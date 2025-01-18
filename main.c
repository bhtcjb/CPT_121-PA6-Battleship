/*****************************************************************
* Author: Blake Turman
* Class: CptS 121, Fall 2024; Section: 10L
* Programming Assignment: PA 6
* Last Updated: November 11, 2024
* Description: This program plays a virtual game of Battleship
*			   between the user and an enemy computer player.
*****************************************************************/
#include "Battleship.h"

int main(void)
{
	int mode = -1;

	// print rules
	print_rules();
	putchar('\n');
	system("pause");
	system("cls");

	// prompt difficulty options
	printf("Select Difficulty\n1. easy\n2. medium\n3. hard\n\n");
	do
	{
		printf("Enter Number: ");
		scanf("%d", &mode);
		if (mode != 1 && mode != 2 && mode != 3)
		{
			printf("Invalid Input X(\n");
		}

	} while (mode != 1 && mode != 2 && mode != 3);

	// play game
	system("cls");
	play_game(mode);

	return 0;
}