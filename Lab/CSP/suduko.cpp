#include <stdio.h>

// --- Global Variables ---

// N is the size of the Sudoku grid (4x4)
#define N 4

// The 4x4 Sudoku grid. 0 represents an empty cell.
// This is a new, known solvable puzzle.
int grid[N][N] = {
    {0, 0, 3, 4},
    {3, 4, 0, 0},
    {1, 2, 0, 0},
    {0, 0, 1, 2}};

// --- Helper Functions ---

void printGrid()
{
    printf("Solved Sudoku:\n");
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            printf("%2d", grid[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if it's safe to place a number in a given cell.
int isSafe(int row, int col, int num)
{
    // Check if 'num' is already present in the current row
    for (int x = 0; x < N; x++)
    {
        if (grid[row][x] == num)
        {
            return 0; // Not safe
        }
    }

    // Check if 'num' is already present in the current column
    for (int x = 0; x < N; x++)
    {
        if (grid[x][col] == num)
        {
            return 0; // Not safe
        }
    }

    // Check if 'num' is already present in the 2x2 sub-grid
    int startRow = row - row % 2;
    int startCol = col - col % 2;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (grid[i + startRow][j + startCol] == num)
            {
                return 0; // Not safe
            }
        }
    }

    return 1; // Safe
}

// --- Backtracking Algorithm ---

// The main recursive function to solve the Sudoku puzzle.
int solveSudoku()
{
    int row = -1;
    int col = -1;
    int isEmpty = 1;

    // Find the first empty cell (value 0)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (grid[i][j] == 0)
            {
                row = i;
                col = j;
                isEmpty = 0; // We found an empty cell
                break;
            }
        }
        if (isEmpty == 0)
        {
            break;
        }
    }

    // Base Case: If there are no more empty cells, the puzzle is solved.
    if (isEmpty == 1)
    {
        return 1; // Success
    }

    // Try placing numbers from 1 to 4 in the empty cell
    for (int num = 1; num <= N; num++)
    {
        if (isSafe(row, col, num))
        {
            // Make the assignment
            grid[row][col] = num;

            // Recur to solve the rest of the puzzle
            if (solveSudoku() == 1)
            {
                return 1; // If it leads to a solution, great!
            }

            // If it doesn't lead to a solution, backtrack.
            grid[row][col] = 0;
        }
    }

    // This triggers backtracking
    return 0;
}

// --- Main Driver ---

int main()
{
    printf("--- 4x4 Sudoku Solver using Backtracking ---\n");
    printf("Initial Grid:\n");

    // A trick to use printGrid for the initial state without a separate function
    int tempGrid[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tempGrid[i][j] = grid[i][j];

    // Temporarily set grid to initial state for printing
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            printf("%2d", tempGrid[row][col]);
        }
        printf("\n");
    }
    printf("\n");

    if (solveSudoku() == 1)
    {
        printGrid();
    }
    else
    {
        printf("No solution exists for this Sudoku puzzle.\n");
    }

    return 0;
}
