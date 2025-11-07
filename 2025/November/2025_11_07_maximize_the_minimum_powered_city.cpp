/*
---------------------------------------------------------------------------------------
PROBLEM STATEMENT:
You are given a 0-indexed integer array stations of length n where stations[i] represents
the number of power stations in city i.

Each station supplies power to every city in range r:
    A station at city i affects all cities j such that |i - j| <= r.

The "power" of a city = total number of stations affecting it.

You can build k more stations (in any city). Return the maximum possible minimum power
across all cities after optimally adding these k stations.

---------------------------------------------------------------------------------------
APPROACH:
1. Precompute initial power of every city using prefix sum (sliding range sum).
2. Binary search on the answer (max possible min power).
3. For each candidate target power, simulate adding stations:
      - If city power < target → add required stations in the optimal location.
      - Two implementation options (enabled by macro flags below).

---------------------------------------------------------------------------------------
TIME & SPACE COMPLEXITY:

Approach 1: Sliding Window + Queue (`USING_QUEUE_APPROACH`)
    Time:  O(n log(maxPower))
    Space: O(n)   (queue holds added ranges)

Approach 2: Difference Array (`USING_DIFF_ARRAY_APPROACH`)
    Time:  O(n log(maxPower))
    Space: O(n)   (diff array)

---------------------------------------------------------------------------------------
*/

#define USING_QUEUE_APPROACH 1
#define USING_DIFF_ARRAY_APPROACH 0

class Solution {
public:
    long long maxPower(vector<int>& stations, int r, int k) {
        int n = stations.size();
        vector<long long> PrefixSum(n + 1, 0);
        vector<long long> InitialPower(n, 0);

        for (int i = 1; i <= n; i++)
            PrefixSum[i] = PrefixSum[i - 1] + stations[i - 1];

        for (int i = 0; i < n; i++) {
            int left = max(0, i - r);
            int right = min(n, i + r + 1);
            InitialPower[i] = PrefixSum[right] - PrefixSum[left];
        }
      
        long long left = 0;
        long long right = *max_element(InitialPower.begin(), InitialPower.end()) + k;
        auto canAchieve = [&](long long target) -> bool {
            long long used = 0;
            long long windowSum = 0;
#if USING_QUEUE_APPROACH
            queue<pair<int, long long>> q;
            for (int i = 0; i < n; i++) {
                while (!q.empty() && q.front().first <= i) {
                    windowSum -= q.front().second;
                    q.pop();
                }
                long long currentPower = InitialPower[i] + windowSum;
                if (currentPower < target) {
                    long long need = target - currentPower;
                    used += need;
                    if (used > k) return false;
                    windowSum += need;
                    int expireIndex = min(n, i + 2 * r + 1);
                    q.push({expireIndex, need});
                }
            }
#endif
#if USING_DIFF_ARRAY_APPROACH
            vector<long long> diff(n + 1, 0);
            for (int i = 0; i < n; i++) {
                windowSum += diff[i];
                long long currentPower = InitialPower[i] + windowSum;
                if (currentPower < target) {
                    long long need = target - currentPower;
                    used += need;
                    if (used > k) return false;
                    windowSum += need;
                    diff[i] += need;
                    diff[min(n, i + 2 * r + 1)] -= need;
                }
            }
#endif
            return true;
        };
        while (left <= right) {
            long long mid = (left + right) / 2;
            if (canAchieve(mid)) left = mid + 1;
            else right = mid - 1;
        }
        return right;
    }
};
