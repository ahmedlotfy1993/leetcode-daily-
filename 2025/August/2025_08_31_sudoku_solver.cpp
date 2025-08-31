/*
Problem:
---------
We are tasked with solving a partially filled 9x9 Sudoku puzzle.  
The rules of Sudoku are:
1. Each row must contain digits 1–9 without repetition.
2. Each column must contain digits 1–9 without repetition.
3. Each 3x3 sub-grid (box) must contain digits 1–9 without repetition.
Empty cells are represented by '.' and need to be filled such that the Sudoku rules are satisfied.

Solution Approach (Backtracking):
---------------------------------
1. **Backtracking Recursion**:
   - Traverse the board cell by cell.
   - When an empty cell ('.') is found:
       - Try filling it with digits '1' to '9'.
       - For each digit, check if it's valid using Sudoku rules.
       - If valid, place the digit and recursively attempt to solve the rest of the board.
       - If the choice leads to a dead end, reset the cell (backtrack) and try the next digit.

2. **Validation Function**:
   - For a given cell (row, col), check:
       - Row: no duplicate of the current digit.
       - Column: no duplicate of the current digit.
       - 3x3 Sub-grid: no duplicate in its box.

3. **Base Case**:
   - If the entire board is traversed with all cells filled validly, return true.
   - If no digit fits in a cell, return false (triggers backtracking).

Complexity:
------------
- Time Complexity: O(9^(n)) in the worst case, where n is the number of empty cells 
  (each empty cell may try up to 9 possibilities).
- Space Complexity: O(1) → The board is modified in place; recursion depth ≤ 81.
*/

class Solution {
    bool isValid(vector<vector<char>>& board, int row, int col, char num) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == num) return false;
            if (board[i][col] == num) return false;
            int boxRow = 3 * (row / 3) + i / 3;
            int boxCol = 3 * (col / 3) + i % 3;
            if (board[boxRow][boxCol] == num) return false;
        }
        return true;
    }
    bool solve(vector<vector<char>>& board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == '.') { 
                    for (char num = '1'; num <= '9'; num++) {
                        if (isValid(board, row, col, num)) {
                            board[row][col] = num; 
                            if (solve(board)) 
                                return true; 
                            board[row][col] = '.'; 
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};
