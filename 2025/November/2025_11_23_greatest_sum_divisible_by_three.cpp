/*
    Problem Summary:
    ----------------
    You are given an integer array nums.  
    Your task is to compute the **maximum sum of elements** such that the final sum is **divisible by 3**.

    Approach (Dynamic Programming on Remainders):
    ---------------------------------------------
    We maintain a DP array `dp[3]` where:
        dp[r] = maximum sum achievable so far whose remainder is r (mod 3).

    Initialization:
        dp = {0, -1, -1}
        - dp[0] = 0  → sum 0 is divisible by 3
        - dp[1] = dp[2] = -1 → impossible states at start

    For each number `num`:
        - Compute remainder r = num % 3
        - Update dp states using a temporary array next_dp
        - For each old state dp[x], update:
            next_dp[(x + r) % 3] = max(next_dp[(x + r) % 3], dp[x] + num)

    Finally:
        - The answer must be dp[0], the max sum divisible by 3.

    Why this works:
    ----------------
    We consider all possible sums modulo 3 and take the maximum valid sum for each remainder class.

    Time Complexity:
    ----------------
    O(n), because for each element we only update 3 states.

    Space Complexity:
    -----------------
    O(1), constant DP array of size 3.
*/

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        vector<int> dp{0, -1, -1};   // dp[r] = max sum with remainder r

        for(int num : nums){
            int r = num % 3;
            vector<int> next_dp = dp;

            // Try appending num to each valid previous state
            if (dp[0] != -1) next_dp[(0 + r) % 3] = max(next_dp[(0 + r) % 3], dp[0] + num);
            if (dp[1] != -1) next_dp[(1 + r) % 3] = max(next_dp[(1 + r) % 3], dp[1] + num);
            if (dp[2] != -1) next_dp[(2 + r) % 3] = max(next_dp[(2 + r) % 3], dp[2] + num);

            dp = next_dp;
        }

        return dp[0];   // final sum divisible by 3
    }
};
