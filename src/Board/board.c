#include "board.h"

/*
 * Verifies if Board.txt is a valid board 
 * Params: char*
 * Return: bool
 */
bool verifyBoard(char* path)
{
	FILE* infile = fopen(path, "r");
	char row[MAX_WIDTH];

	// Counts the START and END characters given in the board
	int e = 0, s = 0;

	while (fscanf(infile, "%s", row) != EOF)
	{
		for (int i = 0; row[i]; i++)
		{
			char tmp = tolower(row[i]);
			// if the board contains invalid characters
			if (tmp != '#' && tmp != 's' && tmp != 'e' && tmp != '_')
			{
				fclose(infile);
				return false;
			}

			if (tmp == 's')
				s++;
			
			if (tmp == 'e')
				e++;
		}
	}

	fclose(infile);				
	// If START and END characters count is not 1 then it is an invalid board
	if (e != 1 || s != 1)
		return false;

	return true;
}

/*
 * Returns the Dimension (WxH) of Board.txt
 * Params: char*, int*, int*
 * Return: bool
 */
bool getDimension(char* path, int* height, int* width)
{
	FILE* infile = fopen(path, "r");
	char row[MAX_WIDTH];

	// Read the first line of the board
	if (fscanf(infile, "%s", row) == EOF)
	{
		fclose(infile);
		return false;
	}

	*width = strlen(row);
	*height = 1;	

	while (fscanf(infile, "%s", row) != EOF)
	{
		// if the width of the board is not symmentrical then it is an invalid board
		if (strlen(row) != *width) 
		{
			fclose(infile);
			return false;
		}

		(*height)++;	
	}

	fclose(infile);

	if (!verifyBoard(path))
		return false;

	return true;
}

/*
 * Reads the Board.txt file and fills in the Board[][] with Nodes
 * Params: char*, int, int, List*[][], List**, List**, bool
 * Return: void
 */
void readBoard(char* path, int height, int width, ListNode* board[height][width], ListNode** start, ListNode** goal, bool pathing)
{	
	FILE* infile = fopen(path, "r");
	char row[MAX_WIDTH];

	for (int i = 0; i < height; i++)
	{
		if (fscanf(infile, "%s", row) == EOF) 
			return;

		for (int j = 0; j < width; j++)
		{
			char state = tolower(row[j]);
			board[i][j] = createNode(i, j, state, pathing);
			if (state == 's')
				*start = board[i][j];

			if (state == 'e')
				*goal = board[i][j];
		}
	}

	fclose(infile);
}

/* 
 * Sets neighbors of the nodes in the board
 * Params: int, int, ListNode*
 * Return: void
 */
void setNeighbors(int height, int width, ListNode* board[height][width], bool pathing)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			setNodeNeighbors(height, width, board, board[i][j], pathing);
}

/*
 * Prints the board to the stdout
 * Params: int, int, List*[][]
 * Return: void
 */
void printBoard(int height, int width, ListNode* board[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i][j]->start)
				printf("S");
			else if (board[i][j]->end)
				printf("E");
			else if (board[i][j]->wall)
				printf("%c", WALL);
			else if (board[i][j]->path)
				printf("%c", PATH);
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n\n");
}

/* 
 * Frees the memory allocated for the Board[][]
 * Params: int, int, ListNode*[][]
 * Return: void
 */
void freeBoard(int height, int width, ListNode* board[height][width])
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			destroy(board[i][j]);
}
