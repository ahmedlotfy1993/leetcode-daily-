/*
Problem:
---------
You are given an integer array `height` where each element represents the height of a vertical line 
drawn at index `i` (with endpoints at (i, 0) and (i, height[i])).
You need to find two lines that, together with the x-axis, form a container that can hold the 
maximum amount of water. The container must be upright (no slanting).

Key Idea:
----------
- The container’s area is determined by:
      min(height[left], height[right]) * (right - left)
  where `left` and `right` are indices of the two chosen lines.
- To maximize area:
    - Start with two pointers at the ends of the array.
    - Calculate the area formed.
    - Move the pointer pointing to the shorter line inward, since the area is limited by the shorter height.
    - Continue until both pointers meet.

This is the **two-pointer greedy technique** which eliminates the need for a brute-force O(n^2) check.

Time Complexity:
----------------
- O(n): Each index is visited at most once by either the left or right pointer.

Space Complexity:
-----------------
- O(1): Only a few variables are used.

Underlying Technique:
---------------------
- Two-pointer optimization with greedy choice (always move the limiting side inward).
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = 0;
        int left_i = 0;
        int right_i = height.size() - 1;

        while (left_i < right_i) {
            int min_h = min(height[left_i], height[right_i]);
            int current_area = min_h * (right_i - left_i);
            area = max(area, current_area);

            if (height[left_i] < height[right_i]) {
                left_i++;
            } else if (height[left_i] > height[right_i]) {
                right_i--;
            } else {
                left_i++;
                right_i--;
            }
        }
        return area;
    }
};
