#include <iostream>
using namespace std;

#define N 4  // 4x4 Sudoku Grid

// Function to print Sudoku grid
void printGrid(int arr[N][N]) {
    cout << "\nSolved 4x4 Sudoku Grid:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
}

// Function to check if placing num is valid
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;

    // Check column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // Check 2x2 subgrid
    int startRow = row - row % 2, startCol = col - col % 2;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Recursive backtracking Sudoku solver
bool solveSudoku(int grid[N][N], int row, int col) {
    // If we reached the end of the grid
    if (row == N - 1 && col == N)
        return true;

    // Move to next row if at end of current one
    if (col == N) {
        row++;
        col = 0;
    }

    // Skip already filled cells
    if (grid[row][col] > 0)
        return solveSudoku(grid, row, col + 1);

    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid, row, col + 1))
                return true;
        }
        grid[row][col] = 0; // Backtrack
    }
    return false;
}

int main() {
    int grid[N][N];

    cout << "=== 4x4 Sudoku Solver (2x2 Subgrids) ===\n";
    cout << "Enter Sudoku Grid (use 0 for empty cells):\n";

    // Take user input
    for (int i = 0; i < N; i++) {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    cout << "\nInput Sudoku Grid:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }

    if (solveSudoku(grid, 0, 0))
        printGrid(grid);
    else
        cout << "\nNo solution exists for the given Sudoku grid.\n";

    return 0;
}
