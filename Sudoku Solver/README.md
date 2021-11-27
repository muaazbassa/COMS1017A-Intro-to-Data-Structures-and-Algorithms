# Sudoku Solver

I have coded a sudoku solver for a 9x9, 16x16 and 25x25 grid
* The program takes input via the terminal
* Zeros are spaces that need to be filled
* The program outputs the solved sudoku or "No Solution" where applicable

The Sudoku Solvers use Hidden/Naked Singles Technique to help speed up the solving of the problem. It was used to make the Time Complexity better.

Sample Input:
```c++
0 4 0 0 0 0 1 7 9
0 0 2 0 0 8 0 5 4
0 0 6 0 0 5 0 0 8
0 8 0 0 7 0 9 1 0
0 5 0 0 9 0 0 3 0
0 1 9 0 6 0 0 4 0
3 0 0 4 0 0 7 0 0
5 7 0 1 0 0 2 0 0
9 2 8 0 0 0 0 6 0 
```
Sample Output:
```c++
8 4 5 6 3 2 1 7 9
7 3 2 9 1 8 6 5 4
1 9 6 7 4 5 3 2 8
6 8 3 5 7 4 9 1 2
4 5 7 2 9 1 8 3 6
2 1 9 8 6 3 5 4 7
3 6 1 4 2 9 7 8 5
5 7 4 1 8 6 2 9 3
9 2 8 3 5 7 4 6 1
```
