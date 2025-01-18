/*****************************************************************
* Author: Blake Turman
* Class: CptS 121, Fall 2024; Section: 10L
* Programming Assignment: PA 6
* Last Updated: November 11, 2024
* Description: This program plays a virtual game of Battleship
*			   between the user and an enemy computer player.
*****************************************************************/
#include "Battleship.h"

void print_rules(void)
{
	printf("***** Welcome to Battleship! *****\n\n"
		"Rules of the Game:\n\n"
		"1. This is a two player game.\n"
		"2. Player One is you and Player Two is the computer.\n"
		"3. You will place your ships on your board and Player Two will do the same (you will not see the enemy's ship placement)\n"
		"4. Then you will flip a coin to see who goes first.\n"
		"5. Starting with the player that won the coin flip, you will each take turns guessing cells.\n"
		"6. If an enemy ship is hit, this will be called and marked on each player's enemy board with an '*'.\n"
		"7. If the guess does not hit a ship, this will be called and marked on each player's enemy board with a '0'.\n"
		"8. Once a ship is hit in all cells that it takes up, that ship is sunk and will be called.\n"
		"9. The player that sinks all 5 enemy ships wins!\n"
		"\nDifficulty Settings:\n easy - random ai\n medium - methodical ai\n hard - cheating ai\n");
}

void init_board(char board[][MAX_COLS], int row_size, int col_size, char symbol)
{
	int row_index = 0,
		col_index = 0;

	for (; row_index < row_size; ++row_index) // controls the row we're visiting
	{
		for (col_index = 0; col_index < col_size; ++col_index) // controls the column
		{
			board[row_index][col_index] = symbol;
		}
	}
}

int check_random_placement(char board[][MAX_COLS], int row_index, int col_index, int right_or_down, int ship_size)
{
	int check = 1,
		initial_row = row_index,
		initial_col = col_index;

	if (!right_or_down)
	{
		if (row_index + ship_size - 1 < MAX_ROWS)
		{
			for (; row_index < initial_row + ship_size; ++row_index)
			{
			
				if (board[row_index][col_index] != '~')
				{
					check = 0;
				}
			}
		}
		else
		{
			check = 0;
		}
	}
	else
	{
		if (col_index + ship_size - 1 < MAX_COLS)
		{
			for (; col_index < initial_col + ship_size; ++col_index)
			{
				if (board[row_index][col_index] != '~')
				{
					check = 0;
				}
			}
		}
		else
		{
			check = 0;
		}
	}

	return check;
}

void place_single_ship(char board[][MAX_COLS], int row_index, int col_index, int right_or_down, int ship_type)
{
	int initial_row = row_index,
		initial_col = col_index;

	if ((ship_type == CARRIER) && !right_or_down)
	{
		for (; row_index < initial_row + 5; ++row_index)
		{
			board[row_index][col_index] = 'c';
		}
	}
	else if ((ship_type == CARRIER) && right_or_down)
	{
		for (; col_index < initial_col + 5; ++col_index)
		{
			board[row_index][col_index] = 'c';
		}
	}

	else if ((ship_type == BATTLESHIP) && !right_or_down)
	{
		for (; row_index < initial_row + 4; ++row_index)
		{
			board[row_index][col_index] = 'b';
		}
	}
	else if ((ship_type == BATTLESHIP) && right_or_down)
	{
		for (; col_index < initial_col + 4; ++col_index)
		{
			board[row_index][col_index] = 'b';
		}
	}

	else if ((ship_type == CRUISER) && !right_or_down)
	{
		for (; row_index < initial_row + 3; ++row_index)
		{
			board[row_index][col_index] = 'r';
		}
	}
	else if ((ship_type == CRUISER) && right_or_down)
	{
		for (; col_index < initial_col + 3; ++col_index)
		{
			board[row_index][col_index] = 'r';
		}
	}

	else if ((ship_type == SUBMARINE) && !right_or_down)
	{
		for (; row_index < initial_row + 3; ++row_index)
		{
			board[row_index][col_index] = 's';
		}
	}
	else if ((ship_type == SUBMARINE) && right_or_down)
	{
		for (; col_index < initial_col + 3; ++col_index)
		{
			board[row_index][col_index] = 's';
		}
	}

	else if ((ship_type == DESTROYER) && !right_or_down)
	{
		for (; row_index < initial_row + 2; ++row_index)
		{
			board[row_index][col_index] = 'd';
		}
	}
	else if ((ship_type == DESTROYER) && right_or_down)
	{
		for (; col_index < initial_col + 2; ++col_index)
		{
			board[row_index][col_index] = 'd';
		}
	}
}

void place_ships_randomly(char board[][MAX_COLS], int row_size, int col_size)
{
	int row_or_column = -1,
		row_position = -1,
		col_position = -1,
		check = 0,
		ship_sizes[] = { 5, 4, 3, 3, 2 };

	

	for (int i = 0; i < 5; i++) {
		do
		{
			row_or_column = rand() % 2;
			row_position = rand() % row_size;
			col_position = rand() % col_size;

			check = check_random_placement(board, row_position, col_position, row_or_column, ship_sizes[i]);
		} while (check == 0);
		place_single_ship(board, row_position, col_position, row_or_column, i);
	}
}

int prompt_manual_or_random(void)
{
	char answer = '\0';
	int result = -1;
	do
	{
		printf("Would you like to place ships manually or randomly? m or r? ");
		scanf(" %c", &answer);
		answer = tolower((int)answer);
		if (answer != 'm' && answer != 'r')
		{
			printf("Invalid Input X(\n");
		}
	} while (answer != 'm' && answer != 'r');

	if (answer == 'm')
	{
		result = 1;
	}
	else
	{
		result = 0;
	}

	return result;
}

int check_manual_placement(char board[][MAX_COLS], char col_arr[], int row_arr[], int size)
{
	int check = 1,
		is_vertical = 0;

	// check if in bounds
	for (int i = 0; i < size && check == 1; ++i)
	{
		if (tolower(col_arr[i]) < 'a' || tolower(col_arr[i]) > 'j')
		{
			check = 0;
		}
		if (row_arr[i] < 1 || row_arr[i] > 10)
		{
			check = 0;
		}
		//check if space already taken
		if (board[row_arr[i] - 1][tolower(col_arr[i]) - 'a'] != '~')
		{
			check = 0;
		}
	}
	// check if not vertical or horizontal
	for (int i = 1; i < size && check == 1; ++i)
	{
		if (tolower(col_arr[i]) != tolower(col_arr[i - 1]) && row_arr[i] != row_arr[i - 1])
		{
			check = 0;
		}
	}

	// set to 1 if vertical
	if (tolower(col_arr[0]) == tolower(col_arr[1]))
	{
		is_vertical = 1;
	}


	for (int i = 0; i < size && check == 1; ++i)
	{
		for (int j = 0; j < size && check == 1; ++j)
		{
			//check if has spaces
			if (tolower(col_arr[i]) - tolower(col_arr[j]) >= size || tolower(col_arr[i]) - tolower(col_arr[j]) <= size * -1)
			{
				check = 0;
			}
			if (row_arr[i] - row_arr[j] >= size || row_arr[i] - row_arr[j] <= size * -1)
			{
				check = 0;
			}
			//check if same cell is inputted twice
			if (is_vertical && i != j && row_arr[i] == row_arr[j])
			{
				check = 0;
			}
			if (!is_vertical && i != j && tolower(col_arr[i]) == tolower(col_arr[j]))
			{
				check = 0;
			}
		}
	}

	
	return check;
}

void place_ships_manually(char board[][MAX_COLS], int row_size, int col_size)
{
	int check = 0,
		row_arr[5] = { 0 };
	char col_arr[5] = { '\0' };

	system("cls");
	print_board(board, row_size, col_size);
	printf("\nCarrier (5 cells)\n");
		do
		{
			printf("\nPlease enter the letter then number of each cell seperated by a space then press enter\n");
			printf("-Do not enter more cells than length of ship\n");
			
			for (int i = 0; i < 5; ++i)
			{
				scanf(" %c", &col_arr[i]);
				scanf("%d", &row_arr[i]);
			}
			
			check = check_manual_placement(board, col_arr, row_arr, 5);
			if (!check)
			{
				printf("\nInvalid Inputs X(");
			}

		} while (!check);
		for (int i = 0; i < 5; ++i)
		{
			board[row_arr[i] - 1][tolower(col_arr[i]) - 'a'] = 'c';
		}

		
	
		system("cls");
		print_board(board, row_size, col_size);
	
		printf("\nBattleship (4 cells)\n");
		do
		{
			printf("\nPlease enter the letter then number of each cell seperated by a space then press enter\n");
			printf("-Do not enter more cells than length of ship\n");

			for (int i = 0; i < 4; ++i)
			{
				scanf(" %c", &col_arr[i]);
				scanf("%d", &row_arr[i]);
			}

			check = check_manual_placement(board, col_arr, row_arr, 4);
			if (!check)
			{
				printf("\nInvalid Inputs X(");
			}

		} while (!check);
		for (int i = 0; i < 4; ++i)
		{
			board[row_arr[i] - 1][tolower(col_arr[i]) - 'a'] = 'b';
		}

		system("cls");
		print_board(board, row_size, col_size);

		printf("\nCruiser (3 cells)\n");
		do
		{
			printf("\nPlease enter the letter then number of each cell seperated by a space then press enter\n");
			printf("-Do not enter more cells than length of ship\n");

			for (int i = 0; i < 3; ++i)
			{
				scanf(" %c", &col_arr[i]);
				scanf("%d", &row_arr[i]);
			}

			check = check_manual_placement(board, col_arr, row_arr, 3);
			if (!check)
			{
				printf("\nInvalid Inputs X(");
			}

		} while (!check);
		for (int i = 0; i < 3; ++i)
		{
			board[row_arr[i] - 1][tolower(col_arr[i]) - 'a'] = 'r';
		}
	
		system("cls");
		print_board(board, row_size, col_size);
	
		printf("\nSubmarine (3 cells)\n");
		do
		{
			printf("\nPlease enter the letter then number of each cell seperated by a space then press enter\n");
			printf("-Do not enter more cells than length of ship\n");

			for (int i = 0; i < 3; ++i)
			{
				scanf(" %c", &col_arr[i]);
				scanf("%d", &row_arr[i]);
			}

			check = check_manual_placement(board, col_arr, row_arr, 3);
			if (!check)
			{
				printf("\nInvalid Inputs X(");
			}

		} while (!check);
		for (int i = 0; i < 3; ++i)
		{
			board[row_arr[i] - 1][tolower(col_arr[i]) - 'a'] = 's';
		}
	
		system("cls");
		print_board(board, row_size, col_size);
	
		printf("\nDestroyer (2 cells)\n");
		do
		{
			printf("\nPlease enter the letter then number of each cell seperated by a space then press enter\n");
			printf("-Do not enter more cells than length of ship\n");

			for (int i = 0; i < 2; ++i)
			{
				scanf(" %c", &col_arr[i]);
				scanf("%d", &row_arr[i]);
			}

			check = check_manual_placement(board, col_arr, row_arr, 2);
			if (!check)
			{
				printf("\nInvalid Inputs X(");
			}

		} while (!check);
		for (int i = 0; i < 2; ++i)
		{
			board[row_arr[i] - 1][tolower(col_arr[i]) - 'a'] = 'd';
		}
	
		system("cls");
		print_board(board, row_size, col_size);
		system("pause");

}

int coin_flip(void)
{
	char answer = '\0';
	int coin = rand() % 2;

	do
	{
		printf("Heads or Tails? h or t? ");
		scanf(" %c", &answer);
		answer = tolower((int)answer);
		if (answer != 'h' && answer != 't')
		{
			printf("Invalid Input X(\n");
		}

	} while (answer != 'h' && answer != 't');

	if (coin == 1 && answer == 'h')
	{
		printf("Heads!\n\nYou Win!\n");
	}
	else if (coin == 0 && answer == 'h')
	{
		printf("Tails!\n\nYou Lose!\n");
	}
	else if (coin == 1 && answer == 't')
	{
		printf("Tails!\n\nYou Win!\n");
	}
	else
	{
		printf("Heads!\n\nYou Lose!\n");
	}

	return coin;
}

void guess_manually(char board[][MAX_COLS], char board_parallel[][MAX_COLS],int row_size, int col_size, Stats *player_stats, FILE* log)
{
	int row_guess = -1,
		col_guess_int = -1;
	char col_guess = -1;

	do
	{
		printf("Please make a guess. letter and number: ");
		scanf(" %c", &col_guess);
		scanf("%d", &row_guess);
		col_guess_int = tolower((int)col_guess) - (int)'a';
		--row_guess;

		if (board_parallel[row_guess][col_guess_int] == '0' || board_parallel[row_guess][col_guess_int] == '*' ||
			col_guess_int < 0 || col_guess_int >= col_size || row_guess < 0 || row_guess >= row_size)
		{
			printf("Invalid Input X(\n");
		}
	} while (board_parallel[row_guess][col_guess_int] == '0' || board_parallel[row_guess][col_guess_int] == '*' ||
		col_guess_int < 0 || col_guess_int >= col_size || row_guess < 0 || row_guess >= row_size);
	system("cls");
	printf("Player One Guessed %c%d\n", toupper(col_guess), row_guess + 1);
	fprintf(log, "Player One Guessed %c%d.\n", toupper((int)col_guess), row_guess + 1);

	if (board[row_guess][col_guess_int] == '~')
	{
		printf("Miss!\n");
		fprintf(log, "Miss!\n");
		board[row_guess][col_guess_int] = '0';
		board_parallel[row_guess][col_guess_int] = '0';
		++player_stats->misses;
	}
	else
	{
		printf("Hit!\n");
		fprintf(log, "Hit!\n");
		board[row_guess][col_guess_int] = '*';
		board_parallel[row_guess][col_guess_int] = '*';
		++player_stats->hits;
	}
}

void guess_randomly(char board[][MAX_COLS],int row_size, int col_size, Stats* player_stats, FILE* log)
{
	int row_guess = -1,
		col_guess = -1;

	do
	{
		row_guess = rand() % row_size;
		col_guess = rand() % col_size;
	} while (board[row_guess][col_guess] == '0' || board[row_guess][col_guess] == '*');
	system("cls");
	printf("Player Two Guessed %c%d\n", (char) (col_guess + 'A'), row_guess + 1);
	fprintf(log, "Player Two Guessed %c%d\n", (char)(col_guess + 'A'), row_guess + 1);

	if (board[row_guess][col_guess] == '~')
	{
		printf("Miss!\n");
		fprintf(log, "Miss!\n");
		board[row_guess][col_guess] = '0';
		++player_stats->misses;
	}
	else
	{
		printf("Hit!\n");
		fprintf(log, "Hit!\n");
		board[row_guess][col_guess] = '*';
		++player_stats->hits;
	}
}

void guess_randomly_method(char board[][MAX_COLS], int row_size, int col_size, Stats* player_stats, FILE* log)
{
	int row_guess = -1,
		col_guess = -1;

	do
	{
		row_guess = rand() % row_size;
		if (row_guess % 2 == 1)
		{
			col_guess = 2 * (rand() % (col_size / 2));
		}
		else
		{
			col_guess = (2 * (rand() % (col_size / 2)) + 1);
		}
	} while (board[row_guess][col_guess] == '0' || board[row_guess][col_guess] == '*');
	system("cls");
	printf("Player Two Guessed %c%d\n", (char)(col_guess + 'A'), row_guess + 1);
	fprintf(log, "Player Two Guessed %c%d\n", (char)(col_guess + 'A'), row_guess + 1);

	if (board[row_guess][col_guess] == '~')
	{
		printf("Miss!\n");
		fprintf(log, "Miss!\n");
		board[row_guess][col_guess] = '0';
		++player_stats->misses;
	}
	else
	{
		printf("Hit!\n");
		fprintf(log, "Hit!\n");
		board[row_guess][col_guess] = '*';
		++player_stats->hits;
	}
}

int check_if_done(Stats p1_stats, Stats p2_stats)
{
	int check = 0;
	if (p1_stats.ships_sunk == 5 || p2_stats.ships_sunk == 5)
	{
		check = 1;
	}
	return check;
}

int determine_if_ship_sunk(char board[][MAX_COLS], int row_size, int col_size, char type)
{
	int check = 0,
		count = 0;

	for (int i = 0; i < row_size; ++i)
	{
		for (int j = 0; j < col_size; ++j)
		{
			if (board[i][j] == type)
			{
				++count;
			}
		}
	}

	if (count == 0)
	{
		check = 1;
	}
	return check;
}

int find_number_sunk(int ships_arr[5], char board[][MAX_COLS], int row_size, int col_size)
{
	int number_ships = 0;
	if (!ships_arr[CARRIER])
	{
		ships_arr[CARRIER] = determine_if_ship_sunk(board, row_size, col_size, 'c');
	}
	if (!ships_arr[BATTLESHIP])
	{
		ships_arr[BATTLESHIP] = determine_if_ship_sunk(board, row_size, col_size, 'b');
	}
	if (!ships_arr[CRUISER])
	{
		ships_arr[CRUISER] = determine_if_ship_sunk(board, row_size, col_size, 'r');
	}
	if (!ships_arr[SUBMARINE])
	{
		ships_arr[SUBMARINE] = determine_if_ship_sunk(board, row_size, col_size, 's');
	}
	if (!ships_arr[DESTROYER])
	{
		ships_arr[DESTROYER] = determine_if_ship_sunk(board, row_size, col_size, 'd');
	}

	for (int i = 0; i < 5; ++i)
	{
		number_ships += ships_arr[i];
	}

	return number_ships;
}

void print_board(char board[][MAX_COLS], int row_size, int col_size)
{
	int row_index = 0,
		col_index = 0;

	printf("\033[0;36m%4c%2c%2c%2c%2c%2c%2c%2c%2c%2c\n", 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J');
	for (; row_index < row_size; ++row_index) // controls the row we're visiting
	{
		printf("\033[0;36m%2d ", row_index+1);
		for (col_index = 0; col_index < col_size; ++col_index) // controls the column
		{
			if (board[row_index][col_index] == '~')
			{
				printf("\033[0;34m%-2c", board[row_index][col_index]);
			}
			else if (board[row_index][col_index] == '0')
			{ 
				printf("\033[0;37m%-2c", board[row_index][col_index]);
			}
			else if (board[row_index][col_index] == '*')
			{
				printf("\033[0;31m%-2c", board[row_index][col_index]);
			}
			else
			{
				printf("\033[0;35m%-2c", board[row_index][col_index]);
			}
		}
		printf("\033[0;37m\n");
		//putchar('\n');
	}
}

void print_stats_to_log(FILE* output, Stats player_stats)
{
	fprintf(output, "Hits\t\t\t%3d\n", player_stats.hits);
	fprintf(output, "Misses\t\t\t%3d\n", player_stats.misses);
	fprintf(output, "Shots\t\t\t%3d\n", player_stats.shots);
	fprintf(output, "Hit/Miss Ratio\t%5.2lf%%\n", player_stats.hit_miss_ratio);
	fprintf(output, "Ships Sunk\t\t%3d\n", player_stats.ships_sunk);
	fprintf(output, "Winner?\t\t\t%3d\n", player_stats.won_or_lost);
}

void ai_med(char board[][MAX_COLS], int row_size, int col_size, Stats* player_stats, FILE* log)
{
	int check = 1,
		col_guess = 0,
		row_guess = 0;

	if (player_stats->hits == 0)
	{
		guess_randomly_method(board, row_size, col_size, player_stats, log);
	}
	else
	{
		for (int i = 0; i < row_size; ++i)
		{
			for (int j = 0; j < col_size; ++j)
			{
				if (board[i][j] == '*')
				{
					if (i + 1 < row_size && board[i + 1][j] != '*' && board[i + 1][j] != '0')
					{
						row_guess = i + 1;
						col_guess = j;
						j = col_size;
						i = row_size;
						check = 0;
					}
					else if (i - 1 >= 0 && board[i - 1][j] != '*' && board[i - 1][j] != '0')
					{
						row_guess = i - 1;
						col_guess = j;
						j = col_size;
						i = row_size;
						check = 0;
					}
					else if (j + 1 < col_size && board[i][j + 1] != '*' && board[i][j + 1] != '0')
					{
						row_guess = i;
						col_guess = j + 1;
						j = col_size;
						i = row_size;
						check = 0;
					}
					else if (j - 1 >= 0 && board[i][j - 1] != '*' && board[i][j - 1] != '0')
					{
						row_guess = i;
						col_guess = j - 1;
						j = col_size;
						i = row_size;
						check = 0;
					}
				}
			}
		}
		if (check)
		{
			guess_randomly_method(board, row_size, col_size, player_stats, log);
		}
		else
		{
			system("cls");
			printf("Player Two Guessed %c%d\n", (char)(col_guess + 'A'), row_guess + 1);
			fprintf(log, "Player Two Guessed %c%d\n", (char)(col_guess + 'A'), row_guess + 1);

			if (board[row_guess][col_guess] == '~')
			{
				printf("Miss!\n");
				fprintf(log, "Miss!\n");
				board[row_guess][col_guess] = '0';
				++player_stats->misses;
			}
			else
			{
				printf("Hit!\n");
				fprintf(log, "Hit!\n");
				board[row_guess][col_guess] = '*';
				++player_stats->hits;
			}
		}
	}

	
}

void ai_hard(char board[][MAX_COLS], int row_size, int col_size, Stats* player_stats, FILE* log)
{
	for (int i = 0; i < row_size; ++i)
	{
		for (int j = 0; j < col_size; ++j)
		{
			if (board[i][j] == 'c' || board[i][j] == 'b' || board[i][j] == 'r' || board[i][j] == 's' || board[i][j] == 'd')
			{
				system("cls");
				printf("Player Two Guessed %c%d\n", (char)(j + 'A'), i + 1);
				fprintf(log, "Player Two Guessed %c%d\n", (char)(j + 'A'), i + 1);
				printf("Hit!\n");
				fprintf(log, "Hit!\n");
				board[i][j] = '*';
				++player_stats->hits;

				i = row_size;
				j = col_size;
			}
		}
	}

}

void play_game(int mode)
{
	char p1_board[MAX_ROWS][MAX_COLS],
		p2_board[MAX_ROWS][MAX_COLS],
		enemy_board[MAX_ROWS][MAX_COLS];
	int player_flag = 0,
		p1_sunk_ships[5] = { 0 },
		p2_sunk_ships[5] = { 0 },
		sunk_ships_flag = 0;
	FILE* log = fopen("battleship.log", "w");
	Stats p1_stats = { 0,0,0,0,0,-1 },
		p2_stats = { 0,0,0,0,0,-1 };

	srand((unsigned int)time(NULL));

	
	
	//init boards
	init_board(p1_board, MAX_ROWS, MAX_COLS, '~');
	init_board(p2_board, MAX_ROWS, MAX_COLS, '~');
	init_board(enemy_board, MAX_ROWS, MAX_COLS, '~');

	

	//place ships
	if (prompt_manual_or_random())
	{
		place_ships_manually(p1_board, MAX_ROWS, MAX_COLS);
	}
	else
	{
		place_ships_randomly(p1_board, MAX_ROWS, MAX_COLS);
	}

	place_ships_randomly(p2_board, MAX_ROWS, MAX_COLS);
	
	system("cls");

	//select who goes first
	player_flag = coin_flip();
	system("pause");
	system("cls");

	//players take turns
	while (!check_if_done(p1_stats, p2_stats))
	{
		//player 1 goes
		if (player_flag == 1)
		{
			printf("Player One's Turn:\n\n");
			printf("Enemy Board:\n");
			print_board(enemy_board, MAX_ROWS, MAX_COLS);
			printf("\nYour Board:\n");
			print_board(p1_board, MAX_ROWS, MAX_COLS);
			putchar('\n');
			guess_manually(p2_board, enemy_board, MAX_ROWS, MAX_COLS, &p1_stats, log);

			printf("Enemy Board:\n");
			print_board(enemy_board, MAX_ROWS, MAX_COLS);
			printf("\nYour Board:\n");
			print_board(p1_board, MAX_ROWS, MAX_COLS);
			putchar('\n');
			system("pause");
			system("cls");

			++p1_stats.shots;
			p1_stats.ships_sunk = find_number_sunk(p2_sunk_ships, p2_board, MAX_ROWS, MAX_COLS);
			p1_stats.hit_miss_ratio = ((double)p1_stats.hits / (p1_stats.misses + (p1_stats.misses == 0))) * 100;

			if (sunk_ships_flag != p1_stats.ships_sunk + p2_stats.ships_sunk)
			{
				printf("SHIP SUNK!\n\n");
				fprintf(log, "SHIP SUNK!\n");
				sunk_ships_flag = p1_stats.ships_sunk + p2_stats.ships_sunk;
				system("pause");
				system("cls");
			}

			player_flag = 0;
		}
		//player 2 goes
		else
		{
			printf("Player Two's Turn:\n\n");
			printf("Enemy Board:\n");
			print_board(enemy_board, MAX_ROWS, MAX_COLS);
			printf("\nYour Board:\n");
			print_board(p1_board, MAX_ROWS, MAX_COLS);
			putchar('\n');
			system("pause");

			system("cls");
			if (mode == 1)
			{
				guess_randomly(p1_board, MAX_ROWS, MAX_COLS, &p2_stats, log);
			}
			else if (mode == 2)
			{
				ai_med(p1_board, MAX_ROWS, MAX_COLS, &p2_stats, log);
			}
			else
			{
				ai_hard(p1_board, MAX_ROWS, MAX_COLS, &p2_stats, log);
			}
			printf("Enemy Board:\n");
			print_board(enemy_board, MAX_ROWS, MAX_COLS);
			printf("\nYour Board:\n");
			print_board(p1_board, MAX_ROWS, MAX_COLS);
			putchar('\n');
			system("pause");
			system("cls");

			++p2_stats.shots;
			p2_stats.ships_sunk = find_number_sunk(p1_sunk_ships, p1_board, MAX_ROWS, MAX_COLS);
			p2_stats.hit_miss_ratio = ((double)p2_stats.hits / (p2_stats.misses + (p2_stats.misses == 0))) * 100;

			if (sunk_ships_flag != p1_stats.ships_sunk + p2_stats.ships_sunk)
			{
				printf("SHIP SUNK!\n\n");
				fprintf(log, "SHIP SUNK!\n");
				sunk_ships_flag = p1_stats.ships_sunk + p2_stats.ships_sunk;
				system("pause");
				system("cls");
			}

			player_flag = 1;
		}
	}

	//display winner
	p1_stats.won_or_lost = (p1_stats.ships_sunk > p2_stats.ships_sunk);
	p2_stats.won_or_lost = (p2_stats.ships_sunk > p1_stats.ships_sunk);

	if (p1_stats.won_or_lost)
	{
		printf("Player One Wins!\n\n");
		fprintf(log, "Player One Wins!\n\n");
	}
	else
	{
		printf("Player Two Wins!\n\n");
		fprintf(log, "Player Two Wins!\n\n");
	}
	system("pause");
	system("cls");
	printf("Final Boards:\n");
	printf("\nPlayer One's Board:\n");
	print_board(p1_board, MAX_ROWS, MAX_COLS);
	printf("\nPlayer Two's Board:\n");
	print_board(p2_board, MAX_ROWS, MAX_COLS);
	putchar('\n');
	system("pause");
	system("cls");

	//print stats
	fprintf(log, "\nPlayer One Stats:\n");
	print_stats_to_log(log, p1_stats);
	fprintf(log, "\nPlayer Two Stats:\n");
	print_stats_to_log(log, p2_stats);

	fclose(log);
}
