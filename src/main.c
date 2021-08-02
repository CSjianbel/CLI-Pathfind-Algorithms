#include <stdio.h>
#include <string.h>

#include "./Pathfind/pathfind.h"
#include "./Board/board.h"

void verifyArgs(int argc, char **argv, bool* pathing, char* algorithm, char** filepath);
void err_args(char* extra_msg);

int main(int argc, char **argv)
{
	/*
	 * Default values:
	 * 	pathing: true = diagonal 
	 * 	algorithm: 'a' = Astar
	 */
	bool pathing = true;
	char algorithm = 'a';
	char* filepath = argv[1];

	// Verify Command line args
	verifyArgs(argc, argv, &pathing, &algorithm, &filepath);

	// Verify Structure File
	FILE *test = fopen(filepath, "r");
	if (!test)
	{	
		err_args("Invalid structure filepath!");
		return 2;
	}
	fclose(test);

	// Stores the dimensions of the given board
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

/*
 * Verifies Command Line Arguments and sets variables in main
 * Params: int, char**, bool*, char*, char**
 * Return: void
 */
void verifyArgs(int argc, char** argv, bool* pathing, char* algorithm, char** filepath)
{
	// Check if the user provided valid number of arguments
	if (argc < 2 || argc > 4)
	{
		err_args("");
		exit(1);
	}
	
	// if the pathing, algorithm and board is specified
	if (argc == 4)
	{
		// if the value for pathing is invalid
		if (strcmp("-d", argv[1]) && strcmp("-a", argv[1]))
		{	
			err_args("");
			exit(1);
		}

		// Set the value of pathing
		// true : diagonal, false : across 
		*pathing = !strcmp("-d", argv[1]) ? true : false;

		// if the value for algorithm is invalid
		if (strcmp(argv[2], "-a") && strcmp(argv[2], "-d") && strcmp(argv[2], "-b"))
		{
			err_args("");
			exit(1);
		}

		// Set the value of algorithm
		// a : A*, d : DFS. b : BFS
		if (!strcmp(argv[2], "-a"))
			*algorithm = 'a';
		else if (!strcmp(argv[2], "-d"))
			*algorithm = 'd';
		else if (!strcmp(argv[2], "-b"))
			*algorithm = 'b';

		*filepath = argv[3];
	} 
	// if only the pathing and board is provided
	else if (argc == 3)
	{
		// if the value for pathing is invalid
		if (strcmp("-d", argv[1]) && strcmp("-a", argv[1]))
		{	
			err_args("");
			exit(1);
		}

		// Set the value of pathing
		// true : diagonal, false : across 
		*pathing = !strcmp("-d", argv[1]) ? true : false;
		*filepath = argv[2];
	}
}

/*
 * Prints out an error message for command line arguments errors
 * Params: char*
 * Return: void
 */
void err_args(char* extra_msg)
{
	printf("%s\n", extra_msg);
	printf("Usage: pathfind [-a, -d]* [-a, -d, -b]* [struture.txt]\n");
}