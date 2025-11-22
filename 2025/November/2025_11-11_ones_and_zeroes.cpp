/*
    Problem:
    You are given an array of binary strings `strs` and two integers `m` and `n`.
    Each string contains zeros and ones.
    You must pick the largest possible subset such that:
        - total zeros used ≤ m
        - total ones used  ≤ n
    This is a classic "0/1 knapsack" with TWO weight constraints (zeros & ones).

    Approach:
    - `dp[i][j]` represents the maximum number of strings that can be formed using
      at most `i` zeros and `j` ones.
    - For each string, compute (zeros, ones).
    - Iterate DP **backwards** from (m → zeros) and (n → ones) to ensure each string
      is counted at most once (0/1 knapsack rule).
    - Transition:
            dp[i][j] = max(dp[i][j], dp[i - zeros][j - ones] + 1)

    Time Complexity:
        O(S * m * n)
        where S = number of strings

    Space Complexity:
        O(m * n)

*/

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (const string& s : strs) {
            int zeros = count(s.begin(), s.end(), '0');
            int ones  = s.size() - zeros;

            // iterate backwards (0/1 knapsack)
            for (int i = m; i >= zeros; --i) {
                for (int j = n; j >= ones; --j) {
                    dp[i][j] = max(dp[i][j], dp[i - zeros][j - ones] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
