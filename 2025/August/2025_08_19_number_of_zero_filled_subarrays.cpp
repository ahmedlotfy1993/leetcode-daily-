/*
Problem: Count Zero-Filled Subarrays

Given an integer array `nums`, return the total number of contiguous subarrays that consist only of 0s.
A subarray is defined as a non-empty contiguous sequence of elements from the array.

Example:
Input:  nums = {0, 0, 1, 0, 0, 0}
Output: 9
Explanation:
  - From the first segment of 2 zeros: [0], [0], [0,0] → 3 subarrays
  - From the second segment of 3 zeros: [0], [0], [0], [0,0], [0,0], [0,0,0] → 6 subarrays
  - Total = 3 + 6 = 9
*/

/*
Approach:
- Traverse the array while counting consecutive zeros using a counter.
- For each sequence of `count` zeros, the number of valid subarrays is:
    count * (count + 1) / 2
  This is the formula for the sum of the first `count` natural numbers, representing all possible subarrays.

Optimized Solution:
- Iterate through the array once (O(n) time).
- Use a single loop to accumulate results and reset the zero counter when encountering a non-zero.
- Add the final segment (if any) after the loop ends.

Time Complexity: O(n)
Space Complexity: O(1)
*/

class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long int result = 0;
        long long int count = 0;
        for(int num: nums){
            if(num == 0){
                count++;
            }else if (count != 0){
              result += count * (count + 1) / 2;
              count = 0;
            }
        }
        result += count * (count + 1) / 2;
        return result;
    }
};
