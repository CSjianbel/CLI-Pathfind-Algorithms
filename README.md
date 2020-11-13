# CLI A* Pathfinding Algorithm
 
Command Line Program version of the A* pathfinding Algorithm written in C<br />
Recreating a List Data Structure to utilize for the algorithm.<br /> 

## Clone
```bash
	git clone "https://github.com/CSjianbel/CLI-A-Star-Algorithm.git"
```

## Build

Unix Based Systems:
```bash
	make pathfind
```

Windows: 
```
	gcc -O3 -std=c11 -Wall -Werror -c -o assets/List.o src/List/List.c
	gcc -O3 -std=c11 -Wall -Werror -c -o assets/pathfind.o src/pathfind.c
	gcc -O3 -std=c11 -Wall -Werror -c -o assets/main.o src/main.c
	gcc -O3 -std=c11 -Wall -Werror -o pathfind assets/main.o assets/pathfind.o assets/List.o -lm
```

## Usage
```bash
	./pathfind [-d, -a] [structure.txt]
```

* _-d_ Sets Pathing to Across & Diagonal
* _-a_ Sets Pathing to Across Only
* _structure.txt_ must be a path to a board

By default the program utilizes across and diagonal if the 2nd command line argument is ommitted

## Creating a board

Create a _.txt_ file and fill it with the following characters:

* [S, s] : Start Node
* [E, e] : End Node
* \# : Wall
* _ : Open Path

### Rules

The Start Node and End Node Characters must only appear once in the board to be a valid board.<br />
The Width of each row of the board must be symmetrical to be a valid board.<br />
If there are characters present in the board that are not mentioned above then it will be an invalid board<br />

#### Sample Valid Board

```
S####
____#
###_E
```

#### Sample Invalid Board

```
S###X
_ASD
##E##
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change. 

## License 
[MIT](https://choosealicense.com/licenses/mit/)

*A Project by Jiankarlo A. Belarmino*

