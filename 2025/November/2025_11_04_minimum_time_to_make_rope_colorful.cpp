/********************************************************************************************
 * Problem:
 * Alice has n balloons arranged on a rope represented by a string `colors`.
 * - colors[i] represents the color of balloon i.
 * - Bob can remove balloons; removing balloon i costs neededTime[i] seconds.
 * - The goal: No two adjacent balloons should have the same color.
 *
 * Return:
 *     The minimum total removal time required to make the rope colorful.
 *
 * -----------------------------------------------------------------------------------------
 * Approach (Greedy — keep the max, remove the rest):
 * For each group of consecutive balloons with the same color:
 *     - We keep the balloon with the highest removal cost (max time).
 *     - Remove all others in the group.
 *
 * Example:
 *     colors     = "abaac"
 *     neededTime = [1,2,3,4,5]
 *
 *     Group "aa": max is 4, remove 3 → cost = 3
 *
 * -----------------------------------------------------------------------------------------
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 *
 ********************************************************************************************/

class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size();
        int totalCost = 0;

        int maxTimeInGroup = neededTime[0];

        for (int i = 1; i < n; i++) {
            if (colors[i] == colors[i - 1]) {
                totalCost += min(maxTimeInGroup, neededTime[i]);
                maxTimeInGroup = max(maxTimeInGroup, neededTime[i]);
            } else {
                maxTimeInGroup = neededTime[i];
            }
        }

        return totalCost;
    }
};
