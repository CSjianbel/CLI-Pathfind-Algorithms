#include "pathfind.h"

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
			if (tolower(row[j]) == 's')
			{
				*start = board[i][j];
			}
			if (tolower(row[j]) == 'e')
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
			if (board[i][j]->start)
			{
				printf("S");
			}
			else if (board[i][j]->end)
			{
				printf("E");
			}
			else if (board[i][j]->path)
			{
				printf("%c", PATH);
			}
			else if (board[i][j]->wall)
			{
				printf("%c", WALL);
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

double heuristic(Node *start, Node *goal)
{
	int y1 = start->row, x1 = start->column;
	int y2 = goal->row, x2 = goal->column;
	
	// Euclidean distance of 2 Nodes
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
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
	// If the index is invalid for the given linked list
	if (index < 0 && index >= listLength(head))
		return NULL;

	while (index)
	{
		head = head->next;
		index--;
	}

	return head;
}

bool AStar(int height, int width, Node *board[height][width], Node *start, Node *goal)
{
	List *openSet = NULL, *closedSet = NULL;

	// Initially add the start node to the openset
	append(&openSet, start);
	start->fScore = heuristic(start, goal);

	while (listLength(openSet))
	{
		int lowestFindex = getLowestFScore(openSet);
		List *current = getNode(openSet, lowestFindex);

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

			freeList(openSet);
			freeList(closedSet);
			return true;
		}

		// Remove winner from openset and append to closedSet
		List *removed = removeNode(&openSet, lowestFindex);
		append(&closedSet, removed->node);

		for (int i = 0; current->node->neighbors[i]; i++)
		{
			Node *neighbor = current->node->neighbors[i];

			// if neighbor is in the closedSet
			if (search(closedSet, neighbor))
				continue;

			double tGscore = neighbor->gScore + heuristic(current->node, neighbor);

			bool newPath = false;
			if (search(openSet, neighbor))
			{
				if (tGscore < neighbor->gScore)
				{
					neighbor->gScore = tGscore;
					newPath = true;
				}
			}
			else
			{
				neighbor->gScore = tGscore;
				append(&openSet, neighbor);
				newPath = true;
			}

			// if new path has been found
			if (newPath)
			{
				neighbor->previous = current->node;
				neighbor->hScore = heuristic(neighbor, goal);
				neighbor->fScore = neighbor->gScore + neighbor->hScore; 
			}
		}
	}

	// Free memory allocated by the lists
	freeList(openSet);
	freeList(closedSet);
	return false;
}

bool depthFirstSearch(int height, int width, Node *board[height][width], Node *start, Node *goal)
{
	List *stack = NULL;
	List *explored = NULL;

	// Initially add the start node to the stack frontier
	append(&stack, start);

	while (listLength(stack))
	{
		List *current = pop(&stack);

		// If soltion has been found
		if (current->node == goal)
		{
			Node *tmp = current->node;
			tmp->path = true;

			while (tmp->previous)
			{
				tmp = tmp->previous;
				tmp->path = true;
			}

			freeList(stack);
			freeList(explored);	
			return true;
		}

		// Add current to explored states
		if (!search(explored, current->node))
			append(&explored, current->node);

		// Add neighbors to stack frontier
		for (int i = 0; current->node->neighbors[i]; i++)
		{
			Node *neighbor = current->node->neighbors[i];

			if (!search(explored, neighbor) && !search(stack, neighbor) && !neighbor->wall)
			{
				append(&stack, neighbor);
				neighbor->previous = current->node;
			}
		}
	}

	freeList(stack);
	freeList(explored);
	return false;
}

bool breadthFirstSearch(int height, int width, Node *board[height][width], Node *start, Node *goal)
{
	List *queue = NULL;
	List *explored = NULL;

	// Initially add the start node to the queue frontier
	append(&queue, start);

	while (listLength(queue))
	{
		List *current = dequeue(&queue);

		// If solution has been found
		if (current->node == goal)
		{
			Node *tmp = current->node;
			tmp->path = true;

			while (tmp->previous)
			{
				tmp = tmp->previous;
				tmp->path = true;
			}

			freeList(queue);
			freeList(explored);
			return true;
		}

		// Add current to explored states
		append(&explored, current->node);

		// Add neighbors to queue frontier
		for (int i = 0; current->node->neighbors[i]; i++)
		{
			Node *neighbor = current->node->neighbors[i];

			if (!search(explored, neighbor) && !search(queue, neighbor) && !neighbor->wall)
			{
				append(&queue, neighbor);
				neighbor->previous = current->node;
			}
		}
	}

	freeList(queue);
	freeList(explored);
	return false;
}

bool findPath(int height, int width, Node *board[height][width], Node *start, Node *goal, char algorithm, bool pathing)
{
	// Set neighbors of Nodes
	setNeighbors(height, width, board, pathing);
	printf("Finding path...\n\n");

	if (algorithm == 'a')
	{
		if (AStar(height, width, board, start, goal))
			return true;
		return false;
	}
	else if (algorithm == 'd')
	{
		if (depthFirstSearch(height, width, board, start, goal))
			return true;
		return false;
	}
	else if (algorithm == 'b')
	{
		if (breadthFirstSearch(height, width, board, start, goal))
			return true;
		return false;
	}

	return false;
}