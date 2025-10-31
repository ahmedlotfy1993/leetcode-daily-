/*
Problem:
--------
You are given a string `s` and an integer `k`.

You are allowed to change **at most one index** in `s` to another lowercase English letter.
After that, repeatedly perform the following partitioning operation until `s` becomes empty:

    • Choose the longest prefix of `s` that contains at most `k` distinct characters.
    • Delete that prefix from `s`, count it as one partition, and continue with the rest.

Return the maximum number of partitions you can achieve after optimally choosing (or not choosing)
one character in `s` to modify.

Approach:
---------
We simulate partitioning **from left to right** to compute, for every index `i`:
    - how many partitions were formed before `i`,
    - the distinct characters mask,
    - distinct character count so far.

Then perform the same logic **from right to left**, storing information on partitions that would be
formed after index `i`.

For each index `i`, we consider changing `s[i]` to any possible character (implicitly handled via
bitmask reasoning):
    - When combining left and right results around position `i`, check if merging both windows
      exceeds `k` distinct characters or not.
    - Adjust partition count accordingly to maximize number of partitions.

Finally, take the maximum over all possible change positions.

Time Complexity:
----------------
O(n)
    - Two preprocessing passes (left-to-right and right-to-left)
    - One final scan over all indices

Space Complexity:
-----------------
O(n)
    - We store left and right partition information for each index
*/

class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        int n = s.length();

        // Each entry stores: { partitions_so_far, bitmask_of_distinct_chars, count_distinct_chars }
        vector<vector<int>> leftInfo(n, vector<int>(3));
        vector<vector<int>> rightInfo(n, vector<int>(3));

        int partitions = 0;     // number of formed partitions
        int seenMask = 0;       // bitmask of characters seen in current segment
        int distinctCnt = 0;    // number of distinct chars in current segment

        for (int i = 0; i < n - 1; i++) {
            int bit = 1 << (s[i] - 'a');

            // if this char is new in current window
            if (!(seenMask & bit)) {
                distinctCnt++;
                // If distinct char count exceeds k → new partition
                if (distinctCnt <= k) {
                    seenMask |= bit;
                } else {
                    partitions++;       // close a partition
                    seenMask = bit;     // restart new segment
                    distinctCnt = 1;
                }
            }
            leftInfo[i + 1] = { partitions, seenMask, distinctCnt };
        }

        // ====== Right to left preprocessing (same logic) ======
        partitions = 0;
        seenMask = 0;
        distinctCnt = 0;

        for (int i = n - 1; i > 0; i--) {
            int bit = 1 << (s[i] - 'a');

            if (!(seenMask & bit)) {
                distinctCnt++;
                if (distinctCnt <= k) {
                    seenMask |= bit;
                } else {
                    partitions++;
                    seenMask = bit;
                    distinctCnt = 1;
                }
            }
            rightInfo[i - 1] = { partitions, seenMask, distinctCnt };
        }

        int best = 0;

        for (int i = 0; i < n; i++) {
            int totalSegments = leftInfo[i][0] + rightInfo[i][0] + 2;

            int mergedMask = leftInfo[i][1] | rightInfo[i][1];

            int mergedDistinct = __builtin_popcount(mergedMask);

            if (leftInfo[i][2] == k && rightInfo[i][2] == k && mergedDistinct < 26) {
                totalSegments++;
            }
            else if (min(mergedDistinct + 1, 26) <= k) {
                totalSegments--;
            }

            best = max(best, totalSegments);
        }

        return best;
    }
};
