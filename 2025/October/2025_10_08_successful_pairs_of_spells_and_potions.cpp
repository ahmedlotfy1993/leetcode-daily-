/*
Problem: Successful Pairs of Spells and Potions
-----------------------------------------------
You are given:
 - Two arrays:
      spells[i] → strength of the ith spell
      potions[j] → strength of the jth potion
 - An integer `success` → the threshold for a “successful” spell–potion pair.

A pair `(spell, potion)` is **successful** if:
      spell * potion ≥ success

You must return a vector `pairs` of size `n` where:
      pairs[i] = number of potions that form a successful pair with spells[i].

Example:
---------
Input:
  spells = [5,1,3], potions = [1,2,3,4,5], success = 7
Output:
  [4,0,3]

Explanation:
  For spell = 5 → potions {2,3,4,5} yield product ≥ 7  → count = 4  
  For spell = 1 → none yield product ≥ 7                → count = 0  
  For spell = 3 → potions {3,4,5} yield product ≥ 7    → count = 3

------------------------------------------------------------
Approach: Sorting + Binary Search (Greedy Threshold Finding)
------------------------------------------------------------
Underlying Technique: **Binary search on sorted array**  
(We find the smallest potion value that meets `spell * potion >= success`.)

Idea:
1. Sort the `potions` array.
2. For each `spell`, compute the minimum potion strength needed:
        potion_limit = ceil(success / spell) = (success + spell - 1) / spell
3. Find the first potion in `potions` that is ≥ potion_limit using `lower_bound`.
4. All potions after that index will make successful pairs.
5. Count = (total potions - index of first valid potion).

------------------------------------------------------------
Time Complexity:
  O(n log m)
  - Sorting potions: O(m log m)
  - For each spell (n), binary search over potions: O(log m)

Space Complexity:
  O(1) (excluding output vector)

------------------------------------------------------------
*/
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> result;
        sort(potions.begin(), potions.end());

        for (int spell : spells) {
            long long potion_limit = (success + spell - 1) / spell;
            auto it = lower_bound(potions.begin(), potions.end(), potion_limit);
            int num_success = (it == potions.end()) ? 0 : static_cast<int>(potions.end() - it);
            result.push_back(num_success);
        }

        return result;
    }
};
