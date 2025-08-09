/*
    With base cases:
    If A ≤ 0 and B > 0: return 1 (A empty first)
    If A ≤ 0 and B ≤ 0: return 0.5 (both empty same time)
    If A > 0 and B ≤ 0: return 0 (B empty first)
*/
#define USING_RECURSION
class Solution {
  double func(int a, int b){
          if(a <= 0 && b > 0)return 1;
          if(a <= 0 && b <= 0)return 0.5;
          if ( a > 0 && b <= 0)return 0;
          return 0.25 * (func(a - 100, b) + func(a - 75, b - 25) + func(a - 50, b - 50) + func(a - 25, b - 75));
  }
public:
  double soupServings(int n) {
    return func(n);
  }
};
#define USING_NESTED_UNDORDERED_MAP
#ifdef USING_NESTED_UNDORDERED_MAP
class Solution {
    unordered_map<unsigned long int, unordered_map<unsigned long int, double>> memo;
    double func(int a, int b) {
        if (a <= 0 && b > 0) return 1.0;
        if (a <= 0 && b <= 0) return 0.5;
        if (a > 0 && b <= 0) return 0.0;

        if (memo[a].count(b)) return memo[a][b];

        memo[a][b] = 0.25 * (
            func(a - 100, b) +
            func(a - 75, b - 25) +
            func(a - 50, b - 50) +
            func(a - 25, b - 75)
        );
        return memo[a][b] ;
    }
public:
    double soupServings(int n) {
        if (n >= 4800) return 1.0;  // empirical optimization
        return func(n, n);
    }
};
#endif
#define USING_UNORDERED_MAP_WITHPAIR_KEY
#if USING_UNORDERED_MAP_WITHPAIR_KEY
class Solution {
        struct pair_hash{
            size_t operator()(const pair<int,int>& p) const{
                return hash<int>()(p.first) ^ (hash<int>()(p.second)<< 1);
            }
        };
        int m ;
        unordered_map<pair<int, int>, double, pair_hash> dp;
        double func (int i, int j){
            if (i <= 0 && j <= 0) return 0.5;
            if (i <= 0) return 1;
            if (j <= 0) return 0;
            
            pair<int, int> key = {i, j};
            if (dp.contains(key)) {
                return dp[key];
            }
            return dp[key] = (func(i - 4, j) + func(i - 3, j - 1) + func(i - 2, j - 2) + func(i - 1, j - 3)) /4;
        }
public:
    double soupServings(int n) {
        m = ceil(n / 25.0);
        for (int k = 1; k <= m; k++) {
            if (func(k, k) > 1 - 1e-5) {
                return 1;
            }
        }
        return func(m, m);
    }
};
#endif
