/*
Problem: Maximum Total Damage from Non-Adjacent Spells
------------------------------------------------------
You are given an array `power`, where each element represents the damage of a spell.
Multiple spells can have the same damage value.

Constraint:
------------
If a magician casts a spell with a damage of `power[i]`, they cannot cast any spell with
damage values `power[i] - 2`, `power[i] - 1`, `power[i] + 1`, or `power[i] + 2`.

Each spell can be cast only once.

Goal:
------
Return the maximum total damage the magician can achieve.

-----------------------------------------------------------------
Approach 1: Using HashMap + DP
-----------------------------------------------------------------
1. Count the total damage for each unique spell damage using a hash map:
       totalDamage[val] = val * frequency(val)
2. Sort all unique damage values.
3. Use Dynamic Programming:
   - Let dp[i] = maximum damage we can get up to the i-th unique damage value.
   - Transition:
        dp[i] = max(dp[i-1], totalDamage[i] + dp[j]) 
        where j < i and unique[i] - unique[j] > 2
4. The answer is dp[n-1].

Underlying Technique:
----------------------
Dynamic Programming with non-adjacent value constraint 
(similar to “Delete and Earn” / “House Robber” problem).

Time Complexity  : O(n log n)   (sorting unique values)
Space Complexity : O(n)         (DP + hash map)
*/

#if USE_HASHMAP_BASED_DP
class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<int, long long> uniqueToSum;
        for (int p : power)
            uniqueToSum[p] += p;

        vector<int> uniqueValues;
        for (auto &kv : uniqueToSum)
            uniqueValues.push_back(kv.first);
        sort(uniqueValues.begin(), uniqueValues.end());

        int n = uniqueValues.size();
        vector<long long> dp(n, 0);

        for (int i = 0; i < n; ++i) {
            long long take = uniqueToSum[uniqueValues[i]];
            int j = i - 1;
            while (j >= 0 && uniqueValues[i] - uniqueValues[j] <= 2)
                j--;
            if (j >= 0)
                take += dp[j];
            dp[i] = i > 0 ? max(dp[i - 1], take) : take;
        }

        return dp[n - 1];
    }
};
#endif


/*
-----------------------------------------------------------------
Approach 2: Sorted Grouping + DP (Macro: USE_SORTED_GROUPING_DP)
-----------------------------------------------------------------
1. Sort `power` array directly.
2. Combine consecutive duplicates into (damage, totalDamage) pairs.
3. Apply the same DP idea:
      dp[i] = max(dp[i-1], totalDamage[i] + dp[j])
      where j is the last index before i with difference > 2.

This avoids hash maps and relies only on sorting and grouping.

Underlying Technique:
----------------------
Dynamic Programming on grouped sorted values (efficient and clean).

Time Complexity  : O(n log n)
Space Complexity : O(n)
*/

#if USE_SORTED_GROUPING_DP
class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        sort(power.begin(), power.end());

        vector<pair<int,long long>> uniqueToSum;
        for (int i = 0; i < (int)power.size();) {
            int v = power[i];
            long long sum = 0;
            while (i < (int)power.size() && power[i] == v)
                sum += power[i++];
            uniqueToSum.emplace_back(v, sum);
        }

        int n = uniqueToSum.size();
        vector<long long> dp(n);

        for (int i = 0; i < n; ++i) {
            long long take = uniqueToSum[i].second;
            int j = i - 1;
            while (j >= 0 && uniqueToSum[i].first - uniqueToSum[j].first <= 2)
                j--;
            if (j >= 0)
                take += dp[j];
            dp[i] = i > 0 ? max(dp[i-1], take) : take;
        }

        return dp[n-1];
    }
};
#endif
