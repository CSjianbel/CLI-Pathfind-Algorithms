#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define Across 4
#define Diagonal 8

typedef struct Node
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

	struct Node *previous;
	struct Node **neighbors;

}
Node;

typedef struct List
{

	struct Node *node;
	struct List *next;

}
List;

// Node Constructor
Node *createNode(int row, int col, char state, bool pathing);
// Sets the neighboring Nodes of a given Node
void getNeighbors(int height, int width, Node *Board[height][width], Node *node, bool pathing);

/*
 * List Methods:
 *		Append, Search, Remove, Free list
 */
void append(List **head, Node *node);
bool search(List *head, Node *node);
void freeList(List *head);
int listLength(List *head);
List *removeNode(List **head, int index);
void destroy(List *node);




