/*
 * Problem:
 * Given an integer n, determine if its digits can be rearranged (without leading zeros)
 * to form a number that is a power of two (e.g., 1, 2, 4, 8, 16, 32, ...).
*/

/*
 * My Solution:
 * - I count the frequency of each digit in the input number using an unordered_map.
 * - Then I loop through all powers of 2 up to 2^30 (since 2^30 > 10^9).
 * - For each power of 2, I count its digit frequencies using the same approach.
 * - I compare the two frequency maps. If they match, it means a permutation exists that is a power of 2, so I return true.
 */
#define SOLUTION_1
#ifdef SOLUTION_1
class Solution {
    bool check_powerof2(const unordered_map<char, int>& my_digits_number, int number) {
        string number_s = to_string(number);
        unordered_map<char, int> digits_number;

        for (const auto& ch : number_s) digits_number[ch]++;

        return digits_number == my_digits_number;
    }
public:
    bool reorderedPowerOf2(int n) {
        string number_s = to_string(n);
        unordered_map<char, int>digits_number;
        bool result = false;
        for(const auto& ch: number_s)digits_number[ch]++;
        for(int i = 0; i <  31; i++){
            if (check_powerof2(digits_number,  1 << i)){
                result =  true;
                break;
            }
        }
        return result;
    }
};
#endif

/*
 * Optimized Solution:
 * - Instead of generating all permutations, we take advantage of the fact that two numbers
 *   with the same digits (regardless of order) will have the same sorted digit string.
 * - We precompute all powers of 2 from 2^0 to 2^30 and store their sorted digit strings
 *   in an unordered_set for fast lookup.
 * - For the input number, we sort its digits and check if it exists in the set.
 * - This approach is optimal in both time and memory:
 *   * Time: O(31 × log N) — very efficient since only 31 comparisons are needed.
 *   * Memory: Constant — only 31 small strings are stored.
 */
#define SOLUTION_2
class Solution {
public:
    bool reorderedPowerOf2(int n) {
        static unordered_set<string> power_of_2_digits;

        if (power_of_2_digits.empty()) {
            for (int i = 0; i < 31; ++i) {
                int power = 1 << i;
                string s = to_string(power);
                sort(s.begin(), s.end());
                power_of_2_digits.insert(s);
            }
        }

        string ns = to_string(n);
        sort(ns.begin(), ns.end());

        return power_of_2_digits.count(ns);
    }
};
#ifdef SOLUTION_2
#endif
