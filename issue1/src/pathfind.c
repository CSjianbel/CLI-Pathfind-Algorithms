#include "pathfind.h"

/*
 * Returns the index of the node with the lowest Fscore 
 * Params: ListNode*
 * Return: int
 */
int getLowestFscore(ListNode* openset)
{
    int index = 0;
    int lowest = 0;
    ListNode* tmp = openset;

    openset = openset->next;

    while (openset)
    {
        index++;

        if (openset->fScore < tmp->fScore)
        {
            lowest = index;
            tmp = openset;
        }

        openset = openset->next;
    }
    return lowest;
}

/*
 * Returns the Euclidean distance between 2 Nodes
 * Params: ListNode*, ListNode*
 * Return: double
 */
double heuristic(ListNode* start, ListNode* goal)
{
	int y1 = start->row, x1 = start->col;
	int y2 = goal->row, x2 = goal->col;
	
	// Euclidean distance of 2 Nodes
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

/*
 * A* Pathfinding Algorithm 
 * Params: int, int, ListNode*[][], ListNode*, ListNode
 * Return: bool
 */
bool Astar(int height, int width, ListNode* board[height][width], ListNode* start, ListNode* goal)
{
    ListNode* openset = NULL;
    ListNode* closedset = NULL;

    // Add the start Node to the openset
    append(&openset, start);
    start->fScore = heuristic(start, goal);

    while (getListLength(openset))
    {
        int lowestFIndex = getLowestFscore(openset);
        ListNode* current = removeListNode(&openset, lowestFIndex);

        // Solution has been found
        if (current == goal)
        {
			printf("Path found!\n\n");
            ListNode* tmp = current;
            while (tmp->previous)
            {
                tmp->path = true;
				printf("%d - %d", tmp->row, tmp->col);
                tmp = tmp->previous;
            }

            return true;
        }

        // Append current to closedset
        append(&closedset, current);

        for (int i = 0; current->neighbors[i]; i++)
        {
            ListNode* neighbor = current->neighbors[i];

            // If neighbor is already in the closedset
            if (search(closedset, neighbor))
                continue;

            double tGscore = neighbor->gScore + heuristic(current, neighbor);
            
            bool newPathFound = false;

            if (search(openset, neighbor))
            {
                if (tGscore < neighbor->gScore)
                {
                    neighbor->gScore = tGscore;
                    newPathFound = true;
                }
            }
            else
            {
				neighbor->gScore = tGscore;
				append(&openset, neighbor);
				newPathFound = true;
            }

            if (newPathFound)
            {
				neighbor->previous = current;
				neighbor->hScore = heuristic(neighbor, goal);
				neighbor->fScore = neighbor->gScore + neighbor->hScore; 
            }
        }
    }
    return false;
}


bool findPath(int height, int width, ListNode* board[height][width], ListNode* start, ListNode* goal, char algorithm, bool pathing)
{
	return Astar(height, width, board, start, goal);
}
