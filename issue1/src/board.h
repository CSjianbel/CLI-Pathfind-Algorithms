#ifndef BOARD_H
#define BOARD_H

#include "List/List.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WIDTH 50
#define WALL '#'
#define PATH 'X'

bool getDimension(char* path, int* height, int* width);
void readBoard(char* path, int height, int width, ListNode* board[height][width], ListNode** start, ListNode** goal, bool pathing);
void printBoard(int height, int width, ListNode* board[height][width]);
void freeBoard(int height, int width, ListNode* board[height][width]);
void setNeighbors(int height, int width, ListNode* board[height][width], bool pathing);

#endif