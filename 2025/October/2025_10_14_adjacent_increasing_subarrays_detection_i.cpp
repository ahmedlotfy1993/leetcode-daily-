/***************************************************************************************************
💠 Problem: Check for Adjacent Increasing Subarrays
----------------------------------------------------------------------------------------------------
You are given an integer array `nums` of length `n`, and an integer `k`.

Determine whether there exist **two adjacent subarrays** of length `k` such that:
    1️⃣ Both subarrays are **strictly increasing**.
    2️⃣ The subarrays are **adjacent**, meaning the starting indices satisfy `b = a + k`.

Formally, we are checking if there exist indices `a` and `b = a + k` such that:
    - nums[a] < nums[a + 1] < ... < nums[a + k - 1]
    - nums[b] < nums[b + 1] < ... < nums[b + k - 1]

Return `true` if such subarrays exist, otherwise return `false`.

----------------------------------------------------------------------------------------------------
🔹 Example 1:
Input:
    nums = [1, 2, 3, 4, 2, 3, 4, 5], k = 3
Output:
    true
Explanation:
    - Subarray [1,2,3,4] → (1,2,3) and (4,2,3) are not adjacent increasing.
    - But subarrays [2,3,4] (indices 1–3) and [2,3,4] (indices 4–6) are both strictly increasing and adjacent.
    → Return true.

🔹 Example 2:
Input:
    nums = [1,2,3,1,2,3], k = 3
Output:
    false
Explanation:
    Each subarray of length 3 is increasing, but they are not adjacent (they overlap partially).

----------------------------------------------------------------------------------------------------
💡 Approach 1 (Brute Force Simulation)
----------------------------------------------------------------------------------------------------
🔸 Idea:
Iterate through all possible starting positions `i` and manually check:
    - Subarray [i .. i+k-1]
    - Subarray [i+k .. i+2k-1]
If both are strictly increasing → return true.

🔸 Steps:
1️⃣ For each i in [0, n - 2k]
2️⃣ Check if both windows of size k are strictly increasing.
3️⃣ Return true if found, false otherwise.

🔸 Time Complexity: O(n * k)
🔸 Space Complexity: O(1)

***************************************************************************************************/
#define BRUTE_FORCE_SIMULATION 0
#if BRUTE_FORCE_SIMULATION
class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        bool result = false;
        int n = nums.size();
        int i = 0;
        while (i < n) {
            int counter = 1;
            int index1 = i;
            int index2 = i + k;

            while (counter < k && index2 + 1 < n &&
                   nums[index1 + 1] > nums[index1] &&
                   nums[index2 + 1] > nums[index2]) {
                index2++;
                index1++;
                counter++;
            }

            if (counter == k) {
                result = true;
                break;
            } else {
                i++;
            }
        }
        return result;
    }
};
#endif

/***************************************************************************************************
💡 Approach 2 (Efficient DP / Sliding Window on Increasing Runs)
----------------------------------------------------------------------------------------------------
🔸 Idea:
We precompute the length of the **current increasing sequence** ending at each index.
If we find a point `i` where:
    - the increasing run ending at `i` has length ≥ k, and
    - the increasing run ending at `i - k` also has length ≥ k,
then we have two adjacent increasing windows of length k.

🔸 Steps:
1️⃣ Compute `increasing[i]` = length of strictly increasing sequence ending at index i.
2️⃣ For i in range [2*k - 1, n):
       - If increasing[i] >= k AND increasing[i - k] >= k → return true.
3️⃣ Otherwise return false.

🔸 Time Complexity: O(n)
    (Single pass to fill increasing array and single pass to check condition)
🔸 Space Complexity: O(n)
    (For storing the increasing run lengths)

***************************************************************************************************/
#define SLIDING_WINDOW 1
#if SLIDING_WINDOW
class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        if (n < 2 * k) return false;

        vector<int> increasing(n, 1);
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1])
                increasing[i] = increasing[i - 1] + 1;
        }

        for (int i = 2 * k - 1; i < n; i++) {
            if (increasing[i] >= k && increasing[i - k] >= k)
                return true;
        }
        return false;
    }
};
#endif
