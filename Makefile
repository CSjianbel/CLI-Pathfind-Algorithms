pathfind:
	gcc -O3 -std=c11 -Wall -Werror -c -o assets/List.o src/List/List.c
	gcc -O3 -std=c11 -Wall -Werror -c -o assets/pathfind.o src/pathfind.c
	gcc -O3 -std=c11 -Wall -Werror -c -o assets/main.o src/main.c
	gcc -O3 -std=c11 -Wall -Werror -o pathfind assets/main.o assets/pathfind.o assets/List.o -lm
