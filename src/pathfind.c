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
			if (!board[i][j]->wall)
				getNeighbors(height, width, board, board[i][j], pathing);
		}
	}
}

int getLowestFScore(List *openset)
{
	// Returns -1 if the list is empty
	if (!openset)
	{
		return -1;
	}

	Node *cursor = openset->node;
	int lowest = 0;
	int index = 0;

	openset = openset->next;

	while (openset)
	{
		index++;

		if (openset->node->fScore < cursor->fScore)
		{
			cursor = openset->node;
			lowest = index;
		}
		openset = openset->next;
	}

	return lowest;
}

List *getNode(List *head, int index)
{
	while (index)
	{
		head = head->next;
		index--;
	}

	return head;

}

void printNeighbors(int height, int width, Node *board[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int counter = 0;
			for (int y = 0; board[i][j]->neighbors[y]; y++)
			{
				counter ++;
			}

			if (counter)
				printf("%d ", counter);
			else
				printf("# ");
		
		}
		printf("\n");
	}
}


bool findPath(int height, int width, Node *board[height][width], Node *start, Node *goal, bool pathing)
{
	// Set neighbors of Nodes
	setNeighbors(height, width, board, pathing);

	// print neighbor counts
	printNeighbors(height, width, board);
	printf("\n\n");

	List *openset = NULL, *closedSet = NULL;

	// Initially add the start node to the openset
	append(&openset, start);
	start->fScore = heuristic(start, goal);

	while (listLength(openset))
	{
		int lowestFindex = getLowestFScore(openset);
		List *current = getNode(openset, lowestFindex);

		if (current->node == goal)
		{
			// If the solution has been found
			Node *tmp = current->node;
			tmp->path = true;

			while (tmp->previous)
			{
				tmp = tmp->previous;
				tmp->path = true;
			}

		
			freeList(openset);
			freeList(closedSet);
			return true;
		}

		// Remove winner from openset and append to closedSet
		List *removed = removeNode(&openset, lowestFindex);
		append(&closedSet, removed->node);

		for (int i = 0; current->node->neighbors[i]; i++)
		{
			Node *neighbor = current->node->neighbors[i];

			if (search(closedSet, neighbor))
				continue;

			double tGscore = neighbor->gScore + heuristic(current->node, neighbor);

			bool newPath = false;
			if (search(openset, neighbor))
			{
				if (tGscore < neighbor->gScore)
				{
					neighbor->gScore = tGscore;
					newPath = true;
				}
				else
				{
					neighbor->gScore = tGscore;
					append(&openset,neighbor);
					newPath = true;
				}

				if (newPath)
				{
					neighbor->previous = current->node;
					neighbor->hScore = heuristic(neighbor, goal);
					neighbor->fScore = neighbor->gScore + neighbor->hScore; 
				}
			}
		}
	}

	freeList(openset);
	freeList(closedSet);

	return false;
}

