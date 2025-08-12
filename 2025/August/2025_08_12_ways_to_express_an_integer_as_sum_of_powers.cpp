/*
Problem:
--------
Given two positive integers n and x, the task is to count the number of ways 
to express n as the sum of x-th powers of unique positive integers.

Formally, find the number of distinct sets [a1, a2, ..., ak] such that:
    a1^x + a2^x + ... + ak^x = n
Each ai must be unique and positive.

Example:
    Input: n = 160, x = 3
    Output: 1
    Explanation: 160 = 2^3 + 3^3 + 5^3
*/

/*
Solution:
---------
This problem is a variation of the classic 0/1 Knapsack problem. 
We use dynamic programming (DP) to build the number of ways to reach each 
sum up to n using unique numbers raised to power x.

Key Ideas:
- dp[i] stores the number of ways to reach sum i.
- Initialize dp[0] = 1 (1 way to sum to 0 — use nothing).
- Iterate through possible bases (1^x, 2^x, ...) as candidates.
- For each base^x, update the dp array from i = n down to base^x to 
  ensure each number is used at most once (0/1 knapsack behavior).

Time Complexity:
- O(n * sqrt(x)(approx)), since we iterate over all powers ≤ n and update the dp array.

Space Complexity:
- O(n), as we only store a 1D DP array.

This approach ensures correctness and avoids overcounting by only allowing 
each base to contribute once to each sum.
*/
class Solution {
    static constexpr int MOD = 1e9 + 7;
public:
    int numberOfWays(int n, int x) {
        vector<int>dp(n + 1,0);
        dp[0] = 1;
        int base = 1;
        int power = 1;
        while (power <= n){
            for(int i = n; i>=power; i--){
                dp[i] = (dp[i] + dp[i - power]) % MOD;
            }
            power = pow(++base, x);
        }
        return dp[n];
    }
};
