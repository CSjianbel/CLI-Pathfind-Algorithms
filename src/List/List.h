#include <stdbool.h>

struct Node
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
	struct Node neighbors[8];

};

struct List
{

	struct Node node;
	struct List *next;

};