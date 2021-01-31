#include <stdio.h>
#include "pathfind.h"

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 4)
	{
		printf("Usage: pathfind [-a, -d] [-a, -d, -b] [struture.txt]\n");
		return 1;
	}
	
	bool pathing = true;
	char algorithm = 'a';
	char* filepath = argv[1];

	if (argc == 4)
	{
		if (strcmp("-d", argv[1]) && strcmp("-a", argv[1]))
		{	
			printf("Usage: pathfind [-a, -d] [-a, -d, -b] [struture.txt]\n");
			return 1;
		}

		pathing = !strcmp("-d", argv[1]) ? true : false;

		if (strcmp(argv[2], "-a") && strcmp(argv[2], "-d") && strcmp(argv[2], "-b"))
		{
			printf("Usage: pathfind [-a, -d] [-a, -d, -b] [struture.txt]\n");
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
			printf("Usage: pathfind [-a, -d] [-a, -d, -b] [struture.txt]\n");
			return 1;
		}

		pathing = !strcmp("-d", argv[1]) ? true : false;
		filepath = argv[2];
	}

	FILE *test = fopen(filepath, "r");
	if (!test)
	{	
		printf("Invalid structure filepath!\n\n");
		printf("Usage: pathfind [-a, -d] [-a, -d, -b] [struture.txt]\n");
		return 2;
	}
	fclose(test);

	int width = 0, height = 0;

	// Get the dimension of the given board
	if (!getDimension(filepath, &height, &width))
	{
		printf("Invalid Board!\n\n");
		printf("Usage: pathfind [-a, -d] [-a, -d, -b] [struture.txt]\n");
		return 3;
	}

	printf("Height: %d - Width: %d\n", height, width);
	printf("Pathing: %s\n\n", pathing ? "Diagonal" : "Across");


	// Create a 2d array of given dimensions
	ListNode* board[height][width];
	ListNode* start = NULL;
	ListNode* goal = NULL;

	// Read the board into the array
	readBoard(filepath, height, width, board, &start, &goal, pathing);
	printBoard(height, width, board);
	printf("\n\n");
	
	if (algorithm == 'a')
		printf("A* Search\n\n");
	else if (algorithm == 'd')
		printf("Depth First Search\n\n");
	else
		printf("Breadth First Search\n\n");

	if (findPath(height, width, board, start, goal, algorithm, pathing))
	{
		printf("**********Solution Found!**********\n\n");
		printBoard(height, width, board);
	}
	else
	{
		printf("**********No Solution Found!**********\n\n");
		printBoard(height, width, board);
	}

	freeBoard(height, width, board);
	printf("Board Successfully Free'd!\n");
}
