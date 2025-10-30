/*
Problem:
--------
You are given an integer array `target`. You start with an integer array `initial`
(full of zeros) with the same size as `target`. In one operation, you may choose
any subarray of `initial` and increment each element in that subarray by 1.

Return the **minimum number of operations** required to transform `initial` into `target`.

Key Insight:
------------
Whenever `target[i] > target[i-1]`, we need exactly `(target[i] - target[i-1])`
new operations to raise that section. If `target[i] <= target[i-1]`, no new
operation is needed — previous increments already cover it.

Time Complexity:
----------------
Approach 1 (Difference-based Greedy):  O(n)
Approach 2 (Stack-based approach):      O(n) amortized

Space Complexity:
-----------------
Approach 1 (Difference-based Greedy):  O(1)
Approach 2 (Stack-based approach):      O(n) worst case (due to stack)
*/

class Solution {
public:
    int minNumberOperations(vector<int>& target) {

#if USE_DIFF_BASED_APPROACH       // Approach 1: Greedy using difference with previous element
        int operations = target[0];
        int n = target.size();
        for(int i = 1; i < n; i++){
            operations += max(target[i] - target[i-1], 0); 
        }
        return operations;
#endif

#if USE_STACK_BASED_APPROACH      // Approach 2: Stack-based tracking of increasing ranges
         stack<int> st;
        int operations = 0;

        for (int num : target) {

            if (st.empty() || st.top() < num) {
                int prev = st.empty() ? 0 : st.top();
                operations += num - prev;
            }
            while (!st.empty() && st.top() > num)
                st.pop();

            if (st.empty() || st.top() != num)
                st.push(num);
        }

        return operations;
#endif
    }
};
