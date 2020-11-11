#include "List.h"

Node *createNode(int row, int col, char state, bool pathing)	
{
	Node *newNode = malloc(sizeof(Node));	

	newNode->row = row;
	newNode->column = col;

	newNode->wall = state == '#' ? true : false;
	newNode->start = state == 's' ? true : false;
	newNode->end = state == 'e' ? true : false;
	newNode->path = false;

	newNode->hScore = newNode->gScore = newNode->fScore = 0;

	newNode->previous = NULL;

	newNode->neighbors = malloc(sizeof(Node*) * pathing ? Diagonal : Across);

	return newNode;
}

void getNeighbors(int height, int width, Node Board[height][width], Node *node, bool pathing)
{
	int index = 0;
	if (pathing) 
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
	else
	{
		for (int i = -1; i < 2; i++)
		{
			if (node->row + i > 0 && node->row + i < height)
				node->neighbors[index++] = Board[node->row + 1][node->column];

			if (node->column + i > 0 && node->column + i < width)
				node->neighbors[index++] = Board[node->row][node->column + i];
		}
	}
}

void append(List **head, Node *node)
{
	List *n = malloc(sizeof(List));
	n->node = node;
	n->next = NULL;

	if (!*head)
	{
		*head = n;
	}
	else 
	{
		List *tmp = *head;
		while (tmp->next)
			tmp = tmp->next;

		tmp->next = n;
	}
}

bool search(List *head, Node *node)
{
	while (head)
	{
		if (head->node == node)
			return true;

		head = head->next;
	}
	return false;
}

void reverseList(List **head)
{

}

void freeList(List *head)
{
	while (head)
	{
		List *tmp = head->next;
		free(head);
		head = tmp;
	}
}

int listLength(List *head)
{
	int counter = 0;

	while (head)
	{
		head = head->next;
		counter++;
	}	
	return counter;
}
