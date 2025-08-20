/*
Problem: Count Square Submatrices with All Ones

Given an m x n binary matrix filled with 0s and 1s, return the total number of square submatrices that contain only 1s.
*/

/*
Approach: Dynamic Programming (DP)

We use a DP table where dp[i][j] represents the size of the largest square ending at position (i, j).

- If matrix[i][j] == 0 → dp[i][j] = 0 (cannot be part of any square)
- If matrix[i][j] == 1:
    - If i == 0 or j == 0 → dp[i][j] = 1 (border cells can only form 1x1 square)
    - Else → dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
      (we can extend the minimum-sized square formed by top, left, and top-left neighbors)

The total count of square submatrices is the sum of all values in the dp table.

Time Complexity: O(m * n)
Space Complexity: O(m * n)
*/
#define TWO_DIMINSION_ARRAY_DYNAMIC_PROGRAMMING
#ifdef TWO_DIMINSION_ARRAY_DYNAMIC_PROGRAMMING
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int row_num = matrix.size();
        int col_num = matrix[0].size();
        vector<vector<int>>dp(row_num, vector<int>(col_num, 0));
        int result = 0;
        for(int i = 0; i < row_num; i++){
            for(int j = 0; j < col_num; j++){
                if(i == 0 || j == 0){
                    dp[i][j] = matrix[i][j];
                }else if(matrix[i][j]){
                    int min_val = min(dp[i-1][j], min(dp[i][j - 1], dp[i-1][j-1]));
                    dp[i][j] = matrix[i][j] + min_val;
                }
                result += dp[i][j];
            }
        }
        return result;
    }
};
#endif

/*
Optimized Space Version of: Count Square Submatrices with All Ones

We optimize the DP solution by using a single row instead of a full 2D matrix.
- Instead of maintaining a 2D dp table, we use a 1D array `dp[col_num]`.
- We also track the previous value of `dp[j-1]` from the last row using a variable `prev`.

For each cell (i, j):
- If matrix[i][j] == 1:
    - If i == 0 or j == 0 → dp[j] = 1
    - Else → dp[j] = 1 + min(dp[j], dp[j-1], prev)
      where:
        - dp[j] is the value from the previous row (top)
        - dp[j-1] is the current row (left)
        - prev is dp[j-1] from the previous row (top-left)
- If matrix[i][j] == 0 → dp[j] = 0

We update the result by summing dp[j] values during each iteration.

Time Complexity: O(m * n)
Space Complexity: O(n)
*/
#define ONE_DIMINSION_ARRAY_DYNAMIC_PROGRAMMING
#ifdef ONE_DIMINSION_ARRAY_DYNAMIC_PROGRAMMING
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int row_num = matrix.size();
        int col_num = matrix[0].size();
        vector<int> dp(col_num, 0);
        int result = 0;
        int prev = 0;

        for (int i = 0; i < row_num; ++i) {
            prev = 0;  
            for (int j = 0; j < col_num; ++j) {
                int temp = dp[j]; 
                if (matrix[i][j] == 1) {
                    if (i == 0 || j == 0) {
                        dp[j] = 1;
                    } else {
                        dp[j] = 1 + min({dp[j], dp[j - 1], prev});
                    }
                    result += dp[j];
                } else {
                    dp[j] = 0;
                }
                prev = temp; 
            }
        }
        return result;
    }
};
#endif
