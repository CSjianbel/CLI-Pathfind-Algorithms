#ifndef PATHFIND_H
#define PATHFIND_H

#include "../List/List.h"
#include "../Board/board.h"

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define Star 'a'
#define DFS 'd'
#define BFS 'b'

bool (*Algorithms[26]) (int height, int width, ListNode* board[height][width], ListNode* start, ListNode* goal);
bool findPath(int height, int width, ListNode* board[height][width], ListNode* start, ListNode* goal, char algorithm, bool pathing);

#endif
