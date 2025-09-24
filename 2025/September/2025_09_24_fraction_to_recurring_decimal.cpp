/**
 * Problem:
 * --------
 * Given two integers numerator and denominator, return the fraction as a string.
 * - If the fractional part is repeating, enclose the repeating part in parentheses.
 *
 * Examples:
 * ----------
 * 1. numerator = 1, denominator = 2  => "0.5"
 * 2. numerator = 2, denominator = 3  => "0.(6)"
 * 3. numerator = 4, denominator = 333 => "0.(012)"
 *
 * Approach:
 * ---------
 * 1. Handle the sign: use XOR to detect negative result.
 * 2. Use long long to avoid overflow with INT_MIN.
 * 3. Compute integer part: numerator / denominator.
 * 4. Compute fractional part using remainder:
 *    - Multiply remainder by 10 each step.
 *    - Track each remainder's index using a hashmap.
 *    - If a remainder repeats, insert parentheses at the first occurrence.
 *
 * Time Complexity: O(n), where n is the length of the fractional part.
 * Space Complexity: O(n), for storing remainders in the hashmap.
 */
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        ostringstream result;
        if (numerator == 0) result << 0;
        else{
            if ((numerator < 0) ^ (denominator < 0)) result << "-";
            long long n = llabs((long long)numerator);
            long long d = llabs((long long)denominator);

            result << (n / d);
            long long remainder = n % d;
            if (remainder != 0){
                result << '.';
                unordered_map<long long, int> seen;
                string fractional;
                while (remainder != 0 && !seen.count(remainder)) {
                    seen[remainder] = fractional.size();
                    remainder *= 10;
                    fractional.push_back('0' + (remainder / d));
                    remainder %= d;
                }
                if (remainder != 0) {
                    fractional.insert(seen[remainder], "(");
                    fractional.push_back(')');
                }
                result << fractional;
            }
        }
        return result.str();
    }
};
