/*
    Problem Summary:
    ----------------
    You are given a binary array nums.
    Define xi as the integer represented by the prefix nums[0..i] in binary.

        Example:
            nums = [1,0,1]
            x0 = 1
            x1 = 2
            x2 = 5

    You must return a boolean array where answer[i] = true
    iff xi is divisible by 5.

    Key Insight:
    ------------
    The prefix number grows exponentially if we build it normally.
    But we only care whether it is divisible by 5 → we keep the number modulo 5.

    Let:
        number = prefix % 5

    Each step:
        new_number = (old_number * 2 + current_bit) % 5

    This avoids overflow and is mathematically correct due to modulo properties.

    Time Complexity:
    ----------------
    O(n) — iterate through nums once.

    Space Complexity:
    -----------------
    O(n) for the output result.

*/

class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& nums) {
        vector<bool> ans;
        int number = 0;

        for (int bit : nums) {
            number = ((number << 1) | bit) % 5;
            ans.push_back(number == 0);
        }

        return ans;
    }
};
