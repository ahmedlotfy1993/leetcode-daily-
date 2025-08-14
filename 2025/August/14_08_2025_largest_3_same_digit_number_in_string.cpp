#include <vector>
#include <string>
/*
 * Problem:
 * Given a string `num` representing a large integer, find the maximum "good" integer.
 * An integer is considered "good" if:
 *   - It is a substring of `num` with length exactly 3.
 *   - It contains only one unique digit (e.g., "000", "111", ..., "999").
 * Return the largest good integer (as a string), or an empty string if none exists.
 *
 * Solution:
 * Since valid good integers are limited to 10 specific values ("000" to "999"),
 * we prepare a list of these good substrings in descending order.
 * We iterate through this list and check if any of these substrings appear in `num`.
 * The first match we find will be the largest possible good integer due to the ordering.
 * This approach avoids unnecessary scanning and guarantees optimal performance.
 *
 * Time Complexity: O(1), as the loop runs at most 10 times with efficient substring checks.
 * Space Complexity: O(1), ignoring the constant space used by the good strings vector.
 */
using namespace std;
class Solution {
    inline static vector<string>good_strings {"999", "888", "777", "666", "555", "444", "333", "222", "111", "000"};
public:
    string largestGoodInteger(string num) {
        string max_good {""};
        for(const auto& good_string: good_strings){
            if(num.contains(good_string)){
                max_good = good_string;
                break;
            }
        }
        return max_good;
    }
};
