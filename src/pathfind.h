#include "List/List.h"

#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_WIDTH 50
#define WALL 219
#define PATH 15

bool getDimension(char *path, int *height, int *width);
void readBoard(char *path, int height, int width, Node *board[height][width], Node **start, Node **goal, bool pathing);
void printBoard(int height, int width, Node *board[height][width]);
bool findPath(int height, int width, Node *board[height][width], Node *start, Node *goal, char algorithm, bool pathing);

