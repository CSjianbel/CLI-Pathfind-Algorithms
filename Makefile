CC = gcc
CFLAGS = -std=c11 -Wall -Werror -O3
CFLAGSD = -std=c11 -Wall -Werror -O0

OUT = pathfind

pathfind:

	$(CC) $(CFLAGS) -c -o assets/List.o src/List/List.c
	$(CC) $(CFLAGS) -c -o assets/pathfind.o src/pathfind.c
	$(CC) $(CFLAGS) -c -o assets/main.o src/main.c
	$(CC) $(CFLAGS) -o $(OUT) assets/main.o assets/pathfind.o assets/List.o -lm

debug:

	$(CC) $(CFLAGSD) -c -o assets/List.o src/List/List.c
	$(CC) $(CFLAGSD) -c -o assets/pathfind.o src/pathfind.c
	$(CC) $(CFLAGSD) -c -o assets/main.o src/main.c
	$(CC) $(CFLAGSD) -ggdb3 -o $(OUT) assets/main.o assets/pathfind.o assets/List.o -lm

clean:

	rm -f $(OUT)
	rm -rf assets
	mkdir assets
