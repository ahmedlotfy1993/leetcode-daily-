/*
Problem Statement:
------------------
You are given an integer array `nums`.

Start by selecting a starting position `curr` such that `nums[curr] == 0`, and choose a movement direction — either **left (-1)** or **right (+1)**.

Then repeatedly perform the following process:

1. If `curr` goes out of bounds (not in [0, n - 1]), the process ends.
2. If `nums[curr] == 0`, move one step in the **current direction**.
3. Else if `nums[curr] > 0`:
   - Decrement `nums[curr]` by 1.
   - **Reverse** the direction (left ↔ right).
   - Move one step in the new direction.

A selection of `(start, direction)` is **valid** if all elements in `nums` become `0` by the end of the process.

Return the number of possible **valid selections**.


Approach:
---------
1. Define a helper function `simulate()` that:
   - Takes a copy of `nums` (so the original is not modified).
   - Starts at `start` index with a given direction `dir`.
   - Repeats the described simulation until the position goes out of range.
   - Returns `true` if all elements become zero at the end.
2. Iterate over all indices where `nums[i] == 0`.
   - For each such index, test both directions (`dir = +1` and `dir = -1`).
   - Count how many lead to all zeros.
3. Return this count.

Time Complexity:
----------------
O(k * n)  
- where k = number of starting positions (each having 2 directions).
- Each simulation may visit elements up to n times.

Space Complexity:
-----------------
O(n)
- due to the copy of `nums` inside each simulation call.


Code:
-----
*/

class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        auto simulate = [](vector<int>& nums, int start, int dir) -> bool {
            vector<int> v = nums;
            int n = nums.size();
            int curr = start;

            while (curr >= 0 && curr < n) {
                if (v[curr] == 0) {
                    curr += dir;
                } else {
                    v[curr]--;
                    curr -= dir;  // reverse movement first
                    dir = -dir;   // then flip direction
                }
            }
            return all_of(v.begin(), v.end(), [](int x) { return x == 0; });
        };

        int answer = 0;
        int n = nums.size();
        vector<pair<int, int>> selections;

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                selections.emplace_back(i, 1);
                selections.emplace_back(i, -1);
            }
        }

        for (const auto& [index, dir] : selections) {
            if (simulate(nums, index, dir)) answer++;
        }

        return answer;
    }
};
