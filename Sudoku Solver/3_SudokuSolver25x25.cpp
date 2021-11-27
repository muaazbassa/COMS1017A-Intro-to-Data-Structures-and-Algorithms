//Mu'aaz Bassa
//Project 1: Sudoku (25x25)
#include <iostream>

using namespace std;

// optimization "Ofast" - https://www.geeksforgeeks.org/speed-up-naive-algorithms-in-competitive-coding-in-c-cpp/
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

//Constants used 25x25 
const int n=25; 
const int sqrn=5;

//Functions used
int EmptyCells();
void Singles();
int NakedSingle();
bool CheckConflict(int i, int j);
bool isLegal(int sudoku[n][n], int row, int col, int num);
bool Solve(int sudoku[n][n], int row);
void print(int sudoku[n][n]);

int sudoku[n][n] = {0}; //Initializing sudoku as an empty array

//Link to website that helped me understand this technique of solving a sudoku
/*  http://hodoku.sourceforge.net/en/tech_singles.php#:~:text=Naked%20Single%20means%20that%20in,behind%20and%20is%20thus%20naked)
    .&text=In%20the%20sudoku%20on%20the,there%20and%20can%20be%20placed.
*/

//Youtube Channel used for research
/*
https://www.youtube.com/channel/UC2N60jDPloV5_imTYKIVH2Q
*/


//single functions - technique used to solve sudoku - speeds up the run time of the code
int NakedSingle()
//This function tries to fill 1 to n (n = 25) at every empty cell in each row 
//If only one of the numbers is possible then it updates the cell 
//If some cells were filled after first loop it loops again to check for more available/possible places to insert
{
    int EmptyCellsPrev = 0;
    while (EmptyCellsPrev != EmptyCells())
    {
        EmptyCellsPrev = EmptyCells();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int possible_guesses = 0;
                int Value = 0;
                if (sudoku[i][j] == 0)
                {
                    for (int guess = 1; guess <= n; guess++)
                    {
                        sudoku[i][j] = guess;
                        if (!CheckConflict(i, j))
                        {
                            possible_guesses++;
                            Value = guess;
                        }
                    }
                    if (possible_guesses != 1)
                    {
                        sudoku[i][j] = 0;
                    }
                    else
                    {
                        sudoku[i][j] = Value;
                    }
                }
            }
        }
    }
    return 0;
}
void ColumnHiddenSingle()
//Finds the values from 1-n (n = 25) which can only be filled in one cell in given column, goes through every column
{
    int z = 0;
    while (z != EmptyCells())
    {
        z = EmptyCells();
        for (int i = 0; i < n; i++)
        {
            for (int k = 1; k <= n; k++)
            {
                int Col = 0;
                int NumPos = 0;
                for (int j = 0; j < n; j++)
                {
                    if (sudoku[i][j] == 0)
                    {
                        sudoku[i][j] = k;
                        if (!CheckConflict(i, j))
                        {
                            NumPos++;
                            Col = j;
                        }
                        sudoku[i][j] = 0;
                    }
                }
                if (NumPos == 1)
                {
                    sudoku[i][Col] = k;
                }
            }
        }
    }
}

void RowHiddenSingle()
/*Finds the values from 1-n (n = 25) which can only be filled in one cell in given row,
the function iterates for all the row*/
{
    int z = 0;
    while (z != EmptyCells())
    {
        z = EmptyCells();
        for (int j = 0; j < n; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                int Row = 0;
                int NumPos = 0;
                for (int i = 0; i < n; i++)
                {
                    if (sudoku[i][j] == 0)
                    {
                        sudoku[i][j] = k;
                        if (!CheckConflict(i, j))
                        {
                            NumPos++;
                            Row = i;
                        }
                        sudoku[i][j] = 0;
                    }
                }
                if (NumPos == 1)
                {
                    sudoku[Row][j] = k;
                }
            }
        }
    }
}

void BoxHiddenSingle()
/*Finds the values from 1-n (n = 25) which can only be filled in one cell in given sqrnxsqrn (sqrn = 4) box,
its loops through all all boxes*/
{
    int z = 0;
    while (z != EmptyCells())
    {
        z = EmptyCells();
        for (int boxi = 0; boxi < sqrn; boxi++)
        {
            for (int boxj = 0; boxj < sqrn; boxj++)
            {
                for (int k = 1; k <= n; k++)
                {
                    int Row = 0;
                    int Col = 0;
                    int NumPos = 0;
                    for (int a = boxi * sqrn; a < boxi * sqrn + sqrn; a++)
                    {
                        for (int b = boxj * sqrn; b < boxj * sqrn + sqrn; b++)
                        {
                            if (sudoku[a][b] == 0)
                            {
                                sudoku[a][b] = k;
                                if (!CheckConflict(a, b))
                                {
                                    NumPos++;
                                    Row = a;
                                    Col = b;
                                }
                                sudoku[a][b] = 0;
                            }
                        }
                    }
                    if (NumPos == 1)
                    {
                        sudoku[Row][Col] = k;
                    }
                }
            }
        }
    }
}

void HiddenSingle()
// Running all three components of the HiddenSingle technique
{
    ColumnHiddenSingle();
    RowHiddenSingle();
    BoxHiddenSingle();
}

void Singles()
// Running both naked singles and hidden singles techniques till they fill what they can
{
    int i = 1;
    while (i != EmptyCells())
    {
        i = EmptyCells();
        NakedSingle();
        HiddenSingle();
    }
}
////////////////////////////////

///function used in the singles
bool CheckConflict(int i, int j)
//returns true if the current value of sudoku[i][j] results in a issue
{
    bool conflict = false;
    int k = sudoku[i][j];
    for (int a = 0; a <= (n-1); a++)
    {
        if (sudoku[i][a] == k && a != j)
        {
            conflict = true;
        }
        if (sudoku[a][j] == k && a != i)
        {
            conflict = true;
        }
    }
    int boxi = i / sqrn;
    int boxj = j / sqrn;
    for (int a = boxi * sqrn; a <= boxi * sqrn + (sqrn-1); a++)
    {
        for (int b = boxj * sqrn; b <= boxj * sqrn + (sqrn-1); b++)
        {
            if (sudoku[a][b] == k && a != i && b != j)
            {
                conflict = true;
            }
        }
    }
    return conflict;
}
///function used in the singles
int EmptyCells()
/*returns number of empty cells in sudoku*/
{
    int NumOfZero = 0;
    for (int i = 0; i <= (n-1); i++)
    {
        for (int j = 0; j <= (n-1); j++)
        {
            if (sudoku[i][j] == 0)
                NumOfZero++;
        }
    }
    return NumOfZero;
}

bool CompletionCheck(int sudoku[n][n], int &row, int &col)
{
    for (row; row < n; ++row)
    {
        for (col = 0; col < n; ++col)
        {
            if (sudoku[row][col] == 0)
            {
                return false;
            }
        }
    }
    return true;
}
// Returns whether it will be legal to assign num to the given row,col location. 
bool isLegal(int sudoku[n][n], int row, int col, int num)
{
    for (int i = 0; i < n; ++i)
    {
        if (sudoku[row][i] == num || sudoku[i][col] == num)
        {
            return 0;
        }
    }
    int boxrow = row - row % sqrn;
    int boxcol = col - col % sqrn;
    for (int r = 0; r < sqrn; ++r)
    {
        for (int c = 0; c < sqrn; ++c)
        {
            if (sudoku[r + boxrow][c + boxcol] == num)
            {
                return 0;
            }
        }
    }
    return 1;
}

bool Solve(int sudoku[n][n], int row)
{
    int col;
    //if (EmptyCells()==0)
    if (CompletionCheck(sudoku, row, col))
    {
        return true;
    }
    for (int num = 1; num <= n; ++num)
    {   
        if (isLegal(sudoku, row, col, num))
        {
            sudoku[row][col] = num;
            if (Solve(sudoku, row))
            {
                return 1;
            }
            sudoku[row][col] = 0;
        }
    }
    return false;
}

void print(int sudoku[n][n])
{
    for (int r = 0; r < n; ++r)
    {
        if (sudoku[r][0] > 9)
        {
            char out = (char)(sudoku[r][0] + 55);
            cout << out;
        }
        else
        {
            cout << sudoku[r][0];
        }
        for (int c = 1; c < n; ++c)
        {
            if (sudoku[r][c] > 9)
            {
                char out = (char)(sudoku[r][c] + 55);
                cout << ' ' << out;
            }
            else
            {
                cout << ' ' << sudoku[r][c];
            }
        }
        cout << endl;
    }
}

int main()
{
 /*
    int sudoku[25][25] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    */

for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            char n;
            cin >> n;
            int num = n;
            if (num < 65)
            {
                sudoku[row][col] = num - 48;
            }
            else
            {
                sudoku[row][col] = num - 55;
            }
        }
    }
    Singles();
    NakedSingle();
    if (Solve(sudoku, 0))
    {
        print(sudoku);
    }
    else
    {
        cout << "No Solution" << endl;
    }

    return 0;
}
