#include "List/List.h"

#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_WIDTH 50
#define WALL '#'
#define PATH 'X'

#define Star 'a'
#define DFS 'd'
#define BFS 'b'

bool (*Algorithms[26]) (int height, int width, ListNode* board[height][width], ListNode* start, ListNode* goal);

bool getDimension(char* path, int* height, int* width);
void readBoard(char* path, int height, int width, ListNode* board[height][width], ListNode** start, ListNode** goal, bool pathing);
void printBoard(int height, int width, ListNode* board[height][width]);
bool findPath(int height, int width, ListNode* board[height][width], ListNode* start, ListNode* goal, char algorithm, bool pathing);
void freeBoard(int height, int width, ListNode* board[height][width]);
