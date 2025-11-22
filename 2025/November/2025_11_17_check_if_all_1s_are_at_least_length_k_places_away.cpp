/*
    Problem Summary:
    ----------------
    Given a binary array `nums` and an integer `k`, check if all `1`s in the array are 
    at least `k` places apart. Return true if the condition is satisfied, otherwise false.

    Approach:
    ---------
    • Initialize `prev_index = -1` to track the previous index of '1'.
    • Traverse the array:
        - If the current element is '1' and `prev_index != -1`, 
          check if the distance to the previous '1' is less than `k`.
          - If yes, return false immediately.
        - Otherwise, update `prev_index` to current index.
    • If the loop finishes without returning false, all '1's satisfy the condition, return true.

    Time Complexity:
    ----------------
    O(n), where n = nums.size()
    • Each element is visited exactly once.

    Space Complexity:
    -----------------
    O(1), only a single variable `prev_index` is used.
*/

class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        int prev_index = -1;
        int n = nums.size();

        for (int index = 0; index < n; index++) {
            if (nums[index] == 1) {
                if (prev_index != -1 && index - prev_index - 1 < k) {
                    return false;
                }
                prev_index = index;
            }
        }

        return true;
    }
};
