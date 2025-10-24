/*
Problem:
--------
You are given an integer array `nums` and two integers `k` and `numOperations`.

You must perform an operation `numOperations` times on `nums`, where in each operation you:
    - Select an index `i` that was not selected in any previous operations.
    - Add an integer in the range [-k, k] to `nums[i]`.

Return the maximum possible frequency of any element in `nums` after performing the operations.


Solution:
---------
We start by sorting the array to make range checks efficient.
Then, for each number, we keep track of how many times it occurs using a hash map.
To maximize frequency, we consider potential values (including `val - k` and `val + k`) that
can be reached by modifying nearby numbers within the allowed range.

For each possible target value `val`:
    - Find the window of elements in `nums` that could be converted to `val` using additions in [-k, k].
    - The window is found using binary search (`lower_bound`, `upper_bound`).
    - The possible frequency for `val` is limited by the number of elements in that window and
      the number of remaining operations (`numOperations`).
    - Update the maximum frequency accordingly.

We use a set to ensure we only check unique candidate values.

Underlying Technique:
---------------------
Sliding window (via binary search bounds) combined with value normalization via range exploration.

Complexity Analysis:
--------------------
Time Complexity: O(n log n)
    - Sorting takes O(n log n).
    - Each binary search for bounds runs in O(log n) for each unique value.

Space Complexity: O(n)
    - For storing counts and candidate values.


Code:
-----
*/
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        sort(nums.begin(), nums.end());

        int max_freq = 0;
        unordered_map<int, int> numCount;
        set<int> values;

        // Count frequency and prepare possible candidate values
        for (int val : nums) {
            numCount[val]++;
            max_freq = max(max_freq, numCount[val]);
            values.insert(val);
            if (val - k >= nums.front()) values.insert(val - k);
            if (val + k <= nums.back()) values.insert(val + k);
        }

        // For each candidate value, find the reachable window
        for (int val : values) {
            int l = lower_bound(nums.begin(), nums.end(), val - k) - nums.begin();
            int r = upper_bound(nums.begin(), nums.end(), val + k) - nums.begin();
            int window_size = r - l;

            int freq = 0;
            if (numCount.count(val))
                freq = min(window_size, numCount[val] + numOperations);
            else
                freq = min(window_size, numOperations);

            max_freq = max(max_freq, freq);
        }

        return max_freq;
    }
};
