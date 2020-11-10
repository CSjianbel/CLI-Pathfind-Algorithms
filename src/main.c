#include "pathfind.h"

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
	{
		printf("Usage: pathfind [-d, -a] [struture.txt]\n");
		return 1;
	}
	
	bool pathing = true;
	char *filepath = argv[1];

	if (argc == 3)
	{
		if (strcmp("-d", argv[1]) && strcmp("-a", argv[1]))
		{	
			printf("Usage: pathfind [-d, -a] [struture.txt]\n");
			return 1;
		}

		if (!strcmp("-d", argv[1]))
		{
			pathing = true;
		}
		else 
		{
			pathing = false;
		}
		filepath = argv[2];
	}

	FILE *test = fopen(filepath, "r");
	if (!test)
	{	
		printf("Invalid structure filepath!\n\n");
		printf("Usage: pathfind [-d, -a] [struture.txt]\n");
		return 2;
	}

	int width = 0, height = 0;

	// Get the dimension of the given board
	int res = getDimension(filepath, &height, &width);

	printf("Height: %d - Width: %d - Res: %d\n", height, width, res);

	if (!res)
	{
		printf("Invalid Board!\n\n");
		printf("Usage: pathfind [-d, -a] [struture.txt]\n");
		return 3;
	}

	// Create a 2d array of given dimensions
	Node *board[height][width];

	// Read the board into the array
	readBoard(filepath, height, width, board, pathing);
	printBoard(height, width, board);

}
