/*
Problem:
--------
You're given a 2D integer array `fruits`, where each entry is of the form [position, amount], 
representing that there are `amount` fruits at a specific position on an infinite x-axis.

You also have:
- An integer `startPos`: your starting position on the x-axis.
- An integer `k`: the maximum number of steps you can take (1 step = move 1 unit left or right).

From your starting position, you can move left or right (changing direction as needed),
and for every position you reach, you collect all the fruits present there.

Goal:
-----
Return the **maximum number of fruits** you can collect using at most `k` steps.

Constraints:
- The `fruits` array is sorted by positions in ascending order.
- Each position is unique.
*/

/*
Approach:
---------
1. **Preprocessing:**
   - Separate `fruits` into two arrays:
     - `position`: holds all the x-axis positions.
     - `amount_fruit`: holds the corresponding number of fruits.
   - Build a prefix sum array `prefix_fruit`, where `prefix_fruit[i]` holds the total number of fruits
     from index 0 to i-1.

2. **Two Walking Strategies:**
   Since direction switching has a step cost, we explore two strategies:
   
   A) Walk **left first**, then possibly to the right:
      - For all possible left steps (from 0 to k):
         - Calculate how far you can still go right using remaining steps.
         - Determine the range [left_pos, right_pos] you can cover.
         - Use binary search to find the corresponding indices in `position[]`.
         - Use the prefix sum to calculate the total fruits within this range.
         - Track the maximum.

   B) Walk **right first**, then possibly to the left:
      - Same logic as above, but starting with right steps.

3. **Binary Search:**
   - Use `lower_bound` and `upper_bound` to efficiently find positions within the reachable range.
   - Convert the indices into prefix sum difference to get the total fruits collected.

4. **Result:**
   - Return the maximum number of fruits collected from either strategy.

Time Complexity:
----------------
- O(n log n), where n is the number of fruit positions.
  (Due to binary search in each of the O(k) iterations.)

Space Complexity:
-----------------
- O(n) for storing positions, amount_fruit, and prefix sum.

Summary:
--------
This solution smartly leverages:
- Prefix sums for fast range queries.
- Binary search to identify reachable fruit positions.
- A greedy check across all combinations of left-first and right-first strategies to maximize fruit collection.
*/

class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        vector<int>position;
        vector<int>amount_fruit;

        for(const auto&fruit:fruits){
            position.push_back(fruit[0]);
            amount_fruit.push_back(fruit[1]);
        }
        int n = fruits.size();
        vector<int>prefix_fruit(n + 1, 0);
        for(int i = 1; i < n + 1; i++)prefix_fruit[i] = amount_fruit[i - 1] + prefix_fruit[i - 1];
        int max_fruits = 0;
        for(int step = 0; step <= k; step++){
            int left_pos = startPos - step;
            int right_pos = startPos + (k - (2 * step));
            auto index_left = distance(position.begin(), lower_bound(position.begin(), position.end(), left_pos));
            auto index_right =  distance(position.begin(), upper_bound(position.begin(), position.end(), right_pos));
            int total = prefix_fruit[index_right] - prefix_fruit[index_left];
            max_fruits = max(max_fruits, total);
        }

        for(int step = 0; step <= k; step++){
            int right_pos = startPos + step;
            int left_pos = startPos - (k - (2 * step));
            auto index_left = distance(position.begin(), lower_bound(position.begin(), position.end(), left_pos));
            auto index_right =  distance(position.begin(), upper_bound(position.begin(), position.end(), right_pos));
            int total = prefix_fruit[index_right] - prefix_fruit[index_left];
            max_fruits = max(max_fruits, total);
        }
        return max_fruits;
    }
};
