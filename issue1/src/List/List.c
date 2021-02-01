#include "List.h"

/*
 * Constructor for ListNode
 * Params: int, int, char, bool
 * Return: ListNode*
 */
ListNode* createNode(int row, int col, char state, bool pathing)
{
    ListNode* newNode = malloc(sizeof(ListNode));
    if (!newNode)
        return NULL;

    newNode->row = row;
    newNode->col = col;
    
    newNode->start = state == 's' ? true : false;
    newNode->end= state == 'e' ? true : false;
    newNode->wall= state == '#' ? true : false;

    newNode->fScore = newNode->gScore = newNode->hScore = 0;

    newNode->path = false;
    newNode->previous = NULL;
    newNode->neighbors = calloc(pathing ? DIAGONAL : ACROSS, sizeof(ListNode*));

    newNode->next = NULL;
    
    return newNode;
}

/* 
 * Sets the neighbors of a given node in board
 * Params: int, int, ListNode*[][], ListNode*, bool
 * Return: void
 */
void setNodeNeighbors(int height, int width, ListNode* board[height][width], ListNode* node, bool pathing)
{
    int index = 0;
    // Pathing is set to diagonal & across
    if (pathing)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (!i && !j)
                    continue;

                int oY = node->row + i;
                int oX = node->col + j;
                if (oY >= 0 && oY < height && oX >= 0 && oX < width && !board[oY][oX]->wall)
                    node->neighbors[index++] = board[oY][oX];
            }
        }
    }
    else
    {
        for (int i = -1; i < 2; i += 2)
        {
			if (node->row + i >= 0 && node->row + i < height && !board[node->row + i][node->col]->wall)
				node->neighbors[index++] = board[node->row + i][node->col];

			if (node->col + i >= 0 && node->col + i < width && !board[node->row][node->col + i]->wall)
				node->neighbors[index++] = board[node->row][node->col+ i];
		}
    }
}

/* 
 * Appends a node to the end of the List
 * Params: List**, List*
 * Return: void
 */
void append(ListNode** head, ListNode* node)
{
    if (!*head)
    {
        *head = node;
    }
    else
    {
        ListNode* cursor = *head;
        while (cursor->next)
            cursor = cursor->next;
        
        node->next = NULL;
        cursor->next = node;
    }
}

/*
 * Searches if node exists in the list
 * Params: ListNode*, ListNode*
 * Return: bool
 */
bool search(ListNode* head, ListNode* node)
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
 * Prints the List
 * Params: ListNode*
 * Return: void
 */
void printList(ListNode* head)
{
    printf("[");
    while (head)
    {
        printf("(%d, %d)", head->row, head->col);
        head = head->next;
        if (head)
            printf(", ");
    }
    printf("]\n");
}

/*
 * Prints the Node as a tuple of its row and col values
 * Params: ListNode*
 * Return: void
 */
void printNode(ListNode* node)
{
    if (!node)
        printf("%p\n", node);
    else
        printf("(%d, %d)\n", node->row, node->col);
}

/*
 * Frees the memory allocated for the list
 * Params: ListNode*
 * Return: void
 */
void freeList(ListNode* head)
{
    ListNode* tmp;
    while (head)
    {
        tmp = head->next;
        destroy(head);
        head = tmp;
    }
}

/*
 * Returns the length of the List
 * Params: ListNode*
 * Return: int
 */
int getListLength(ListNode* head)
{
    int length = 0;
    while (head)
    {
        head = head->next;
        length++;
    }
    return length;
}

/*
 * Removes the (index)th node from the List
 * Params: ListNode**, int
 * Return: ListNode*
 */
ListNode* removeListNode(ListNode** head, int index)
{
    if (!*head)
        return NULL;
  
   // Store head node 
   ListNode* tmp = *head;
  
    if (index == 0)
    {
        *head = tmp->next;
        return tmp;
    }
  
    // Find previous node of the node to be deleted 
    for (int i = 0; tmp != NULL && i < index - 1; i++) 
        tmp = tmp->next; 
  
    // If position is more than number of nodes 
    if (tmp == NULL || tmp->next == NULL) 
         return NULL; 
  
    // Node temp->next is the node to be removed
    // Store pointer to the next of node to be deleted 
    ListNode* next = tmp->next->next; 
    ListNode* nodeToBeRemoved = tmp->next;
    // Unlink the deleted node from list
    tmp->next = next; 

    return nodeToBeRemoved;
}

/* 
 * Pops the last Node of the List
 * Params: ListNode**
 * Return: ListNode*
 */
ListNode* pop(ListNode** head)
{
    return removeListNode(head, getListLength(*head) - 1);
}

/*
 * Dequeues the first Node of the List
 * Params: ListNode**
 * Return: ListNode*
 */
ListNode* dequeue(ListNode** head)
{
    return removeListNode(head, 0);
}

/*
 * Wrapper for free()
 * Params: ListNode*
 * Return: void
 */
void destroy(ListNode* node)
{
    free(node->neighbors);
    free(node);
}

