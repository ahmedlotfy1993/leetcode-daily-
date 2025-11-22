/*
    Problem Summary:
    ----------------
    Given an array nums, you can increment or decrement any element by 1 per operation.
    The goal is to make every element divisible by 3 with the minimum number of operations.

    Approach:
    ---------
    1. For each element, consider its remainder modulo 3:
        - If remainder is 0 → no operation needed.
        - If remainder is 1 or 2 → only 1 operation needed to make it divisible by 3 
          (either subtract or add 1 to reach nearest multiple of 3).
    2. Sum up the required operations.

    Time Complexity:
    ----------------
    - O(n), where n = nums.size(), because we traverse the array once.

    Space Complexity:
    -----------------
    - O(1), only constant extra space is used.
*/

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int ans = 0;
        for(int num : nums){
            // If remainder is 1 or 2, we need 1 operation
            ans += (num % 3 ? 1 : 0);
        }
        return ans;
    }
};
