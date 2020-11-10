#include "List/List.h"

#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_WIDTH 50
#define WALL '#'
#define OPEN '_'
#define START 's'
#define END 'e'
#define PATH '*'

bool getDimension(char *path, int *height, int *width);
bool verifyBoard(char *path);
void readBoard(char *path, int height, int width, char board[height][width]);
void printBoard(int height, int width, char board[height][width]);
int heuristic(struct Node start, struct Node goal);
