#include "pathfind.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: pathfind [struture.txt]\n");
		return 1;
	}

	int width = 0, height = 0;

	// Get the dimension of the given board
	int res = getDimension(argv[1], &height, &width);

	printf("Height: %d - Width: %d - Res: %d\n", height, width, res);

	if (!res)
	{
		printf("Invalid Board!\n");
		return 2;
	}

	// Create a 2d array of given dimensions
	char board[height][width];

	// Read the board into the array
	readBoard(argv[1], height, width, board);
	printBoard(height, width, board);

	/* test createNode() 
	Node *node = createNode(1, 1, "wall", true);

	printf("row: %d - col: %d start: %d end: %d wall: %d scores: %d %d %d \n", node->row, node->column, node->start, node->end, node->wall, node->hScore, node->gScore, node->fScore);
	*/

}
