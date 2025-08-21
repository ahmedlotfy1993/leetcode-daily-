/*
Problem:
--------
Given a binary matrix `mat` of size m x n, count the total number of submatrices (rectangles) 
that consist entirely of 1s.

A submatrix is any rectangular section of the matrix defined by a top-left and bottom-right corner.
We need to count all possible such submatrices where every cell is 1.
*/

/*
Approach (Dynamic Programming + Histogram Insight):
---------------------------------------------------
We process the matrix row by row and build a `dp` matrix where:
    dp[i][j] = number of consecutive 1s ending at position (i, j) in the current row.

This effectively builds a histogram of 1s for each row.

Then, for each cell (i, j) where mat[i][j] == 1:
    - We treat (i, j) as the bottom-right corner of submatrices.
    - We iterate upwards through rows `k = i ... 0`, checking how many rectangles can end at (i, j),
      by maintaining the minimum width of 1s from current row up to row `k`.
    - The number of submatrices ending at (i, j) that span from row k to i is equal to this min width.

By summing the min widths from each upward row step, we get the total number of submatrices
ending at each (i, j), and accumulate this into the `total`.

Time Complexity:
----------------
O(m * n * m) in the worst case (for each cell, we may traverse all rows above it).
This is acceptable for small to moderate matrix sizes.
*/
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        int total = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) continue;

                // Compute horizontal width of 1s ending at (i,j)
                dp[i][j] = j!=0? dp[i][j-1] + 1 : mat[i][j];

                // Count submatrices ending at (i,j)
                int minWidth =  dp[i][j];
                for (int k = i; k >= 0 && mat[k][j] == 1; --k) {
                    minWidth = min(minWidth, dp[k][j]);
                    total += minWidth;
                }
            }
        }

        return total;
    }
};
