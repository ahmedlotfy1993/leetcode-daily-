/*
--------------------------------------------------------------------------------
Problem:
You are given a convex polygon with `n` vertices, where each vertex has 
an integer value. The polygon must be triangulated into `n - 2` triangles, 
and the weight of a triangle is defined as the product of the values of 
its three vertices. The total score of a triangulation is the sum of 
weights of all `n - 2` triangles.  
Return the minimum possible score among all triangulations.

--------------------------------------------------------------------------------
Key Insight:
- Since the polygon is convex, any triangulation is valid.
- This is a classic **interval DP problem** (similar to Matrix Chain Multiplication).
- To minimize the score, we must carefully decide which vertex `k` to use as the 
  "divider" between vertices `i` and `j`.

--------------------------------------------------------------------------------
Approaches:

1) **Bottom-up DP (Tabulation)**  
   - Define dp[i][j] as the minimum score to triangulate the polygon 
     formed by vertices i..j.  
   - Transition:  
        dp[i][j] = min( dp[i][k] + dp[k][j] + values[i] * values[j] * values[k] )  
        for all i < k < j.  
   - Answer is dp[0][n-1].

   Time Complexity: O(n^3)  
   Space Complexity: O(n^2)

2) **Top-down DP (Memoized Recursion)**
   - Recursive function `solve(i, j)` returns the minimum triangulation 
     score for the polygon from i..j.  
   - Base case: if (j - i < 2), no triangle can be formed → return 0.  
   - Transition: same recurrence as above.  
   - Use memoization to cache results.  

   Time Complexity: O(n^3)  
   Space Complexity: O(n^2) (for memo + recursion stack)

--------------------------------------------------------------------------------
*/
#define BOTTOM_UP_DP 1
#define MEMORIZATION_RECURSION 2
class Solution {
#ifdef MEMORIZATION_RECURSION
    int solve(int i, int j, vector<int>& values, vector<vector<int>>& memo) {
        if (j - i < 2) return 0;

        if (memo[i][j] != -1) return memo[i][j];

        int ans = INT_MAX;
        for (int k = i + 1; k < j; k++) {
            int left = solve(i, k, values, memo);
            int right = solve(k, j, values, memo);
            int cost = values[i] * values[j] * values[k] + left + right;
            ans = min(ans, cost);
        }
        return memo[i][j] = ans;
    }
#endif
public:
    int minScoreTriangulation(vector<int>& values) {
      #if MEMORIZATION_RECURSION
        int n = values.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        return solve(0, n - 1, values, memo);
      #endif
      #if BOTTOM_UP_DP
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                for (int k = i + 1; k < j; k++) {
                    int score = dp[i][k] + dp[k][j] + values[i] * values[k] * values[j];
                    dp[i][j] = min(dp[i][j], score);
                }
            }
        }
        return dp[0][n - 1];
      #endif
    }
};
