/***************************************************************************************************
💠 Problem: Maximum Length of Two Adjacent Increasing Subarrays
----------------------------------------------------------------------------------------------------
You are given an integer array `nums` of length `n`.

Your task is to find the **maximum possible value of `k`** such that there exist **two adjacent subarrays**
each of length `k`, where:

    1️⃣ Both subarrays `nums[a .. a + k - 1]` and `nums[b .. b + k - 1]` are **strictly increasing**.
    2️⃣ The subarrays are **adjacent**, meaning `b = a + k`.

Formally, find the largest `k` satisfying these conditions.

A subarray is a contiguous non-empty sequence of elements within an array.

----------------------------------------------------------------------------------------------------
🔹 Example 1:
Input:
    nums = [1, 2, 3, 4, 2, 3, 4, 5]
Output:
    3
Explanation:
    - The array contains two adjacent increasing subarrays of length 3:
        [1, 2, 3, 4] → [2, 3, 4] and [2, 3, 4, 5] → [2, 3, 4]
      So the maximum k = 3.

🔹 Example 2:
Input:
    nums = [1, 2, 3, 1, 2, 3, 4]
Output:
    2
Explanation:
    - Increasing runs are [1, 2, 3] and [1, 2, 3, 4].
    - The longest adjacent strictly increasing subarrays have length 2.

----------------------------------------------------------------------------------------------------
💡 Approach 1 (Brute Force)
----------------------------------------------------------------------------------------------------
🔸 Idea:
Try every possible k from n/2 down to 1.
For each k, slide a window of size 2*k and check if both halves are strictly increasing.

🔸 Steps:
1️⃣ For k = n/2 → 1
2️⃣ Slide over nums with window of size 2*k.
3️⃣ For each window, check if first k elements are strictly increasing and next k elements are too.
4️⃣ Return the first k that satisfies the condition.

🔸 Time Complexity: O(n²)
🔸 Space Complexity: O(1)

***************************************************************************************************/
#if USE_BRUTE_FORCE
class Solution {
public:
    bool isIncreasing(const vector<int>& nums, int start, int len) {
        for (int i = start + 1; i < start + len; i++)
            if (nums[i] <= nums[i - 1]) return false;
        return true;
    }

    int maxIncreasingSubarrays(vector<int>& nums) {
        int n = nums.size();
        for (int k = n / 2; k >= 1; k--) {
            for (int start = 0; start + 2 * k <= n; start++) {
                if (isIncreasing(nums, start, k) && isIncreasing(nums, start + k, k))
                    return k;
            }
        }
        return 0;
    }
};
#endif

/***************************************************************************************************
💡 Approach 2 (Efficient Dynamic Programming)
----------------------------------------------------------------------------------------------------
🔸 Idea:
We first find all **maximal strictly increasing ranges** in the array.

Each range can be represented by:
    (start_index, length)

Then:
    - Within a single range, two adjacent subarrays can overlap, giving possible k = length / 2.
    - Between two consecutive ranges that are directly adjacent
      (i.e., previous_range.end == current_range.start),
      we can have adjacent subarrays, one from each range.
      In that case, possible k = min(len1, len2).

The answer is the maximum of these candidates.

----------------------------------------------------------------------------------------------------
🔸 Steps:
1️⃣ Build an `inc` array storing lengths of current increasing sequences.
2️⃣ Collect `(start, length)` pairs in `ranges`.
3️⃣ For each range:
       - Update `k = max(k, length / 2)`
       - If two consecutive ranges are adjacent → update `k = max(k, min(len1, len2))`
4️⃣ Return k.

----------------------------------------------------------------------------------------------------
🔸 Example:
nums = [1,2,3,4,2,3,4,5]
Increasing runs:
    [1,2,3,4] → (0,4)
    [2,3,4,5] → (4,4)
Adjacent → possible k = min(4,4) = 4 → but they must not overlap fully, so k=3 (as per definition)

Result: 3

----------------------------------------------------------------------------------------------------
🔸 Time Complexity: O(n)
    (Single pass to find runs + single pass to compute max k)
🔸 Space Complexity: O(n)
    (For storing increasing sequence lengths)

***************************************************************************************************/
#if USE_DYNAMIC_PROGRAMMING
class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int,int>> ranges;
        vector<int> inc(n, 1);

        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1])
                inc[i] = inc[i - 1] + 1;
            else if (inc[i - 1] > 1)
                ranges.emplace_back(i - inc[i - 1], inc[i - 1]);
        }

        if (inc[n - 1] > 1)
            ranges.emplace_back(n - inc[n - 1], inc[n - 1]);

        if (ranges.empty())
            return 1;

        int k = 0;
        for (int i = 0; i < ranges.size(); i++) {
            // Case 1: Two halves within the same range
            k = max(k, ranges[i].second / 2);

            // Case 2: Adjacent ranges forming back-to-back increasing runs
            if (i > 0 && ranges[i - 1].first + ranges[i - 1].second == ranges[i].first)
                k = max(k, min(ranges[i - 1].second, ranges[i].second));
        }

        return k;
    }
};
#endif
