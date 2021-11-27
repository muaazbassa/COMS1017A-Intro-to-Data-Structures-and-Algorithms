# Breath First Search - The Shortest Path in a Maze

I have coded a program that finds the shortest path in a maze using the Breath First Search algorithm

* The program takes in input via the terminal 
* The first line will contain 2 integers, ```m``` and ```n```, separated by a space. These numbers represent the number of rows and columns in the grid respectively.
* There will then be ```m``` lines each with n columns that represent the maze.
* A ```space``` represents an open block in the world. You may travel through this block.
* An ```x``` represents an obstacle. You may not travel through this block.
* An ```S``` represents the start.
* A ```G``` represents the goal.
* The output should be the maze with ```*``` characters along the shortest path from the start to the goal. 1 If there is no path between the start and goal, then the output should say ```No Path```.

## Sample Input:
```
14 17
xxxxxxxxxxxxxxxxx
x               x
x               x
x            S  x
x               x
x               x
x               x
x               x
x  xxxxxxxxx    x
x          x    x
x  x xxxx  x    x
x  x      Gx    x
x  x            x
xxxxxxxxxxxxxxxxx
```

## Sample Output:
```
xxxxxxxxxxxxxxxxx
x               x
x               x
x            S  x
x            *  x
x            *  x
x            *  x
x            *  x
x  xxxxxxxxx *  x
x          x *  x
x  x xxxx  x *  x
x  x      Gx *  x
x  x      ****  x
xxxxxxxxxxxxxxxxx
```
