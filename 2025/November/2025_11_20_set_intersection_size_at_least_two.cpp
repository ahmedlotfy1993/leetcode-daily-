/*
    Problem Summary:
    ----------------
    Given a set of intervals [starti, endi], we want to choose a set `nums` of integers 
    such that every interval contains at least two numbers from `nums`. Return the 
    minimum possible size of such a set.

    Approach:
    ---------
    1. **Sort intervals** by their ending points `R` ascending; if tie, by starting point descending.
       - Sorting helps to greedily pick numbers at the rightmost positions to cover intervals.
    2. Maintain the last two numbers `p1` and `p2` in the chosen set `nums`:
       - For each interval [L, R]:
           - If both `p1` and `p2` are outside the interval → pick `R-1` and `R` and update `p1` and `p2`.
           - If only `p1` is outside → pick `R` and update `p1` and `p2`.
           - If both are inside → do nothing (interval already covered by two numbers).
    3. The size of `nums` is the answer.

    Time Complexity:
    ----------------
    O(n log n) → for sorting intervals.  
    O(n) → for the single pass to select numbers.  
    Overall: O(n log n), where n = intervals.size().

    Space Complexity:
    -----------------
    O(n) → worst case for storing `nums`.

    Key Idea:
    ---------
    Greedy selection of numbers from the rightmost end ensures minimum size while 
    satisfying the "at least two numbers per interval" requirement.
*/

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        auto cmp = [](const auto& a, const auto& b) {
            return (a[1] != b[1]) ? (a[1] < b[1]) : (a[0] > b[0]);
        };
        sort(intervals.begin(), intervals.end(), cmp);

        vector<int> nums;
        int p1 = -1, p2 = -1;

        for (const auto& interval : intervals) {
            int L = interval[0], R = interval[1];
            bool in1 = (p1 >= L && p1 <= R);
            bool in2 = (p2 >= L && p2 <= R);

            if (!in1 && !in2) {
                // Pick two largest numbers in the interval
                nums.push_back(R - 1);
                nums.push_back(R);
                p1 = R - 1;
                p2 = R;
            } else if (!in1 && in2) {
                // Pick one additional number to cover the interval
                nums.push_back(R);
                p1 = p2;
                p2 = R;
            }
            // else both numbers already cover the interval → do nothing
        }

        return nums.size();
    }
};
