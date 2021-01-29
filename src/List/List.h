#include <stdlib.h>
#include <stdbool.h>

#define Across 4
#define Diagonal 8

typedef struct List
{
	int row;
	int column;

	bool wall;
	bool start;
	bool end;

	bool path;

	double hScore;
	double gScore;
	double fScore;

	struct List *previous;
	struct List **neighbors;

	struct List *next;
}
List;

// List Constructor
List *createNode(int row, int col, char state, bool pathing);
// Sets the neighboring Nodes of a given List
void getNeighbors(int height, int width, List *Board[height][width], List *node, bool pathing);

/*
 * List Methods:
 *		Append, Search, Remove, Free list
 */
void append(List **head, List *node);
bool search(List *head, List *node);
void freeList(List *head);

int listLength(List *head);
List* removeNode(List **head, int index);
List* pop(List **head);
List* dequeue(List **head);
void destroy(List *node);
