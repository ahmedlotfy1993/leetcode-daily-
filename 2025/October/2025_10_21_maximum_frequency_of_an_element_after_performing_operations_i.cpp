/***************************************************************************************************
💠 Problem: Maximum Frequency After Limited Range Add Operations
----------------------------------------------------------------------------------------------------
You are given:
    - An integer array `nums`
    - Two integers `k` and `numOperations`

You must perform exactly `numOperations` operations on `nums`.  
In each operation:
    1. Select an index `i` that has not been selected before.
    2. Add an integer from the range [-k, k] to `nums[i]`.

Return the **maximum possible frequency** (i.e., count of the most frequent number) in the array
after performing all `numOperations`.

----------------------------------------------------------------------------------------------------
🔹 Example 1:
Input:
    nums = [1, 4, 6]
    k = 2
    numOperations = 1
Output:
    2
Explanation:
    - We can add +2 to 4 → nums = [1, 6, 6]
    - Now frequency of 6 = 2, which is the maximum possible.

🔹 Example 2:
Input:
    nums = [3, 9, 12]
    k = 3
    numOperations = 2
Output:
    3
Explanation:
    - Add +3 to 9 → 12
    - Add +3 to 3 → 6 (not useful)
    - But we can also bring all within overlapping range [6–12] for maximum grouping.

----------------------------------------------------------------------------------------------------
💡 Approach: Sliding Window over Value Range + Counting ✅
----------------------------------------------------------------------------------------------------
1. Sort `nums` to simplify range-based grouping.
2. Use a frequency map (`numCount`) to track occurrences of each value.
3. For each potential target value `val`:
    - Determine all numbers that can be adjusted into `[val - k, val + k]`.
    - Compute the potential frequency:
          freq = min(window_size, current_frequency[val] + numOperations)
    - Keep track of the global maximum.

4. The idea is to "stretch" nearby numbers (within ±k) toward the same target value 
   using at most `numOperations` modifications.

----------------------------------------------------------------------------------------------------
🔹 Key Insights:
- Sorting allows range expansion checks via binary search (`lower_bound`, `upper_bound`).
- The number of possible candidates for conversion depends on overlap in range ±k.
- We only need to consider values between `min(nums)` and `max(nums)` as potential centers.

----------------------------------------------------------------------------------------------------
🔸 Time Complexity:  O(n log n + R log n)
    - Sorting: O(n log n)
    - For each candidate value in range R (from min(nums) to max(nums)):
        binary searches for range bounds → O(log n)
    - Overall: acceptable for moderate constraints.

🔸 Space Complexity: O(n)
    - Due to auxiliary hash map and sorted storage.

***************************************************************************************************/
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
#if USE_RANGE_BASED_COUNT
        sort(nums.begin(), nums.end());

        int max_freq = 0;
        unordered_map<int, int> numCount;

        // Count frequency of each element
        for (int val : nums) {
            numCount[val]++;
            max_freq = max(max_freq, numCount[val]);
        }

        // For each value, find how many elements can be adjusted into its ±k range
        for (int val = nums.front(); val <= nums.back(); val++) {
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
#endif
    }
};
