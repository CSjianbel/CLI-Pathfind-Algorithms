#include "pathfind.h"

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
		return false;

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
void readBoard(char* path, int height, int width, List* board[height][width], List** start, List** goal, bool pathing)
{	
	FILE* infile = fopen(path, "r");
	char row[MAX_WIDTH];

	for (int i = 0; i < height; i++)
	{
		if (fscanf(infile, "%s", row) == EOF) 
			return;

		for (int j = 0; j < width; j++)
		{
			board[i][j] = createNode(i, j, tolower(row[j]), pathing);
			if (tolower(row[j]) == 's')
				*start = board[i][j];

			if (tolower(row[j]) == 'e')
				*goal = board[i][j];
		}
	}

	fclose(infile);
}

/*
 * Prints the board to the stdout
 * Params: int, int, List*[][]
 * Return: void
 */
void printBoard(int height, int width, List* board[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{

			if (board[i][j]->start)
				printf("S");
			else if (board[i][j]->end)
				printf("E");
			else if (board[i][j]->path)
				printf("%c", PATH);
			else if (board[i][j]->wall)
				printf("%c", WALL);
			else
				printf(" ");
		}
		printf("\n");
	}
}

/* 
 * Returns the Euclidean distance of 2 Nodes
 * Params: List*, List*
 * Return: double 
 */
double heuristic(List* start, List* goal)
{
	int y1 = start->row, x1 = start->column;
	int y2 = goal->row, x2 = goal->column;
	
	// Euclidean distance of 2 Nodes
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

/*
 * Calls getNeighbors() for each Node in Board
 * Params: int, int, List*[][], bool
 * Return: void
 */
void setNeighbors(int height, int width, List* board[height][width], bool pathing)
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

/*
 * Returns the index of the node with the lowest FScore
 * Param: List*
 * Return: int
 */
int getLowestFScore(List* openset)
{
	// Returns -1 if the list is empty
	if (!openset)
		return -1;

	List* cursor = openset;
	int lowest = 0;
	int index = 0;

	openset = openset->next;

	while (openset)
	{
		index++;

		if (openset->fScore < cursor->fScore)
		{
			cursor = openset;
			lowest = index;
		}
		openset = openset->next;
	}

	return lowest;
}

/*
 * Returns a pointer to the Node given the index
 * Param: List*, int
 * Return: List*
 */
List* getNode(List* head, int index)
{
	// If the index is invalid for the given linked list
	if (index < 0 && index >= listLength(head))
		return NULL;

	while (index--)
		head = head->next;

	/* 
	 * while (index)
	 * {
	 * 		head = head->next;
	 * 		index--;
	 * }
	 */

	return head;
}

/*
 * A* Pathfinding Algorithm
 * Param: int, int, List*[][], List*, List*
 * Return: bool
 */
bool AStar(int height, int width, List* board[height][width], List* start, List* goal)
{
	List* openSet = NULL;
	List* closedSet = NULL;

	// Initially add the start node to the openset
	append(&openSet, start);
	start->fScore = heuristic(start, goal);

	while (listLength(openSet))
	{
		int lowestFindex = getLowestFScore(openSet);
		List *current = getNode(openSet, lowestFindex);

		if (current == goal)
		{
			// If the solution has been found
			List* tmp = current;
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
		List* removed = removeNode(&openSet, lowestFindex);
		append(&closedSet, removed);

		for (int i = 0; current->neighbors[i]; i++)
		{
			List* neighbor = current->neighbors[i];

			// if neighbor is in the closedSet
			if (search(closedSet, neighbor))
				continue;

			double tGscore = neighbor->gScore + heuristic(current, neighbor);

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
				neighbor->previous = current;
				neighbor->hScore = heuristic(neighbor, goal);
				neighbor->fScore = neighbor->gScore + neighbor->hScore; 
			}

		}
	}

	freeList(openSet);
	freeList(closedSet);
	return false;
}

/*
 * Depth-First Search Algorithm
 * Param: int, int, List*[][], List*, List*
 * Return: bool
 */
bool depthFirstSearch(int height, int width, List* board[height][width], List* start, List* goal)
{
	List* stack = NULL;
	List* explored = NULL;

	// Initially add the start node to the stack frontier
	append(&stack, start);

	while (listLength(stack))
	{
		List* current = pop(&stack);

		// If solution has been found
		if (current == goal)
		{
			List* tmp = current;
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
		if (!search(explored, current))
			append(&explored, current);

		// Add neighbors to stack frontier
		for (int i = 0; current->neighbors[i]; i++)
		{
			List* neighbor = current->neighbors[i];

			if (!search(explored, neighbor) && !search(stack, neighbor) && !neighbor->wall)
			{
				append(&stack, neighbor);
				neighbor->previous = current;
			}
		}

	}

	freeList(stack);
	freeList(explored);
	return false;
}

/*
 * Breadth-First Search Algorithm
 * Param: int, int, List*[][], List*, List*
 * Return: bool
 */
bool breadthFirstSearch(int height, int width, List* board[height][width], List* start, List* goal)
{
	List* queue = NULL;
	List* explored = NULL;

	// Initially add the start node to the queue frontier
	append(&queue, start);

	while (listLength(queue))
	{
		List* current = dequeue(&queue);

		// If solution has been found
		if (current == goal)
		{
			List* tmp = current;
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

		// Add current Node to explored states
		append(&explored, current);

		// Add neighbors to queue frontier
		for (int i = 0; current->neighbors[i]; i++)
		{
			List* neighbor = current->neighbors[i];

			if (!search(explored, neighbor) && !search(queue, neighbor) && !neighbor->wall)
			{
				append(&queue, neighbor);
				neighbor->previous = current;
			}
		}
	}

	freeList(queue);
	freeList(explored);
	return false;
}

/*
 * Initializes the Algorithms Function Pointer array
 */
void setup()
{
	Algorithms[Star] = AStar;
	Algorithms[DFS] = depthFirstSearch;
	Algorithms[BFS] = breadthFirstSearch;
}

/* 
 * Runs the desired algorithm on the Board 
 * Params: int, int, List*[][], List*, List*, char, bool
 * Return: bool
 */
bool findPath(int height, int width, List* board[height][width], List* start, List* goal, char algorithm, bool pathing)
{
	// Setup and Initialize Algorithms
	setup();
	// Set neighbors of Nodes
	setNeighbors(height, width, board, pathing);
	printf("Finding path...\n\n");

	if (Algorithms[tolower(algorithm) - 'a'](height, width, board, start, goal))
		return true;
	return false;

	// if (algorithm == 'a')
	// {
	// 	// Use A* Search
	// 	if (AStar(height, width, board, start, goal))
	// 		return true;
	// 	return false;
	// }
	// else if (algorithm == 'd')
	// {
	// 	// Use Depth First Search
	// 	if (depthFirstSearch(height, width, board, start, goal))
	// 		return true;
	// 	return false;
	// }
	// else if (algorithm == 'b')
	// {
	// 	// Use Breadth First Search
	// 	if (breadthFirstSearch(height, width, board, start, goal))
	// 		return true;
	// 	return false;
	// }

	// return false;
}