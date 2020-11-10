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

	int hScore;
	int gScore;
	int fScore;

	struct Node *previous;
	struct Node *neighbors;

}
Node;

typedef struct List
{

	struct Node node;
	struct List *next;

}
List;

Node *createNode(int row, int col, char *state, bool pathing);
void getNeighbors(int height, int width, Node Board[height][width], Node *node, bool pathing);

/*
 * List Methods:
 *		Append, Search, Remove, Reverse
 */

void append(List **head, Node *node);
bool search(List *head, Node *node);
void reverseList(List **head);



