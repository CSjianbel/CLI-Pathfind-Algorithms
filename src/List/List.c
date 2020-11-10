#include "List.h"

Node *createNode(int row, int col, char *state, bool pathing)	
{
	Node *newNode = malloc(sizeof(Node));	

	newNode->row = row;
	newNode->column = col;

	newNode->wall = strcmp(state, "wall") ? true : false;
	newNode->start = strcmp(state, "start") ? true : false;
	newNode->end = strcmp(state, "end") ? true : false;

	newNode->hScore = newNode->gScore = newNode->fScore = 0;

	newNode->previous = NULL;

	newNode->neighbors = malloc(sizeof(Node*) * pathing ? Across : Diagonal);

	return newNode;
}

void getNeighbors(int height, int width, Node Board[height][width], Node *node, bool pathing)
{
	int index = 0;
	if (pathing) 
	{
		for (int i = -1; i < 2; i++)
		{
			if (node->row + i > 0 && node->row + i < height)
				node->neighbors[index++] = Board[node->row + 1][node->column];

			if (node->column + i > 0 && node->column + i < width)
				node->neighbors[index++] = Board[node->row][node->column + i];
		}
	}
	else
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				int oX = node->column + i, oY = node->row + j;
				if (oX > 0 && oX < width && oY > 0 && oY < height)
					node->neighbors[index++] = Board[oY][oX];
			}
		}
	}
}