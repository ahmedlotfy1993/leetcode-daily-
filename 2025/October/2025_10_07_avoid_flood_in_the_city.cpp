/*
Problem: Avoid Flood in The City
--------------------------------
We are given an array `rains` where:
  - `rains[i] > 0` means it rains on lake `rains[i]` that day.
  - `rains[i] == 0` means it’s a dry day — we can choose one lake to dry.

Goal:
Return an array `ans` such that:
  - `ans[i] = -1` if it rains that day.
  - `ans[i] = lake_id` if we choose to dry that lake on a dry day.
If it’s impossible to avoid floods (raining on a full lake), return an empty array.

Example:
---------
Input:  rains = [1,2,0,0,2,1]
Output: [-1,-1,2,1,-1,-1]

Explanation:
- Day 0: Rain fills lake 1
- Day 1: Rain fills lake 2
- Day 2: Dry lake 2
- Day 3: Dry lake 1
- Day 4: Rain again on lake 2 (safe because it was dried)
- Day 5: Rain again on lake 1 (safe because it was dried)

--------------------------------------------------
Approach: Greedy + TreeSet (set) + HashMap
--------------------------------------------------
Underlying technique: **Event scheduling using an ordered set**

Idea:
- Use a hash map `lake_to_fullDay` to store the **last day** each lake became full.
- Use a set `dryDays` to store the **indices** of dry days available.
- When we encounter a rain on a lake that is already full:
  → We must find a dry day **after** it was last filled but **before** today to dry it.
  → Use `dryDays.upper_bound(last_rain_day)` to find the earliest possible dry day.

Steps:
1. Iterate through `rains`:
   - If `rains[i] == 0`, add this day index to `dryDays` and set `ans[i] = 1` as a placeholder.
   - If `rains[i] > 0`:
     - If the lake was already full (exists in `lake_to_fullDay`):
       - Find the earliest dry day after the last rain using `upper_bound`.
       - If not found → flood is unavoidable → return empty array.
       - Otherwise, assign that dry day to dry this lake, remove it from the set.
     - Mark the lake as full again (`lake_to_fullDay[lake] = i`).
     - Set `ans[i] = -1`.

2. Return the constructed `ans` array.

--------------------------------------------------
Time Complexity:  O(n log n)
   - Each insertion and lookup in `set` is O(log n).
Space Complexity: O(n)
   - For the map and set.

Underlying Technique:
- Greedy choice guided by the **closest future constraint** (dry as late as possible but before next rain).

--------------------------------------------------
*/

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        vector<int> ans(n, 0);
        unordered_map<int, int> lake_to_fullDay;  
        set<int> dryDays;

        for (int i = 0; i < n; ++i) {
            int lake = rains[i];

            if (lake == 0) {
                dryDays.insert(i);
                ans[i] = 1;
            } else {
                if (lake_to_fullDay.count(lake)) {
                    // This lake was already full; we must have dried it in between
                    auto it = dryDays.upper_bound(lake_to_fullDay[lake]);
                    if (it == dryDays.end()) {
                      ans.clear();
                      break;
                    }
                    ans[*it] = lake; 
                    dryDays.erase(it);
                }
                lake_to_fullDay[lake] = i;
                ans[i] = -1;
            }
        }
        return ans;
    }
};
