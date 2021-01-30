#include "List.h"

/*
 * Constructor for a Node
 * Params: int, int, char, bool
 * Return: List*
 */
List* createNode(int row, int col, char state, bool pathing)	
{
	List* newNode = malloc(sizeof(List));	

	newNode->row = row;
	newNode->column = col;

	newNode->wall = state == '#' ? true : false;
	newNode->start = state == 's' ? true : false;
	newNode->end = state == 'e' ? true : false;
	newNode->path = false;

	newNode->hScore = newNode->gScore = newNode->fScore = 0;

	newNode->previous = NULL;

	newNode->neighbors = calloc(pathing ? Diagonal : Across, sizeof(List*));

	newNode->next = NULL;

	return newNode;
}

/*
 * Sets the neighbors for a given Node in the Board
 * params: int, int, List*[][], List*, bool
 * Return: void
 */ 
void getNeighbors(int height, int width, List* Board[height][width], List* node, bool pathing)
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
					node->neighbors[index++] = Board[oY][oX];
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

/*
 * Appends a node to the end of the List
 * Params: List**, List*
 * Return: void
 */
void append(List** head, List* node)
{
	if (!*head)
	{
		*head = node;
	}
	else 
	{
		List* tmp = *head;
		while (tmp->next)
			tmp = tmp->next;

		tmp->next = node;
	}
}

/*
 * Searches if a node exists in the list
 * Params: List*, List*
 * Return: bool
 */
bool search(List* head, List* node)
{
	while (head)
	{
		if (head == node)
			return true;

		head = head->next;
	}
	return false;
}

/*
 * Frees the allocated memory for the List
 * Params: List*
 * Return: void
 */
void freeList(List* head)
{
	while (head)
	{
		List* tmp = head->next;
		destroy(head);
		head = tmp;
	}
}

/*
 * Returns the current length of the list
 * Params: List*
 * Return: int
 */
int listLength(List* head)
{
	int counter = 0;

	while (head)
	{
		head = head->next;
		counter++;
	}	
	return counter;
}

/*
 * Removes the (index)th Node from the list
 * Params: List**, int
 * Return: List*
 */
List* removeNode(List** head, int index)
{
	List* cursor = *head;
	if (index < 0 || index >= listLength(*head))
		return NULL;
	
	if (!index)
	{
		*head = cursor->next;
	}
	else
	{
		while (1)
		{
			List* tmp = cursor;
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

/*
 * Pops the Last Node of the List
 * Params: List**
 * Return: List*
 */
List *pop(List **head)
{
	return removeNode(head, listLength(*head) - 1);
}

/*
 * Dequeues the First Node of the List
 * Params: List**
 * Return: List*
 */
List *dequeue(List **head)
{
	return removeNode(head, 0);
}

/*
 * Wrapper for free()
 * Params: List*
 * Return: void
 */
void destroy(List *node)
{
	free(node);
}
