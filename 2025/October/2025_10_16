/***************************************************************************************************
💠 Problem: Maximum MEX After Modulo Operations
----------------------------------------------------------------------------------------------------
You are given a 0-indexed integer array `nums` and an integer `value`.

In one operation, you can add or subtract `value` from any element of `nums` any number of times.

    Example:
        If nums = [1, 2, 3] and value = 2,
        you can choose to subtract value from nums[0] → nums = [-1, 2, 3].

The MEX (minimum excluded number) of an array is the smallest missing non-negative integer.

    Example:
        MEX([-1, 2, 3]) = 0
        MEX([1, 0, 3]) = 2

Return the maximum MEX of nums after applying the operation any number of times.

----------------------------------------------------------------------------------------------------
🔹 Example 1:
Input:
    nums = [1, -10, 7, 13, 6, 8], value = 5
Output:
    4
Explanation:
    We can modify nums to make it contain {0,1,2,3}, so the MEX is 4.

🔹 Example 2:
Input:
    nums = [1, 2, 3], value = 2
Output:
    3
Explanation:
    After operations, the array can contain {0,1,2}, so MEX = 3.

----------------------------------------------------------------------------------------------------
💡 Approach:
----------------------------------------------------------------------------------------------------
The key observation is that when we add or subtract multiples of `value`,  
the remainder of each element modulo `value` stays the same.

Hence, every number belongs to a fixed “remainder class”.

For example:
    nums = [1, 2, 3], value = 2
    Remainders = {1, 0, 1}

We can think of these remainders as buckets:
    - remainder 0 → can generate {0, 2, 4, 6, ...}
    - remainder 1 → can generate {1, 3, 5, 7, ...}

We iterate starting from 0:
    - If we can represent `result` using its remainder class, consume one count.
    - Otherwise, stop. That `result` is our MEX.

----------------------------------------------------------------------------------------------------
🔹 Time Complexity:  O(n)
🔹 Space Complexity: O(value)
***************************************************************************************************/
class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        unordered_map<int, int> modCount;
        int result = 0;

        // Count frequency of each remainder
        for (int num : nums) {
            int mod = ((num % value) + value) % value;
            modCount[mod]++;
        }

        // Incrementally find the maximum possible MEX
        while (modCount[result % value] > 0) {
            modCount[result % value]--;
            result++;
        }
        return result;
    }
};
