/*
--------------------------------------------------------------------------------
Problem:
Given an integer array nums, return the number of triplets chosen from the array 
that can make triangles if we take them as side lengths of a triangle.

A triangle is valid if the sum of any two sides is greater than the third side. 
Since the array can be sorted, we only need to check:
    nums[i] + nums[j] > nums[k]
where i < j < k and nums[i] ≤ nums[j] ≤ nums[k].

--------------------------------------------------------------------------------
Approaches:
Two-Pointer (O(n^2)):
   - Sort the array.
   - Fix the largest side nums[k].
   - Use two pointers (i at start, j before k).
   - If nums[i] + nums[j] > nums[k], then all elements from i...j-1 with j 
     also form valid triangles → add (j - i).
   - Otherwise, move i forward to increase the sum.
   - This is optimal and widely used.
--------------------------------------------------------------------------------
Time Complexity:
- Sorting: O(n log n)
- Two-pointer iteration: O(n^2)
Overall: O(n^2)

Space Complexity:
- O(1) extra space (in-place sorting).

--------------------------------------------------------------------------------
*/

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int result = 0;

        for (int k = n - 1; k >= 2; --k) { // fix the largest side nums[k]
            int i = 0, j = k - 1;
            while (i < j) {
                if (nums[i] + nums[j] > nums[k]) {
                    result += (j - i);
                    --j;
                } else {
                    ++i;
                }
            }
        }
        return result;
    }
};
