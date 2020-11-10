#include <stdbool.h>

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