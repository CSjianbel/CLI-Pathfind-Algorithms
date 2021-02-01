#include <stdio.h>
#include <string.h>

#include "pathfind.h"
#include "board.h"

void err_args(char* extra_msg);

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 4)
	{
		err_args("");
		return 1;
	}
	
	bool pathing = true;
	char algorithm = 'a';
	char* filepath = argv[1];

	if (argc == 4)
	{
		if (strcmp("-d", argv[1]) && strcmp("-a", argv[1]))
		{	
			err_args("");
			return 1;
		}

		pathing = !strcmp("-d", argv[1]) ? true : false;

		if (strcmp(argv[2], "-a") && strcmp(argv[2], "-d") && strcmp(argv[2], "-b"))
		{
			err_args("");
			return 1;
		}

		if (!strcmp(argv[2], "-a"))
			algorithm = 'a';
		else if (!strcmp(argv[2], "-d"))
			algorithm = 'd';
		else if (!strcmp(argv[2], "-b"))
			algorithm = 'b';

		filepath = argv[3];
	} 
	else if (argc == 3)
	{
		if (strcmp("-d", argv[1]) && strcmp("-a", argv[1]))
		{	
			err_args("");
			return 1;
		}

		pathing = !strcmp("-d", argv[1]) ? true : false;
		filepath = argv[2];
	}

	FILE *test = fopen(filepath, "r");
	if (!test)
	{	
		err_args("Invalid structure filepath!");
		fclose(test);
		return 2;
	}
	fclose(test);

	int width = 0, height = 0;

	// Get the dimension of the given board
	if (!getDimension(filepath, &height, &width))
	{
		err_args("Invalid Board!");
		return 3;
	}

	printf("Height: %d - Width: %d\n", height, width);
	printf("Pathing: %s\n\n", pathing ? "Diagonal" : "Across");


	// Create a 2d array of given dimensions
	ListNode* board[height][width];
	// Keeps track of the start and end nodes
	ListNode* start = NULL;
	ListNode* goal = NULL;

	// Read the board into the array
	readBoard(filepath, height, width, board, &start, &goal, pathing);
	printBoard(height, width, board);

	if (findPath(height, width, board, start, goal, algorithm, pathing))
		printf("**********Solution Found!**********\n\n");
	else
		printf("**********No Solution Found!**********\n\n");

	printBoard(height, width, board);
	freeBoard(height, width, board);
}

void err_args(char* extra_msg)
{
	printf("%s\n", extra_msg);
	printf("Usage: pathfind [-a, -d]* [-a, -d, -b]* [struture.txt]\n");
}