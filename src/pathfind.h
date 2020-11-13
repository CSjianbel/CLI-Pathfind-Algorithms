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
#define PATH 15

bool getDimension(char *path, int *height, int *width);
bool verifyBoard(char *path);
void readBoard(char *path, int height, int width, Node *board[height][width], Node **start, Node **goal, bool pathing);
void printBoard(int height, int width, Node *board[height][width]);
double heuristic(Node *start, Node *goal);
void setNeighbors(int height, int width, Node *board[height][width], bool pathing);
bool findPath(int height, int width, Node *board[height][width], Node *start, Node *goal, char algorithm, bool pathing);
bool AStar(int height, int width, Node *board[height][width], Node *start, Node *goal, bool pathing);
bool depthFirstSearch(int height, int width, Node *board[height][width], Node *start, Node *goal, bool pathing);
bool breadthFirstSearch(int height, int width, Node *board[height][width], Node *start, Node *goal, bool pathing);
int getLowestFScore(List *openset);
List *getNode(List *head, int index);
