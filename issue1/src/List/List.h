#include <stdlib.h>
#include <stdbool.h>

#define ACROSS 5
#define DIAGONAL 9

typedef struct ListNode
{
    int row;
    int col;

    bool start;
    bool end;
    bool wall;

    bool path;

    double fScore;
    double gScore;
    double hScore;

    struct ListNode* previous;
    struct ListNode** neighbors;

    struct ListNode* next;
}
ListNode;

// ListNode Constructor
ListNode* createNode(int row, int col, char state, bool pathing);
void getNeighbors(int height, int width, ListNode* board[height][width], ListNode* node, bool pathing);

/*
 * List Methods:
 *		Append, Search, Remove, Free list
 */
void append(ListNode** head, ListNode* node);
bool search(ListNode* head, ListNode* node);
void freeList(ListNode* head);
int getListLength(ListNode* head);
ListNode* removeListNode(ListNode** head, int index);
ListNode* pop(ListNode** head);
ListNode* dequeue(ListNode** head);
void destroy(ListNode*node);
