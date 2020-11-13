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

	newNode->neighbors = calloc(pathing ? Diagonal : Across, sizeof(Node*));

	return newNode;
}

void getNeighbors(int height, int width, Node *Board[height][width], Node *node, bool pathing)
{
	int index = 0;
	if (pathing) 
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (!i && !j)
					continue;

				int oX = node->column + i, oY = node->row + j;
				if (oX >= 0 && oX < width && oY >= 0 && oY < height && !Board[oY][oX]->wall) 
				{
					node->neighbors[index++] = Board[oY][oX];
				}
			}
		}
	}
	else
	{
		for (int i = -1; i < 2; i += 2)
		{
			if (node->row + i >= 0 && node->row + i < height && !Board[node->row + i][node->column]->wall)
				node->neighbors[index++] = Board[node->row + i][node->column];

			if (node->column + i >= 0 && node->column + i < width && !Board[node->row][node->column + i]->wall)
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

List *removeNode(List **head, int index)
{
	List *cursor = *head;
	if (index < 0 || index >= listLength(*head))
	{
		return NULL;
	}
	
	if (!index)
	{
		*head = cursor->next;
	}
	else
	{
		while (1)
		{
			List *tmp = cursor;
			cursor = cursor->next;
			if (!--index)
			{
				tmp->next = cursor->next;
				break;
			}
		}
	}

	return cursor;
}

List *pop(List **head)
{
	return removeNode(head, listLength(*head) - 1);
}

List *dequeue(List **head)
{
	return removeNode(head, 0);
}

void destroy(List *node)
{
	free(node);
}
