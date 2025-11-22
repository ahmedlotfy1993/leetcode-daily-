/*
    LeetCode — Minimum Operations to Make All Array Elements Zero

    Spicy Discussion Line:
    "Looks like a segmentation-fault type Hard… but actually it's just
     a monotonic stack in disguise."

    ------------------------------------------------------------------
    Problem Summary:
    You may pick a subarray [i, j] and set all occurrences of the
    *minimum* non-negative integer in that subarray to 0.

    You want to reduce the array to all zeros using the minimum
    number of operations.
*/

// ================================================================
//  APPROACH: Monotonic Increasing Stack
//  ------------------------------------------------
//  Intuition:
//    Each time we meet a value 'a' that is larger than the top of
//    the stack → that means a *new layer* of numbers must be zeroed
//    separately.
//
//    When a < stack.back(), we pop until the stack is valid again.
//
//    Essentially we count the number of *distinct increasing layers*.
//
//  Example: nums = [1,3,2,5,4]
//      layers: [1], [3], then drop to 2 → start new layer, etc.
//
//  Time Complexity:   O(n)
//  Space Complexity:  O(n) for stack
// ================================================================

class Solution {
public:
    int minOperations(vector<int>& nums) {
        vector<int> st;
        int res = 0;

        for (int a : nums) {
            // shrink stack while top > current element
            while (!st.empty() && st.back() > a) {
                st.pop_back();
            }

            if (a == 0) continue;

            // if new level
            if (st.empty() || st.back() < a) {
                ++res;
                st.push_back(a);
            }
        }
        return res;
    }
};
