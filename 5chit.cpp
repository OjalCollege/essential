#include <iostream>
#include <vector>

using namespace std;

// Function to check if it's safe to place a queen at board[row][col]
bool isSafe(vector<vector<int>> &board, int row, int col, int n)
{
    // Check this row on the left side
    for (int i = 0; i < col; i++)
    {
        if (board[row][i] == 1)
            return false;
    }

    // Check the upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
            return false;
    }

    // Check the lower diagonal on the left side
    for (int i = row, j = col; j >= 0 && i < n; i++, j--)
    {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

// Recursive utility function to solve the N-Queens problem
bool solveNQueensUtil(vector<vector<int>> &board, int col, int n)
{
    // Base case: If all queens are placed
    if (col >= n)
        return true;

    // Try placing the queen in each row one by one
    for (int i = 0; i < n; i++)
    {
        if (isSafe(board, i, col, n))
        {                      // Check if queen can be placed
            board[i][col] = 1; // Place queen

            // Recur to place queens in the rest of the columns
            if (solveNQueensUtil(board, col + 1, n))
                return true;

            // If placing queen doesn't lead to a solution, remove queen
            board[i][col] = 0;
        }
    }

    return false; // If the queen can't be placed in any row
}

// Function to solve the N-Queens problem
void solveNQueens(int n)
{
    vector<vector<int>> board(n, vector<int>(n, 0)); // Initialize board

    if (!solveNQueensUtil(board, 0, n))
    {
        cout << "Solution does not exist" << endl;
        return;
    }

    // Print the solution
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
}

int main()
{
    int n = 4; // Size of the board (4x4)
    solveNQueens(n);

    return 0;
}
