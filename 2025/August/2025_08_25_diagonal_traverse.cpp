/*
Problem:
--------
You are given an m x n matrix `mat`. Your task is to return all elements of the matrix 
in diagonal order, following a zigzag pattern:

- Start from the top-left cell (0, 0).
- Move diagonally upward-right, then diagonally downward-left, and continue this alternating pattern.
- If you hit any boundary (top, bottom, left, or right), switch direction accordingly and continue.
- The traversal should cover every element of the matrix exactly once.

Example:
--------
Input:
mat = [
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output: [1,2,4,7,5,3,6,8,9]
*/
/*
Approach zigzag diagnoal trversal:
---------
1. Initialize the current position at (0, 0).
2. Use a boolean flag `isUpwardDiagonal` to alternate between the two directions:
   - Diagonally Up-Right: (row - 1, col + 1)
   - Diagonally Down-Left: (row + 1, col - 1)
3. Traverse each diagonal until going out of bounds.
4. After finishing one diagonal:
   - If the last direction was up:
     - Try moving right; if not possible (edge reached), move down.
   - If the last direction was down:
     - Try moving down; if not possible, move right.
5. Flip the direction flag.
6. Continue until you've covered all cells.

Time & Space Complexity:
------------------------
- Time: O(m * n), where m is the number of rows and n is the number of columns.
- Space: O(1) extra (excluding output vector).
*/
#define ZIGZAG_DIRECTIONAL_TRAVERSAL
#ifdef ZIGZAG_DIRECTIONAL_TRAVERSAL 
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        vector<int> result;
        int rows = mat.size();
        int cols = mat[0].size();
        int current_row = 0; 
        int current_col = 0;
        bool isUpwardDiagonal = true;

        while (current_row < rows || current_col < cols) {
            int diag_row = current_row;
            int diag_col = current_col;
            while (diag_row >= 0 && diag_row < rows && diag_col >= 0 && diag_col < cols) {
                result.push_back(mat[diag_row][diag_col]);
                current_row = diag_row; 
                current_col = diag_col;
                if (isUpwardDiagonal) {
                    diag_row -= 1;
                    diag_col += 1;
                } else {
                    diag_row += 1;
                    diag_col -= 1;
                }
            }
            if (isUpwardDiagonal) {
                if (current_col + 1 < cols) {
                    current_col += 1;
                } else {
                    current_row += 1;
                }
            } else {
                if (current_row + 1 < rows) {
                    current_row += 1;
                } else {
                    current_col += 1;
                }
            }

            isUpwardDiagonal = !isUpwardDiagonal;
        }

        return result;

    }
#endif 
/*
Approach diagonal grouping:
---------

1. We observe that all elements lying on the same diagonal (from top-left to bottom-right) 
   share the same sum of their indices (i + j).
2. Create a vector of vectors (`diagonals`) where index `i + j` holds all elements from that diagonal.
3. Traverse the matrix and fill the `diagonals` vector based on index sum.
4. To simulate the zigzag pattern:
   - Reverse every even-indexed diagonal group to match the "upward" direction.
   - Keep odd-indexed diagonal groups as is to match the "downward" direction.
5. Concatenate all diagonals in order to produce the final result.

Time Complexity: O(m * n) — each element is visited once and inserted into the result.
Space Complexity: O(m * n) — extra space used for the diagonals structure.
*/
#define DIAGONAL_GROUPING
#ifdef DIAGONAL_GROUPING
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> diagonals(m + n - 1);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                diagonals[i + j].push_back(mat[i][j]);
            }
        }
        vector<int> result;
        for (int k = 0; k < diagonals.size(); ++k) {
            if (k % 2 == 0) {
                reverse(diagonals[k].begin(), diagonals[k].end());
            }
            result.insert(result.end(), diagonals[k].begin(), diagonals[k].end());
        }
        return result;
    }
};
#endif
