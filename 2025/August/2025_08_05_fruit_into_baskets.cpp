/*
Problem:
--------
You are given an integer array `fruits` representing a row of fruit trees. Each `fruits[i]`
denotes the type of fruit on the i-th tree.

You have two baskets and must follow these rules:
1. Each basket can only hold **one type** of fruit, but an unlimited amount of it.
2. Starting from any index, you can only move to the **right**, picking one fruit from each tree.
3. Once you encounter a third fruit type that doesn't fit in your baskets, you must stop.

Return the **maximum number of fruits** you can collect while adhering to these constraints.
*/

/*
Approach:
---------
Manual Backtracking Approach:
   -----------------------------------------------------
   - Iterate over the array while tracking fruit types in a map.
   - When a third fruit type is encountered, backtrack to find how many times the last fruit was repeated.
   - Clear and reconstruct the fruit map with the last contiguous fruit group and the new fruit.
   - Track the number of collected fruits accordingly and update the result.

   Time Complexity: O(n)
   Space Complexity: O(1)
*/
#define MANUAL_BACKTRACKING_APPROACH
#ifdef MANUAL_BACKTRACKING_APPROACH
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int result = 0;
        unordered_map<int, int>fruit_count;
        int fruits_number = 0;
        for(int index = 0; index < n; index++){
            if(fruit_count.contains(fruits[index]) || fruit_count.size() < 2){
                fruit_count[fruits[index]]++;
                fruits_number++;
            }else{
                result = max(result, fruits_number);
                int old_fruit = fruits[index - 1];
                int old_fruit_index = index - 1;
                while(old_fruit_index >= 0 && fruits[old_fruit_index] == old_fruit)old_fruit_index--;
                fruit_count.clear();
                fruit_count[old_fruit] = index - old_fruit_index - 1;
                fruit_count[fruits[index]] =  1;
                fruits_number = index - old_fruit_index ;
            }
        }
        result = max(result, fruits_number);
        return result;
    }
};
#endif
/*
  
Approach:
---------
Sliding Window Approach:
   ----------------------------------
   - Use two pointers `left` and `right` to form a window.
   - Track the count of each fruit type within the window using a hashmap.
   - Expand the window by moving `right`, and shrink it from the `left` when more than 2 fruit types are present.
   - At every valid step, update `max_len` with the size of the current window.
   
   Time Complexity: O(n)
   Space Complexity: O(1) — maximum of 3 keys in the map at any time.

   ✅ Simple, efficient, and scalable solution.

*/
#define SLIDING_WINDOW_APPROACH
#ifdef SLIDING_WINDOW_APPROACH
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> count;
        int n = fruits.size();
        int left = 0, max_len = 0;
        for (int right = 0; right < n; ++right) {
            count[fruits[right]]++;
            while (count.size() > 2) {
                count[fruits[left]]--;
                if (count[fruits[left]] == 0)
                    count.erase(fruits[left]);
                ++left;
            }
            max_len = max(max_len, right - left + 1);
        }
        return max_len;
    }
};
#endif
