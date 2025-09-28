/*
--------------------------------------------------------------------------------
Problem:
Given an array of integers representing side lengths, return the largest 
perimeter of a triangle with non-zero area that can be formed using 
three of these lengths. If no such triangle exists, return 0.

A valid triangle must satisfy the triangle inequality:
    a + b > c, b + c > a, and a + c > b.
When the array is sorted in descending order, it is enough to check:
    nums[i] < nums[i+1] + nums[i+2]
because nums[i] is the largest side.

--------------------------------------------------------------------------------
Approach:
1) Sort the array in descending order.
2) Iterate through the sorted array:
   - For each triplet (nums[i], nums[i+1], nums[i+2]):
       - If nums[i] < nums[i+1] + nums[i+2], then they form a valid triangle.
       - Since we sorted in descending order, the first valid triplet we find 
         gives the maximum possible perimeter.
3) If no valid triplet exists, return 0.

--------------------------------------------------------------------------------
Time Complexity:
- Sorting takes O(n log n).
- Single pass check takes O(n).
Overall: O(n log n)

Space Complexity:
- O(1), in-place sorting.

--------------------------------------------------------------------------------
*/

class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());
        int n = nums.size();
        int index = 0;

        // Look for the first valid triangle starting from the largest sides
        while (index < n - 2 && nums[index] >= nums[index + 1] + nums[index + 2])index++;

        return index < n - 2 && nums[index] < nums[index + 1] + nums[index + 2]
            ? nums[index] + nums[index + 1] + nums[index + 2] : 0;
    }
};
