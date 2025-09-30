/*
--------------------------------------------------------------------------------
Problem:
You are given a 0-indexed integer array `nums` (digits 0–9).
The *triangular sum* is obtained by repeatedly replacing the array with a 
new array of length n-1, where each element is defined as:

    newNums[i] = (nums[i] + nums[i+1]) % 10

This process continues until only one number remains in the array.
Return that number.

--------------------------------------------------------------------------------
Example:
Input: nums = [1,2,3,4,5]
Process:
[1,2,3,4,5]
 → [(1+2)%10=3, (2+3)%10=5, (3+4)%10=7, (4+5)%10=9] = [3,5,7,9]
 → [(3+5)%10=8, (5+7)%10=2, (7+9)%10=6] = [8,2,6]
 → [(8+2)%10=0, (2+6)%10=8] = [0,8]
 → [(0+8)%10=8] = [8]
Output: 8

--------------------------------------------------------------------------------
Approaches:

1) **Extra Array at Each Step**  
   - Use a temporary vector of size n-1 for each iteration.  
   - Fill it with pairwise sums modulo 10.  
   - Replace nums with this new vector.  
   - Time: O(n^2), Space: O(n) (new vector each step).  

2) **In-place Transformation**  
   - Perform the transformation directly inside the original `nums`.  
   - Overwrite nums[i] with `(nums[i] + nums[i+1]) % 10`.  
   - After processing, `pop_back()` the last element (since size reduces).  
   - Repeat until one element remains.  
   - Time: O(n^2), Space: O(1) (no extra vector).  

--------------------------------------------------------------------------------
Complexity:
- Time Complexity: O(n^2) (at each step, reduce length by 1, so ~n + (n-1) + ... + 1 ≈ n^2/2).  
- Space Complexity:  
    • Approach 1: O(n) (temporary vectors).  
    • Approach 2: O(1) (in-place, only modifies `nums`).  

--------------------------------------------------------------------------------
*/
#define USE_EXTRA_VECTOR 0
#define USE_INPLACE_TRANSFORM 1
class Solution {
public:
    int triangularSum(vector<int>& nums) {
        int n = nums.size();
        while (n > 1) {
#if USE_EXTRA_VECTOR
            vector<int> temp(n - 1, 0);
            transform(nums.begin(), nums.end() - 1, nums.begin() + 1, temp.begin(),
                      [](int a, int b) { return (a + b) % 10; });
            nums = move(temp);
            n = nums.size();
#endif
#if USE_INPLACE_TRANSFORM
            transform(nums.begin(), nums.end() - 1, nums.begin() + 1, nums.begin(),
                      [](int a, int b) { return (a + b) % 10; });
            nums.pop_back();
            n = n - 1;
#endif
        }
        return nums[0];
    }
};
