/*
📘 Problem Summary:
You are given an array `energy` representing the energy (positive or negative) of `n` magicians standing in a line,
and an integer `k`. Starting from any magician `i`, you absorb their energy, then teleport to magician `(i + k)`,
continuing this process until you go out of bounds.  
You must take energy from every magician you land on.  
Your goal is to find the **maximum total energy** you can accumulate from such a journey.

⚙️ Approach:
- Use **Dynamic Programming (DP)** from the end of the array.
- Let `dp[i]` represent the total energy gained starting from magician `i`.
- Transition:
  - `dp[i] = energy[i] + (i + k < n ? dp[i + k] : 0)`
- The maximum of all `dp[i]` values gives the best possible energy gain.
- This works efficiently since we reuse computed results and move backward.

💡 Underlying Technique:  
Dynamic Programming (Bottom-Up) — specifically **1D DP with jump transitions**.

🕒 Time Complexity: O(n)  
💾 Space Complexity: O(n)
*/
class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        int n = energy.size();
        vector<int>dp(n,0);
        for(int i = n - 1; i >= 0; i--){
            dp[i] = energy[i] + (i + k < n ? dp[i + k]: 0);
        }
        return *max_element(dp.begin(), dp.end());
    }
};
