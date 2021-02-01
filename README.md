# CLI Pathfind Algorithms

Command Line Program implementation of different Search algorithms in C.<br />
Namely A\*, Depth First Search and lastly Breadth First Search.<br />
Recreating the List Data Structure to utilize for the algorithms.<br />

## Clone

```bash
git clone "https://github.com/CSjianbel/CLI-Pathfind-Algorithms.git"
```

## Build

```bash
make pathfind
```

## Usage

```bash
./pathfind [Pathing] [Algorithm] [Board]

./pathfind [-a, -d] [-a, -d, -b] [structure.txt]

./pathfind -a -d src/Tests/test1.txt

./pathfind -d src/Tests/test2.txt

./pathfind src/Tests/test3.txt
```

- Pathing

  - _-a_ Sets Pathing to Across Only
  - _-d_ Sets Pathing to Across & Diagonal

- Algorithm

  - _-a_ Sets A\* Search as the algorithm to be used
  - _-d_ Sets Depth First Search as the algorithm to be used
  - _-b_ Sets Breadth First search as the algorithm to be used

- Board

  - _structure.txt_ must be a path to a board

- Defaults

  - The program is set to across and diagonal if the 2nd & 3rd command line argument is ommitted.
  - The program is set to A\* search if the 3rd command line argument is ommitted.

- Note

  - The Board is the only command line argument that is required when running the program.
  - To be able to specify the algorithm then all 4 command line arguments must be provided.

## Creating a board

Inside the **src/Tests/** directory there exists test boards that may be utilized for testing.<br />
Inside the **src/Tests/Invalid** directory there exists test boards that are deemed to be invalid by the program.<br />

Here are a few guidelines in Creating a Board of your own...<br />

Create a _.txt_ file and fill it with the following characters:<br />

- ['S', 's'] : Start Node
- ['E', 'e'] : End Node
- '#' : Wall
- '\_' : Open Path

### Rules

- The Start Node and End Node Characters must only appear once in the board to be a valid board.<br />
- The Width of each row of the board must be symmetrical to be a valid board.<br />
- If there are characters present in the board that are not mentioned above then it will be an invalid board.<br />
- The Max Width of the Board is set to be 50, anything above that is considered invalid. This can be changed in <u>src/pathfind.h</u>.<br />

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

_A Project by Jiankarlo A. Belarmino_
