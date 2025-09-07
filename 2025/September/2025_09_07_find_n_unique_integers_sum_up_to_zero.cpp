#include <ranges>
/*
 * Problem:
 * --------
 * Given an integer n, return any array containing n unique integers
 * such that their sum is exactly zero.
 *
 * Example:
 *   n = 5 → [-2, -1, 0, 1, 2]
 *   n = 4 → [-2, -1, 1, 2]
 *
*/

 /*
 * Implemented Approaches:
 * -----------------------
 *
 * 1. LOOP_BASED_CONSTRUCTION
 *    - Iterate index from 0 to n-1.
 *    - Compute each value relative to start = -(n/2).
 *    - If n is even and index crosses midpoint, skip zero.
 *
 *    Time Complexity: O(n)
 *    Space Complexity: O(n)
 *
 * 2. GENERATE_ALGORITHM
 *    - Use std::generate with a lambda.
 *    - Similar logic as above, but more declarative.
 *
 *    Time Complexity: O(n)
 *    Space Complexity: O(n)
 *
 * 3. RANGES_PIPELINE (C++20)
 *    - Use std::ranges::views::iota to generate indices [0..n-1].
 *    - Transform indices into correct symmetric values.
 *    - Functional/modern C++ style, avoids explicit loops.
 *
 *    Time Complexity: O(n)
 *    Space Complexity: O(n)
 *
 * Note:
 * -----
 * - All three approaches are equivalent in efficiency.
 * - Difference lies in readability and coding style preference.
 */

#define LOOP_BASED_CONSTRUCTION   0
#define GENERATE_ALGORITHM        0
#define RANGES_PIPELINE           1 

class Solution {
public:
    vector<int> sumZero(int n) {
#if LOOP_BASED_CONSTRUCTION
        vector<int> result(n);
        int start = -(n / 2);
        int index = 0;
        while (index < n) {
            int value = start + index;
            if ((n % 2 == 0) && index >= n / 2) value++; // skip 0 for even n
            result[index] = value;
            index++;
        }
        return result;
#endif

#if GENERATE_ALGORITHM
        vector<int> result(n);
        int start = -(n / 2);
        int i = 0;
        generate(result.begin(), result.end(), [&i, start, n]() {
            int value = start + i;
            if (n % 2 == 0 && i >= n / 2) value++; // skip 0 for even n
            ++i;
            return value;
        });
        return result;
#endif

#if RANGES_PIPELINE
        int start = -(n / 2);
        auto seq = std::ranges::views::iota(0, n) |
                   std::ranges::views::transform([=](int i) {
                       return start + i + (n % 2 == 0 && i >= n / 2 ? 1 : 0);
                   });
        return vector(seq.begin(), seq.end());
#endif    
    }
};
