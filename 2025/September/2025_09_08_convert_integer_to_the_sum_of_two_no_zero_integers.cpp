/*
 * Problem:
 * --------
 * A "No-Zero integer" is a positive integer that does not contain 
 * the digit '0' in its decimal representation.
 *
 * Given an integer n, return any list of two integers [a, b] such that:
 *   - a and b are No-Zero integers
 *   - a + b = n
 *
 * The test cases guarantee that at least one solution exists.
 * If multiple solutions exist, return any one of them.
 *
 * Example:
 *   Input: n = 11
 *   Output: [2, 9]   (since 2 + 9 = 11 and both contain no zeros)
 */

 /*
 * Approaches:
 * -----------
 *
 * 1. DIGIT_CHECK_FUNCTION
 *    - Write a helper `isNoZero(num)` that checks if a number has digit '0'.
 *    - Iterate from n/2 to n, test both i and (n - i).
 *    - Return the first valid pair.
 *
 *    Time Complexity: O(n * log(n))  (worst case check all pairs, log(n) to check digits)
 *    Space Complexity: O(1)
 *
 * 2. STRING_CONVERSION 
 *    - Instead of digit arithmetic, convert i and (n - i) to strings.
 *    - Use `find('0')` to check for zeros.
 *    - Slightly less efficient but very concise and readable.
 *
 *    Time Complexity: O(n * log(n))  (log(n) for string conversion and scanning digits)
 *    Space Complexity: O(log(n))     (string storage)
 *
 */

#define DIGIT_CHECK_FUNCTION   0
#define STRING_CONVERSION      1 

class Solution {
#if DIGIT_CHECK_FUNCTION
    bool isNoZero(int num) {
        while (num > 0) {
            if (num % 10 == 0) return false;
            num /= 10;
        }
        return true;
    }
#endif

public:
    vector<int> getNoZeroIntegers(int n) {
#if DIGIT_CHECK_FUNCTION
        vector<int> result(2);
        for (int i = n / 2; i < n; i++) {
            if (isNoZero(i) && isNoZero(n - i)) {
                result[0] = i;
                result[1] = n - i;
                break;
            }
        }
        return result;
#endif

#if STRING_CONVERSION
        vector<int> result(2);
        for (int i = n / 2; i < n; i++) {
            string num1 = to_string(i);
            string num2 = to_string(n - i);
            if ((num1.find('0') == string::npos) && (num2.find('0') == string::npos)) {
                result[0] = i;
                result[1] = n - i;
                break;
            }
        }
        return result;
#endif
    }
};
