/***************************************************************************************************
💠 Problem: Maximum Number of Distinct Elements After at Most One Operation
----------------------------------------------------------------------------------------------------
You are given an integer array `nums` and an integer `k`.

You are allowed to perform the following operation **on each element at most once**:
    ➤ Add an integer in the range [-k, k] to the element.

Return the **maximum possible number of distinct elements** in `nums`
after performing the operations.

----------------------------------------------------------------------------------------------------
🔹 Example 1:
Input:
    nums = [1, 2, 2, 3, 4], k = 2
Output:
    5
Explanation:
    We can shift duplicates so all numbers become distinct:
        nums = [-1, 1, 3, 5, 6]
    → All are distinct, count = 5.

🔹 Example 2:
Input:
    nums = [3, 7, 3, 7, 3], k = 2
Output:
    5
Explanation:
    Adjust each 3 or 7 by up to ±2 to make all unique:
        nums = [1, 3, 5, 7, 9].

----------------------------------------------------------------------------------------------------
💡 Approach 1: Brute Force (using unordered_set)
----------------------------------------------------------------------------------------------------
1️⃣ Sort the array.
2️⃣ For each number, try all possible shifts in [-k, k].
3️⃣ Insert the first available number not already used.

🔸 Time Complexity:  O(n * k)
🔸 Space Complexity: O(n)
🔸 Not efficient for large inputs.

----------------------------------------------------------------------------------------------------
💡 Approach 2: Optimized Greedy Approach ✅
----------------------------------------------------------------------------------------------------
1️⃣ Sort the array.
2️⃣ Maintain the next smallest available integer (`curr`) to ensure uniqueness.
3️⃣ For each `num`:
      - Possible range = [num - k, num + k]
      - Choose `place = max(curr, num - k)` (the earliest available unique value).
      - If `place <= num + k`, count it as a new unique element.
      - Update `curr = place + 1`.

This greedy strategy ensures we assign the smallest possible distinct value to each element.

🔸 Time Complexity:  O(n log n)   → sorting dominates
🔸 Space Complexity: O(1)

***************************************************************************************************/
class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
#if USE_BRUTE_FORCE
        // 🔹 Brute Force Approach
        sort(nums.begin(), nums.end());
        unordered_set<int> used;
        for (int num : nums) {
            for (int d = -k; d <= k; ++d) {
                if (used.insert(num + d).second) {
                    break;
                }
            }
        }
        return used.size();
#endif

        // ✅ Optimized Greedy Approach
        sort(nums.begin(), nums.end());
        int curr = INT_MIN; 
        int distinct = 0;

        for (int num : nums) {
            int left = num - k;
            int right = num + k;
            int place = max(left, curr);  

            if (place <= right) {
                distinct++;
                curr = place + 1;
            }
        }
        return distinct;
    }
};
