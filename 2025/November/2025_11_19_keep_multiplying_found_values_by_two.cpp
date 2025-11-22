/*
    Problem Summary:
    ----------------
    Given an array of integers `nums` and an integer `original`, we repeatedly:
    1. Check if `original` exists in `nums`.
    2. If it exists, double its value and repeat.
    3. If it does not exist, stop and return `original`.

    Approach:
    ---------
    • Use a while loop to check whether `original` is in `nums`:
        - If found, multiply `original` by 2 and continue.
        - If not found, exit the loop.
    • Return the final value of `original`.

    Time Complexity:
    ----------------
    O(n * log(maxValue/original)), in the worst case where we search for multiple doublings.
    - Each `find` takes O(n), and we may double `original` up to log(maxValue/original) times.

    Space Complexity:
    -----------------
    O(1), only a few integer variables are used.
*/

class Solution {
public:
    int findFinalValue(vector<int>& nums, int original) {
        auto it = find(nums.begin(), nums.end(), original);
        while (it != nums.end()) {
            original *= 2;
            it = find(nums.begin(), nums.end(), original);
        }
        return original;
    }
};
