/*
    Problem Summary:
    ----------------
    You are given an m x n grid of integers and an integer k.
    Starting at (0,0), you can move only DOWN or RIGHT until you reach (m-1,n-1).
    A path is valid if the sum of values along the path is divisible by k.

    We must return the number of such valid paths modulo 1e9+7.

    Approach:
    ---------
    Use 3D Dynamic Programming:

        dp[i][j][r] = number of ways to reach cell (i,j)
                      such that the path sum % k == r.

    Transition:
        From top (i-1, j):
            dp[i][j][new_r] += dp[i-1][j][old_r]
        From left (i, j-1):
            dp[i][j][new_r] += dp[i][j-1][old_r]

        where:
            new_r = (old_r + grid[i][j] % k) % k

    Initialization:
        dp[0][0][grid[0][0] % k] = 1

    Final answer:
        dp[m-1][n-1][0]

    Time Complexity:
    ----------------
    O(m * n * k)  
    Because for each cell, we iterate over k remainders.

    Space Complexity:
    -----------------
    O(m * n * k)  
    Due to the dp table storing k states per cell.

*/

class Solution {
    static const int MOD = 1e9 + 7;
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k, 0)));

        dp[0][0][grid[0][0] % k] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0) continue;

                int val = grid[i][j] % k;

                // from TOP
                if (i > 0) {
                    for (int r = 0; r < k; r++) {
                        if (dp[i-1][j][r] == 0) continue;
                        int new_r = (r + val) % k;
                        dp[i][j][new_r] = (dp[i][j][new_r] + dp[i-1][j][r]) % MOD;
                    }
                }

                // from LEFT
                if (j > 0) {
                    for (int r = 0; r < k; r++) {
                        if (dp[i][j-1][r] == 0) continue;
                        int new_r = (r + val) % k;
                        dp[i][j][new_r] = (dp[i][j][new_r] + dp[i][j-1][r]) % MOD;
                    }
                }
            }
        }

        return dp[m-1][n-1][0];
    }
};
