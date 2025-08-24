/*
Problem:
--------
You're visiting a farm with fruit trees planted in a row, represented by an integer array `fruits`,
where `fruits[i]` is the type of fruit on the i-th tree.

Rules for collecting fruit:
- You have two baskets, and each can only hold one type of fruit.
- Starting from any tree, you must pick exactly one fruit from each tree while moving to the right.
- You must stop picking once you encounter a third fruit type that doesn't fit in either basket.

Goal:
-----
Return the maximum number of fruits you can collect under the above constraints.
*/

/*
 Approach:
---------
Manual Map Management:
   ----------------------------------------------
   - Iterate through the array and track fruit types manually in a map.
   - When a third fruit type is encountered, compute the result so far.
   - Backtrack to find the last contiguous group of the previous fruit and retain that in the new window.
   - Clear and rebuild the map with the new window starting from that repeated fruit.
   - Continue iterating and updating the result.
   
   Pros:
   - More intuitive about how fruit types are grouped.
   - Helps understand how repeated fruits form the basis for new baskets.

   Cons:
   - More verbose and error-prone.
   - Less efficient compared to the sliding window method.
*/
#define MANUAL_MAP_MANAGEMENT_APPROACH
#ifdef MANUAL_MAP_MANAGEMENT_APPROACH
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
Sliding Window Approach :
   -----------------------------------
   - Use a sliding window defined by two pointers: `left` and `right`.
   - Expand the window by moving `right` and keep track of fruit types using a hashmap `count`.
   - If more than 2 types are in the map, shrink the window from the `left` until only 2 remain.
   - Keep updating `max_len` with the size of the current valid window.
   
   Time Complexity: O(n)
   Space Complexity: O(1) — map will hold at most 3 keys (since we break on >2).
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
