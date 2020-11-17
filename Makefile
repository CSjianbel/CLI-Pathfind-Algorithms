CC = gcc
CFLAGS = -std=c11 -Wall -Werror 	

OUT = pathfind

pathfind:

	$(CC) $(CFLAGS) -O3 -c -o assets/List.o src/List/List.c
	$(CC) $(CFLAGS) -O3 -c -o assets/pathfind.o src/pathfind.c
	$(CC) $(CFLAGS) -O3 -c -o assets/main.o src/main.c
	$(CC) $(CFLAGS) -O3 -o $(OUT) assets/main.o assets/pathfind.o assets/List.o -lm

debug:

	$(CC) $(CFLAGS) -O0 -c -o assets/List.o src/List/List.c
	$(CC) $(CFLAGS) -O0 -c -o assets/pathfind.o src/pathfind.c
	$(CC) $(CFLAGS) -O0 -c -o assets/main.o src/main.c
	$(CC) $(CFLAGS) -O0 -ggdb3 -o $(OUT) assets/main.o assets/pathfind.o assets/List.o -lm

clean:

	rm -f $(OUT)
	rm -rf assets
	mkdir assets