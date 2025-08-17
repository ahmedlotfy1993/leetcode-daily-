/*
    Problem: New 21 Game (Leetcode 837)

    Description:
    Alice plays a game where she starts with 0 points and draws numbers randomly from 1 to maxPts.
    She keeps drawing as long as her total score is less than k. Once she reaches k or more, she stops.
    The goal is to determine the probability that her final score is less than or equal to n.

    Key Observations:
    - Alice only stops drawing when her score is at least k.
    - After stopping, we check if her score lies within [k, n] to be considered a win.
    - Each draw has equal probability (1 / maxPts).
    - We use Dynamic Programming to compute the probability of reaching each score from 0 to k.
*/
/*
    Solution Approach:
    - Let dp[i] be the probability of reaching score i.
    - Initialize dp[0] = 1, as Alice starts at 0 with probability 1.
    - Use a sliding window sum `win_sum` to maintain the cumulative probability of the last `maxPts` entries.
    - For each i in [1, k], compute dp[i] = win_sum / maxPts.
    - If i < k, add dp[i] to win_sum (since it's still possible to draw further).
    - After dp[k] is computed, use it to determine the total probability of reaching scores in [k, n].

    Time Complexity: O(k)
    Space Complexity: O(k)
*/
class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        if (k == 0 || n >= k - 1 + maxPts) return 1.0;

        vector<double> dp(n + 1, 0.0);
        dp[0] = 1.0;
        double win_sum = 1.0, result = 0.0;

        for (int i = 1; i <= n; ++i) {
            dp[i] = win_sum / maxPts;
            if (i < k)
                win_sum += dp[i];
            else
                result += dp[i];  // only accumulate result when Alice stops
            if (i - maxPts >= 0)
                win_sum -= dp[i - maxPts];
        }

        return result;
    }
};
