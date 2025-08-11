/*
Problem:
Given a positive integer `n`, construct an array `powers` that contains the minimum number 
of powers of 2 (sorted in non-decreasing order) that sum up to `n`. This corresponds to 
the set bits in the binary representation of `n`, where each set bit at position `i` adds `2^i` to the array.

You're also given a list of queries, where each query is a pair [left, right], indicating 
a subarray of `powers`. For each query, compute the product of elements from `powers[left]` 
to `powers[right]`, inclusive, and return the result modulo 1e9 + 7.
*/

/*
Approach:
1. Extract the powers of 2 from `n` by checking each bit from 0 to 31.
   - If the ith bit is set, add `2^i` to the `powers` array.
   - The resulting array will be in sorted order because we iterate from LSB to MSB.

2. For each query:
   - Initialize a product as 1.
   - Iterate from index `left` to `right` in the `powers` array.
   - Multiply the elements one by one, applying modulo 1e9 + 7 after each multiplication to avoid overflow.

Time Complexity:
- Building `powers`: O(32) = O(1)
- Each query: O(m), where m is the size of the query range
- Overall: O(q * m), which is acceptable given that `powers` can have at most 32 elements.

No advanced math (like modular inverse) is used — just straightforward iteration and modular multiplication.
*/
#define WITHOUT_INVERSE_MODULAR
#ifdef WITHOUT_INVERSE_MODULAR
class Solution {
    static constexpr int MOD= 1e9 + 7;
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int>powers;
        for(int i = 0; i < 32; i++){
            if(n & (1 << i))powers.push_back(1 << i);
        }
        vector<int>result;
        for(const auto& query: queries){
            unsigned long long int mul = 1;
            for(int i = query[0]; i <= query[1]; i++){
                mul = (mul * powers[i]) % MOD;
            }
            result.push_back(static_cast<int>(mul));
        }
        return result;
    }
};
#endif
/*
Optimized Approach:
1. Extract all set bits in `n` to build the `powers` array.
2. Precompute a prefix product array `prefix` such that:
     prefix[i + 1] = (prefix[i] * powers[i]) % MOD
   This allows efficient O(1) range product queries using:
     product = (prefix[r + 1] * modInverse(prefix[l], MOD)) % MOD

3. To handle division under modulo, we use modular inverse:
   - When MOD is a prime (1e9 + 7), Fermat's Little Theorem gives:
     a⁻¹ ≡ a^(MOD - 2) mod MOD
   - We use fast modular exponentiation to compute this efficiently.

Advantages:
- Reduces per-query complexity from O(range) to O(log MOD)
- Scales well for many queries

Techniques Used:
- Bitwise manipulation to extract powers of 2
- Prefix products to enable fast range multiplication
- Modular inverse using Fermat’s Little Theorem and binary exponentiation
*/
#define INVERSE_MODULAR
#ifdef INVERSE_MODULAR
class Solution {
    static constexpr int MOD= 1e9 + 7;
    // Fermat's Little Theorem: a^(MOD-2) ≡ a^(-1) mod MOD
    long long modInverse(long long a, int mod) {
        long long res = 1;
        int exp = mod - 2;
        while (exp > 0) {
            if (exp & 1) res = (res * a) % mod;
            a = (a * a) % mod;
            exp >>= 1;
        }
        return res;
    }
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> powers;
        for(int i = 0; i < 32; i++) {
            if(n & (1 << i)) powers.push_back(1 << i);
        }

        int m = powers.size();
        vector<long long> prefix(m + 1, 1); // prefix[i] = product of first i powers
        for(int i = 0; i < m; i++) {
            prefix[i + 1] = (prefix[i] * powers[i]) % MOD;
        }

        vector<int> result;
        for(const auto& q : queries) {
            int l = q[0], r = q[1];
            long long inv = modInverse(prefix[l], MOD);
            long long res = (prefix[r + 1] * inv) % MOD;
            result.push_back((int)res);
        }

        return result;
    }
};
#endif
