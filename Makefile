pathfind:
	gcc -O3 -std=c11 -Wall -Werror -c -o src/List.o src/List/List.c
	gcc -O3 -std=c11 -Wall -Werror -c -o src/pathfind.o src/pathfind.c
	gcc -O3 -std=c11 -Wall -Werror -c -o src/main.o src/main.c
	gcc -O3 -std=c11 -Wall -Werror -o main src/main.o src/pathfind.o src/List.o -lm
