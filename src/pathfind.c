#include "pathfind.h"

bool getDimension(char *path, int *height, int *width)
{
	FILE *infile = fopen(path, "r");
	char row[MAX_WIDTH];

	// Read the first line of the board
	fscanf(infile, "%s", row);
	*width = strlen(row);
	*height = 1;	

	while (fscanf(infile, "%s", row) != EOF)
	{
		// if the width of the board is not symmentrical then it is an invalid board
		if (strlen(row) != *width) {
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

bool verifyBoard(char *path)
{
	FILE *infile = fopen(path, "r");
	char row[MAX_WIDTH];

	// Counts the START and END characters given in the board
	int e = 0, s = 0;

	while (fscanf(infile, "%s", row) != EOF)
	{
		for (int i = 0; row[i]; i++)
		{
			char tmp = tolower(row[i]);
			// if the board contains invalid characters
			if (tmp != WALL && tmp != START && tmp != END && tmp != OPEN)
			{
				fclose(infile);
				return false;
			}

			if (tmp == START)
				s++;
			
			if (tmp == END)
				e++;
		}
	}

	fclose(infile);				
	// If there are more than 1 START or END characters in the board then it is invalid
	if (e != 1 || s != 1)
		return false;

	return true;
}

void readBoard(char *path, int height, int width, Node *board[height][width], Node **start, Node **goal, bool pathing)
{	
	FILE *infile = fopen(path, "r");
	char row[MAX_WIDTH];

	for (int i = 0; i < height; i++)
	{
		fscanf(infile, "%s", row);
		for (int j = 0; j < width; j++)
		{
			board[i][j] = createNode(i, j, tolower(row[j]), pathing);
			if (tolower(row[j]) == START)
			{
				*start = board[i][j];
			}
			if (tolower(row[j]) == END)
			{
				*goal = board[i][j];
			}
		}
	}

	fclose(infile);
}

void printBoard(int height, int width, Node *board[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i][j]->path)
			{
				printf("*");
			}
			else if (board[i][j]->wall)
			{
				printf("#");
			}
			else if (board[i][j]->start)
			{
				printf("S");
			}
			else if (board[i][j]->end)
			{
				printf("E");
			}
			else
			{
				printf("_");
			}
		}
		printf("\n");
	}

}

int heuristic(Node *start, Node *goal)
{
	int y1 = start->row, x1 = start->column;
	int y2 = goal->row, x2 = goal->column;
	
	// Euclidean distance of 2 Nodes
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void setNeighbors(int height, int width, Node *board[height][width], bool pathing)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			getNeighbors(height, width, board, board[i][j], pathing);
		}
	}
}

int getLowestFScore(List *openset)
{
	if (!openset)
		return 0;

	lowest = 0;
	while (openset)
	{
		
	}

	return lowest;
}

bool findPath(int height, int width, Node *board[height][width], List **path, Node *start, Node *goal)
{
	List *openset = NULL, *closedSet = NULL;

	// Initially add the start node to the openset
	append(&openset, start);
	start->f = heuristic(startr, goal);

	while (listLength(&openset))
	{

	}

	return false;
}

