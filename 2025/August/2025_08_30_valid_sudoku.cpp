/*
Problem:
---------
We are given a partially filled 9x9 Sudoku board. The task is to determine whether it is valid 
based on Sudoku rules:
1. Each row must contain digits 1-9 without repetition.
2. Each column must contain digits 1-9 without repetition.
3. Each of the nine 3x3 sub-boxes must contain digits 1-9 without repetition.
Note:
- The board may be only partially filled, represented with '.' for empty cells.
- The problem only asks for validity, not solvability.
*/

/*
Solution Approach:
-------------------
1. Row and Column Validation:
   - Iterate over each row and column.
   - Use a hash map (unordered_map<char,int>) to track occurrences of digits.
   - If a digit appears more than once in a row or a column, return false.

2. 3x3 Sub-box Validation:
   - There are 9 sub-boxes, each identified by (boxIndex = 0..8).
   - For each sub-box, determine its starting coordinates:
       startRow = (box / 3) * 3
       startCol = (box % 3) * 3
   - Traverse the 3x3 region, track digits using another hash map.
   - If any digit repeats in the sub-box, return false.

3. If no conflicts are found in rows, columns, or sub-boxes, return true.

Complexity:
------------
- Time Complexity: O(9 * 9) = O(1) → constant work since the board size is fixed.
- Space Complexity: O(1) → at most 27 hash maps storing counts of digits (limited set {1-9}).

This solution prioritizes clarity with hash maps, though boolean arrays could be used for efficiency.
*/

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for (int row = 0; row < 9; row++) {
            unordered_map<char, int> rowCount;
            unordered_map<char, int> colCount;
            for (int col = 0; col < 9; col++) {
                char cellInRow = board[row][col];
                if (cellInRow != '.') {
                    rowCount[cellInRow]++;
                    if (rowCount[cellInRow] > 1) return false;
                }
                char cellInCol = board[col][row];
                if (cellInCol != '.') {
                    colCount[cellInCol]++;
                    if (colCount[cellInCol] > 1) return false;
                }
            }
        }

        for (int box = 0; box < 9; box++) {
            int startRow = (box / 3) * 3;
            int startCol = (box % 3) * 3;
            unordered_map<char, int> boxCount;

            for (int dRow = 0; dRow < 3; dRow++) {
                for (int dCol = 0; dCol < 3; dCol++) {
                    int row = startRow + dRow;
                    int col = startCol + dCol;
                    char cell = board[row][col];
                    if (cell != '.') {
                        boxCount[cell]++;
                        if (boxCount[cell] > 1) return false;
                    }
                }
            }
        }

        return true;
    }
};
