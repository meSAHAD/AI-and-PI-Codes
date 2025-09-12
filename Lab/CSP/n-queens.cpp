#include <stdio.h>

// --- Global Variables ---

// N is the size of the board and the number of queens
#define N 4

// board[N][N] is the chessboard.
// A 1 indicates a queen, and a 0 indicates an empty square.
int board[N][N] = {0};

// --- Helper Functions ---

// Function to print the board
void printBoard()
{
    printf("Solution Found:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if it's safe to place a queen at board[row][col].
// We only need to check the left side for attacking queens because
// we are filling columns from left to right.
int isSafe(int row, int col)
{
    int i, j;

    // Check this row on the left side
    for (i = 0; i < col; i++)
    {
        if (board[row][i] == 1)
        {
            return 0; // Not safe
        }
    }

    // Check upper diagonal on the left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
        {
            return 0; // Not safe
        }
    }

    // Check lower diagonal on the left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
    {
        if (board[i][j] == 1)
        {
            return 0; // Not safe
        }
    }

    return 1; // Safe
}

// --- Backtracking Algorithm ---

// The main recursive function to solve the N-Queens problem.
// It tries to place queens in columns one by one, starting from 'col'.
int solveNQueens(int col)
{
    // Base Case: If all queens are placed, we have a solution.
    if (col >= N)
    {
        printBoard();
        return 1; // Return true
    }

    // Try placing a queen in each row of the current column
    for (int i = 0; i < N; i++)
    {
        // Check if it's safe to place the queen here
        if (isSafe(i, col))
        {
            // Place the queen
            board[i][col] = 1;

            // Recur to place the rest of the queens
            if (solveNQueens(col + 1) == 1)
            {
                return 1;
            }

            // If placing the queen here doesn't lead to a solution,
            // then backtrack and remove the queen from the board.
            board[i][col] = 0;
        }
    }

    // If a queen cannot be placed in any row of this column, return false.
    return 0;
}

// --- Main Driver ---

int main()
{
    printf("--- N-Queens Problem using Backtracking ---\n");

    if (solveNQueens(0) == 0)
    {
        printf("No solution exists for N = %d.\n", N);
    }

    return 0;
}
