CC = gcc
CFLAGS = -std=c11 -Wall -Werror -O3
CFLAGSD = -std=c11 -Wall -Werror -O0 -ggdb3

OUT = pathfind

pathfind: 

	mkdir -p assets
	$(CC) $(CFLAGS) -c -o assets/List.o src/List/List.c
	$(CC) $(CFLAGS) -c -o assets/pathfind.o src/Pathfind/pathfind.c
	$(CC) $(CFLAGS) -c -o assets/board.o src/Board/board.c
	$(CC) $(CFLAGS) -c -o assets/main.o src/main.c
	$(CC) $(CFLAGS) -o $(OUT) assets/main.o assets/pathfind.o assets/board.o assets/List.o -lm

debug:

	mkdir -p assets
	$(CC) $(CFLAGSD) -c -o assets/List.o src/List/List.c
	$(CC) $(CFLAGSD) -c -o assets/pathfind.o src/Pathfind/pathfind.c
	$(CC) $(CFLAGSD) -c -o assets/board.o src/Board/board.c
	$(CC) $(CFLAGSD) -c -o assets/main.o src/main.c
	$(CC) $(CFLAGSD) -o $(OUT) assets/main.o assets/pathfind.o assets/board.o assets/List.o -lm

clean:

	rm $(OUT)
	rm -rf assets
	mkdir assets
