/*
 * Problem:
 * --------
 * On day 1, one person discovers a secret.
 *
 * Rules:
 *  - After `delay` days, a person starts sharing the secret with 1 new person per day.
 *  - After `forget` days, the person forgets the secret and can no longer share it.
 *
 * Given:
 *   - n: the total number of days
 *   - delay: number of days before sharing starts
 *   - forget: number of days after which a person forgets
 *
 * Return:
 *   The number of people who still know the secret at the end of day n.
 *   Answer modulo 1e9 + 7.
 *
 * Example:
 *   n = 6, delay = 2, forget = 4
 *   Output = 5
 *
 * Approaches:
 * -----------
 *
 * 1. SIMULATION_WITH_DEQUE
 *    - Use a deque to track for each person the day they can start sharing 
 *      and the day they forget.
 *    - Iterate day by day, add new sharers, and remove those who forget.
 *    - Conceptually simple but inefficient (can blow up with large n).
 *
 *    Time Complexity: O(n^2) in worst case  
 *    Space Complexity: O(n)
 *
 * 2. DP_PROPAGATION (active)
 *    - Use dp[day] to store the number of *new people* who learn the secret on `day`.
 *    - For each day, propagate its "sharers" to future days in the window 
 *      [day + delay, day + forget).
 *    - Finally, sum contributions of dp[day] for days in [n - forget + 1, n].
 *    - Much more efficient for larger inputs.
 *
 *    Time Complexity: O(n * (forget - delay)) in naive form (can be optimized further)  
 *    Space Complexity: O(n)
 */

#define SIMULATION_WITH_DEQUE  0
#define DP_PROPAGATION         1 

class Solution {
    static constexpr int MOD = 1e9 + 7;
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
#if SIMULATION_WITH_DEQUE
        deque<pair<int, int>> dq;
        int people_counter = 1;
        int day_index = 1;
        dq.emplace_back(day_index + delay, day_index + forget);

        while (day_index <= n) {
            int current_people_num = people_counter;
            for (const auto& [delay_day, forget_day] : dq) {
                if (day_index >= delay_day && day_index < forget_day)
                    current_people_num = (current_people_num + 1) % MOD;
            }
            while (current_people_num > people_counter) {
                dq.emplace_back(day_index + delay, day_index + forget);
                people_counter++;
            }
            while (!dq.empty() && dq.front().second <= day_index) {
                dq.pop_front();
                people_counter--;
            }
            day_index++;
        }
        return people_counter;
#endif

#if DP_PROPAGATION
        vector<long long> dp(n + 1, 0);
        dp[1] = 1; 
        for (int day = 1; day <= n; day++) {
            long long sharers = dp[day];
            if (!sharers) continue;
            for (int next = day + delay; next < day + forget && next <= n; next++) {
                dp[next] = (dp[next] + sharers) % MOD;
            }
        }
        long long ans = 0;
        for (int day = n - forget + 1; day <= n; day++) {
            if (day >= 1) ans = (ans + dp[day]) % MOD;
        }
        return ans;
#endif
    }
};
