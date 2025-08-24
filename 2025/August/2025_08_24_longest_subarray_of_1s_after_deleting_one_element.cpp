/*
    Problem:
    --------
    Given a binary array 'nums' (containing only 0s and 1s), you are allowed to delete exactly one element from the array.
    After the deletion, return the length of the longest possible non-empty subarray that contains only 1s.
    
    Important Constraints:
    - You must delete exactly one element.
    - The resulting subarray must be contiguous.
    - Return 0 if it's not possible to form such a subarray.
*/
/*
    Approach:
    ---------
    1. Edge Case Handling:
       - If the array contains only 1s, then deleting any one of them gives a subarray of size (n - 1).
       - If the array contains no 1s, return 0 since no valid subarray can be formed.

    2. Main Logic (Sliding Window with Two Pointers):
       - Initialize:
           - `left_index` to track the position of the last seen 0 (initialized to -1).
           - `right_index` to iterate through the array.
           - `previous_ones` to count the number of 1s between the previous 0 and the current 0.
           - `result` to store the maximum length of the valid subarray found.

       - Iterate through the array:
           - When a 0 is encountered:
               - Calculate the length of 1s from previous 0 to current 0 + 1s after previous 0.
               - Update `result` if the new length is greater.
               - Update `previous_ones` and `left_index` for the next segment.

       - After the loop, do one final update in case the array ends with a run of 1s.

    3. Time Complexity:
       - O(n), where n is the size of the array (single pass).
    
    4. Space Complexity:
       - O(1), constant space usage.

    Example:
    --------
    Input:  [1, 1, 0, 1, 1]
    Output: 4
    Explanation: Delete the 0 to get the subarray [1, 1, 1, 1]
*/
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        int all_ones = count(nums.begin(), nums.end(), 1);
        if(all_ones == 0)return 0;
        if(all_ones == n)return n - 1;

        int right_index = 0;
        int left_index = -1;
        int previous_ones = 0;
        int result = 0;
        for(right_index = 0; right_index < n; right_index++){
            if(!nums[right_index]){
                result = max(result, right_index -left_index - 1 + previous_ones);
                previous_ones = right_index -left_index - 1;
                left_index = right_index;
            }
        }

        return max(result, right_index -left_index - 1 + previous_ones);
    }
};
