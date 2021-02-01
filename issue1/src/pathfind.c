#include "pathfind.h"
#include "board.h"

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
    printf("A* Search\n\n");
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
            ListNode* tmp = current;
            while (tmp->previous)
            {
                tmp->path = true;
                tmp = tmp->previous;
            }

            return true;
        }

        // Append current to closedset
        if (!search(closedset, current))
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

/*
 * Depth-First Search Algorithm
 * Params: int, int, ListNode*[][], ListNode*, ListNode
 * Return: bool
 */
bool depthFirstSearch(int height, int width, ListNode* board[height][width], ListNode* start, ListNode* goal)
{
    printf("Depth First Search\n\n");
    return false;
}

/*
 * Breath-First Search Algorithm
 * Params: int, int, ListNode*[][], ListNode*, ListNode
 * Return: bool
 */
bool breathFirstSearch(int height, int width, ListNode* board[height][width], ListNode* start, ListNode* goal)
{
    printf("Breadth First Search\n\n");
    return false;
}

void setup(int height, int width, ListNode* board[height][width], bool pathing)
{
    setNeighbors(height, width, board, pathing);
    Algorithms[tolower(Star)] = Astar;
    Algorithms[tolower(DFS)] = depthFirstSearch;
    Algorithms[tolower(BFS)] = breathFirstSearch;
}


bool findPath(int height, int width, ListNode* board[height][width], ListNode* start, ListNode* goal, char algorithm, bool pathing)
{
    setup(height, width,board, pathing);
    return Algorithms[tolower(algorithm)](height, width, board, start, goal);
}
