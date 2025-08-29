/*
Problem:
--------
Alice and Bob are playing a turn-based game with two lanes of flowers:
- Lane 1 contains x flowers (1 ≤ x ≤ n).
- Lane 2 contains y flowers (1 ≤ y ≤ m).
- Alice always plays first.
- Each turn, a player removes 1 flower from either lane.
- The player who removes the **last flower** wins (captures the opponent).

We need to count the number of pairs (x, y) such that **Alice wins the game**.

Key Insight:
------------
- The total number of flowers is (x + y).
- Since players alternate turns, the parity of (x + y) determines the winner:
  * If (x + y) is odd → Alice takes the last flower (Alice wins).
  * If (x + y) is even → Bob takes the last flower (Bob wins).

Therefore, the problem reduces to counting how many pairs (x, y) satisfy (x + y) being odd.
*/

/*
Approach 1 (Brute Force) :
-----------------------------------------
- Iterate over all pairs (x, y).
- Count pairs where (x + y) is odd.
- Works but too slow for large n, m.

Complexity:
-----------
- Time Complexity: O(n*m).
- Space Complexity: O(1).
*/

#define USE_BRUTE_FORCE
#ifdef USE_BRUTE_FORCE
class Solution {
public:
    long long flowerGame(int n, int m) {
        long long num_pairs = 0;
        for(int i = 1; i <=n; i++){
            for(int j = 1; j <=m; j++){
                if((i + j) % 2)num_pairs++;
            }
        }
        return num_pairs;
    }
};
#endif
/*
Approach 2 (Count Parity) :
--------------------------------------
- Count numbers of odds/evens separately:
    odd_n = (n + 1) / 2   → number of odds in [1..n]
    even_n = n / 2        → number of evens in [1..n]
    odd_m = (m + 1) / 2   → number of odds in [1..m]
    even_m = m / 2        → number of evens in [1..m]
- Alice wins when:
    (odd from lane1, even from lane2) OR (even from lane1, odd from lane2).
- So total winning pairs:
    odd_n * even_m + even_n * odd_m

Complexity:
-----------
- Time Complexity: O(1) (just arithmetic).
- Space Complexity: O(1).
*/
#define USE_PARITY_COUNT
#ifdef USE_PARITY_COUNT
class Solution {
public:
    long long flowerGame(int n, int m) {     
        long long int odd_n  = (n + 1) / 2; 
        long long int even_m = m / 2;
        long long int odd_m  = (m + 1) / 2;
        long long int even_n = n / 2;
        return (odd_n * even_m) + (odd_m * even_n);
    }
};
#endif
