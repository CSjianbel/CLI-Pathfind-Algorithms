CC = gcc
CFLAGS = -std=c11 -Wall -Werror 	

MAIN = pathfind

pathfind:

	$(CC) $(CFLAGS) -O3 -c -o assets/List.o src/List/List.c
	$(CC) $(CFLAGS) -O3 -c -o assets/pathfind.o src/pathfind.c
	$(CC) $(CFLAGS) -O3 -c -o assets/main.o src/main.c
	$(CC) $(CFLAGS) -O3 -o $(MAIN) assets/main.o assets/pathfind.o assets/List.o -lm

debug:

	$(CC) $(CFLAGS) -O0 -c -o assets/List.o src/List/List.c
	$(CC) $(CFLAGS) -O0 -c -o assets/pathfind.o src/pathfind.c
	$(CC) $(CFLAGS) -O0 -c -o assets/main.o src/main.c
	$(CC) $(CFLAGS) -O0 -ggdb3 -o $(MAIN) assets/main.o assets/pathfind.o assets/List.o -lm
