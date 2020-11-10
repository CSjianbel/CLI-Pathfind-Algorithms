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

void readBoard(char *path, int height, int width, char board[height][width])
{	
	FILE *infile = fopen(path, "r");
	char row[MAX_WIDTH];

	for (int i = 0; i < height; i++)
	{
		fscanf(infile, "%s", row);
		for (int j = 0; j < width; j++)
		{
			board[i][j] = row[j];
		}
	}

	fclose(infile);
}

void printBoard(int height, int width, char board[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%c", board[i][j]);
		}
		printf("\n");
	}

}

int heuristic(struct Node start, struct Node goal)
{
	int y1 = start.row, x1 = start.column;
	int y2 = goal.row, x2 = goal.column;
	
	// Euclidean distance of 2 Nodes
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}