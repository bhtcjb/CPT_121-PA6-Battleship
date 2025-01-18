/*****************************************************************
* Author: Blake Turman
* Class: CptS 121, Fall 2024; Section: 10L
* Programming Assignment: PA 6
* Last Updated: November 11, 2024
* Description: This program plays a virtual game of Battleship
*			   between the user and an enemy computer player.
*****************************************************************/
#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_ROWS 10
#define MAX_COLS 10

#define CARRIER 0
#define BATTLESHIP 1
#define CRUISER 2
#define SUBMARINE 3
#define DESTROYER 4

typedef struct stats {

	int hits;
	int misses;
	int shots;
	double hit_miss_ratio;
	int ships_sunk;
	int won_or_lost;

}Stats;


/**********************************************************
* Function: print_rules()
* Description: Prints rules to Battleship
* Input Parameters: none
* Output Parameters: none
* Returns: nothing
* Preconditions: includes standard header <stdio.h>
* ********************************************************/
void print_rules(void);

/**********************************************************
* Function: init_board()
* Description: Initializes board array with selected 
*			   symbol.
* Input Parameters: int row_size, int col_size, char symbol
* Output Parameters: char board[][MAX_COLS]
* Returns: nothing
* Preconditions: MAX_COLS is defined
* Credit: Made in lecture
* ********************************************************/
void init_board(char board[][MAX_COLS], int row_size, int col_size, char symbol);

/**********************************************************
* Function: check_random_placement()
* Description: Checks placement of randomly placed ship. 
*			   Returns 1 if valid and 0 if invalid.
* Input Parameters: char board[][MAX_COLS], int row_index, 
*				    int col_index, int right_or_down, 
*					int ship_size
* Output Parameters: none
* Returns: int
* Preconditions: MAX_COLS is defined
* ********************************************************/
int check_random_placement(char board[][MAX_COLS], int row_index, int col_index, int right_or_down, int ship_size);

/**********************************************************
* Function: place_single_ship()
* Description: Places a ship in board array based on 
*			   specifications.
* Input Parameters: int row_index, int col_index, 
*					int right_or_down, int ship_type
* Output Parameters: char board[][MAX_COLS]
* Returns: nothing
* Preconditions: placement must be valid
*			     MAX_COLS is defined
* ********************************************************/
void place_single_ship(char board[][MAX_COLS], int row_index, int col_index, int right_or_down, int ship_type);

/**********************************************************
* Function: place_single_ship()
* Description: Places all 5 ships in random valid positions
*			   to board array.
* Input Parameters: int row_index, int col_index,
*					int right_or_down, int ship_type
* Output Parameters: char board[][MAX_COLS]
* Returns: nothing
* Preconditions: assumes 5 standard ships in order from
*				 largest to smallest
*				 includes local header "Battleship.h"
*				 random seed must be set
* ********************************************************/
void place_ships_randomly(char board[][MAX_COLS], int row_size, int col_size);

/**********************************************************
* Function: prompt_manual_or_random()
* Description: Prompts user to input 'm' or 'r' and repeats 
*			   until valid input. Returns 1 if manual is 
*			   selected or 0 if random is selected.
* Input Parameters: none
* Output Parameters: none
* Returns: int
* Preconditions: includes standard header <stdio.h>
*				 includes standard header <ctype.h>
* ********************************************************/
int prompt_manual_or_random(void);

/**********************************************************
* Function: check_manual_placement()
* Description: Checks if array of cell indeces are valid
*			   for ship placement. Returns 1 if valid and 
*			   0 if invalid.
* Input Parameters: char board[][MAX_COLS], char col_arr[], 
*					int row_arr[], int size
* Output Parameters: none
* Returns: int
* Preconditions: MAX_COLS is defined
*				 includes standard header <ctype.h>
* ********************************************************/
int check_manual_placement(char board[][MAX_COLS], char col_arr[], int row_arr[], int size);

/**********************************************************
* Function: place_ships_manually()
* Description: Prints board and prompts user to input each 
*			   of the 5 ships repeating until valid input.
* Input Parameters: int row_size, int col_size
* Output Parameters: char board[][MAX_COLS]
* Returns: nothing
* Preconditions: assumes 5 standard ships
*				 includes local header "Battleship.h"
* ********************************************************/
void place_ships_manually(char board[][MAX_COLS], int row_size, int col_size);

/**********************************************************
* Function: coin_flip()
* Description: Prompts user to select 'h' or 't' repeating
*			   until valid input and flips a coin, 
*			   displaying if user won. Returns 1 if user
*			   won and 0 if user lost.
* Input Parameters: none
* Output Parameters: none
* Returns: int
* Preconditions: random seed must be set
*				 includes standard header <stdlib.h>
*				 includes standard header <stdio.h>
* ********************************************************/
int coin_flip(void);

/**********************************************************
* Function: guess_manually()
* Description: Prompts user for cell indeces repeating 
*			   until valid input and displays if hit or	
*			   miss and applies to board arrays. Also
*			   applys changes to stats.
* Input Parameters: int row_size, int col_size
* Output Parameters: char board[][MAX_COLS],
*					 char board_parallel[][MAX_COLS],
*					 Stats* player_stats, FILE* log
* Returns: nothing
* Preconditions: file stream must be open
*				 includes standard header <ctype.h>
*				 includes standard header <stdio.h>
* ********************************************************/
void guess_manually(char board[][MAX_COLS], char board_parallel[][MAX_COLS], int row_size, int col_size, Stats* player_stats, FILE* log);

/**********************************************************
* Function: guess_randomly()
* Description: Makes a random guess on board and displays
*			   if hit or miss and applies to stats.
* Input Parameters: int row_size, int col_size
* Output Parameters: char board[][MAX_COLS],
*					 Stats* player_stats, FILE* log
* Returns: nothing
* Preconditions: random seed must be set
*				 file stream must be open
*				 includes standard header <stdlib.h>
*				 includes standard header <stdio.h>
* ********************************************************/
void guess_randomly(char board[][MAX_COLS], int row_size, int col_size, Stats* player_stats, FILE* log);

/**********************************************************
* Function: guess_randomly_method()
* Description: Makes a random guess in a checkerboard
*			   pattern on board and displays if hit or miss
*			   and applies to stats.
* Input Parameters: int row_size, int col_size
* Output Parameters: char board[][MAX_COLS],
*					 Stats* player_stats, FILE* log
* Returns: nothing
* Preconditions: random seed must be set
*				 file stream must be open
*				 includes standard header <stdlib.h>
*				 includes standard header <stdio.h>
* ********************************************************/
void guess_randomly_method(char board[][MAX_COLS], int row_size, int col_size, Stats* player_stats, FILE* log);

/**********************************************************
* Function: check_if_done()
* Description: Checks if all ships of either player have 
*			   been sunk. Returns 1 if yes and 0 if no.
* Input Parameters: Stats p1_stats, Stats p2_stats
* Output Parameters: none
* Returns: int
* Preconditions: none
* ********************************************************/
int check_if_done(Stats p1_stats, Stats p2_stats);

/**********************************************************
* Function: determine_if_ship_sunk()
* Description: Checks if a specified ship has been sunk. 
*			   Returns 1 if yes and 0 if no.
* Input Parameters: char board[][MAX_COLS], int row_size, 
*					int col_size, char type
* Output Parameters: none
* Returns: int
* Preconditions: MAX_COLS is defined
* ********************************************************/
int determine_if_ship_sunk(char board[][MAX_COLS], int row_size, int col_size, char type);

/**********************************************************
* Function: find_number_sunk()
* Description: Places a 1 in ships_arr at each ship index
*			   if that ship is newly sunk. Returns the 
*			   total of the ships_arr.
* Input Parameters: char board[][MAX_COLS], int row_size,
*					int col_size
* Output Parameters: int ships_arr[]
* Returns: int
* Preconditions: assumes 5 standard ships
*				 includes local header "Battleship.h"
* ********************************************************/
int find_number_sunk(int ships_arr[5], char board[][MAX_COLS], int row_size, int col_size);

/**********************************************************
* Function: print_board()
* Description: Displays board array as a square.
* Input Parameters: char board[][MAX_COLS], int row_size, 
*				    int col_size
* Output Parameters: none
* Returns: nothing
* Preconditions: MAX_COLS is defined
*				 includes standard header <stdio.h>
* Credit: Made partially in lecture
* ********************************************************/
void print_board(char board[][MAX_COLS], int row_size, int col_size);

/**********************************************************
* Function: print_stats_to_log()
* Description: Prints all stats to log file.
* Input Parameters: Stats player_stats
* Output Parameters: FILE* output
* Returns: nothing
* Preconditions: file stream must be open
*				 includes standard header <stdio.h>
* ********************************************************/
void print_stats_to_log(FILE* output, Stats player_stats);

/**********************************************************
* Function: ai_med()
* Description: AI that guesses all cells immediatly 
*			   touching a hit (*) cell. If no hit cells are
*			   available for this then it will guess 
*			   randomly in a checkerboard pattern. Whether
*			   the guess was a hit or miss will be 
*			   displayed and stats will be adjusted.
* Input Parameters: int row_size, int col_size
* Output Parameters: char board[][MAX_COLS], 
*					 Stats* player_stats, FILE* log
* Returns: nothing
* Preconditions: file stream must be open
*				 includes local header "Battleship.h"
* ********************************************************/
void ai_med(char board[][MAX_COLS], int row_size, int col_size, Stats* player_stats, FILE* log);

/**********************************************************
* Function: ai_hard()
* Description: AI that guesses all cells where there are 
*			   ships.
* Input Parameters: int row_size, int col_size
* Output Parameters: char board[][MAX_COLS],
*					 Stats* player_stats, FILE* log
* Returns: nothing
* Preconditions: file stream must be open
*				 includes local header "Battleship.h"
* ********************************************************/
void ai_hard(char board[][MAX_COLS], int row_size, int col_size, Stats* player_stats, FILE* log);

/**********************************************************
* Function: play_game()
* Description: Plays a game of Battleship against ai based
*			   on input difficulty. 1 = easy, 2 = medium
*			   3 = hard.
* Input Parameters: int mode
* Output Parameters: 
* Returns: nothing
* Preconditions: includes local header "Battleship.h"
* ********************************************************/
void play_game(int mode);


#endif // !BATTLESHIP_H