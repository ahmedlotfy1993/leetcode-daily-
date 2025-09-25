/**
 * Problem:
 * --------
 * Given a triangle array, return the minimum path sum from top to bottom.
 * At each step, you may move to either the same index or the next index 
 * in the row below.
 *
 * Example:
 * --------
 * Input:
 * [
 *      [2],
 *     [3,4],
 *    [6,5,7],
 *   [4,1,8,3]
 * ]
 * Output: 11
 * Explanation: Path is 2 -> 3 -> 5 -> 1 = 11
 *
 * Approaches:
 * ------------
 * 1. TOP-DOWN DYNAMIC PROGRAMMING (macro: TRIANGLE_TOP_DOWN_DP)
 *    - Build DP row by row from the top.
 *    - Keep track of min path sums using two arrays (prev and curr).
 *    - Transition:
 *        curr[j] = min(prev[j], prev[j-1]) + triangle[i][j]
 *    - Answer: minimum value in the last row of DP.
 *    - Time Complexity: O(n^2)
 *    - Space Complexity: O(n)
 *
 * 2. BOTTOM-UP DYNAMIC PROGRAMMING (macro: TRIANGLE_BOTTOM_UP_DP)
 *    - Start from the last row and collapse upwards.
 *    - Transition:
 *        dp[j] = triangle[i][j] + min(dp[j], dp[j+1])
 *    - Answer: dp[0] after processing.
 *    - Time Complexity: O(n^2)
 *    - Space Complexity: O(n)
 *
 * Both methods yield the same result. The bottom-up approach is slightly cleaner 
 * and more space-efficient in practice.
 */

#define TRIANGLE_TOP_DOWN_DP   1
#define TRIANGLE_BOTTOM_UP_DP  0

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
#if TRIANGLE_TOP_DOWN_DP
        // --- Top-Down Dynamic Programming ---
        int row_num = triangle.size();
        vector<int> prev_dp(row_num, INT_MAX);
        prev_dp[0] = triangle[0][0];

        for (int i = 1; i < row_num; i++) {
            vector<int> curr_dp(row_num, INT_MAX);
            for (int j = 0; j < triangle[i].size(); j++) {
                if (prev_dp[j] != INT_MAX)
                    curr_dp[j] = min(curr_dp[j], prev_dp[j] + triangle[i][j]);
                if (j >= 1 && prev_dp[j - 1] != INT_MAX)
                    curr_dp[j] = min(curr_dp[j], prev_dp[j - 1] + triangle[i][j]);
            }
            prev_dp = move(curr_dp);
        }
        return *min_element(prev_dp.begin(), prev_dp.end());
#endif

#if TRIANGLE_BOTTOM_UP_DP
        // --- Bottom-Up Dynamic Programming ---
        vector<int> dp(triangle.back());
        for (int i = triangle.size() - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
            }
        }
        return dp[0];
#endif
    }
};
