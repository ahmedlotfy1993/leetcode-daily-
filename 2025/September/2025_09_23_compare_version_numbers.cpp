/**
 * Problem:
 * --------
 * Given two version strings version1 and version2, compare them.
 * A version string consists of revisions separated by '.' (dot).
 * - Each revision is converted to an integer (ignoring leading zeros).
 * - Missing revisions are treated as 0.
 *
 * Return:
 * -1 if version1 < version2
 *  1 if version1 > version2
 *  0 if equal
 *
 * Example:
 * --------
 * version1 = "1.01", version2 = "1.001"  => return 0 (both are [1,1])
 * version1 = "1.0",  version2 = "1.0.0" => return 0 (missing treated as 0)
 * version1 = "0.1",  version2 = "1.1"   => return -1
 *
 * Approaches:
 * -----------
 * 1. USE_SPLIT_AND_COMPARE
 *    - Split both version strings into integer vectors.
 *    - Pad shorter one with zeros, then compare element by element.
 *
 * 2. USE_INLINE_PARSE_AND_COMPARE
 *    - Parse both strings on the fly using find('.') and substr().
 *    - Compare revisions directly without storing the whole vector.
 *
 * Time Complexity:
 * ----------------
 * - Both approaches: O(n + m), where n and m are lengths of version1 and version2.
 *   (Each character is processed once).
 *
 * Space Complexity:
 * -----------------
 * - Split approach: O(k), where k = number of revisions (for storing vectors).
 * - Inline parsing: O(1) extra space (besides input strings).
 *
 * Trade-off:
 * ----------
 * - Split approach: easier to implement/read, but uses more memory.
 * - Inline parsing: memory efficient, slightly more complex string handling.
 */

#define USE_SPLIT_AND_COMPARE 0
#define USE_INLINE_PARSE_AND_COMPARE 1

#if USE_SPLIT_AND_COMPARE
class Solution {
    vector<int> splitToInts(const string& s) {
        vector<int> tokens;
        string token;
        stringstream ss(s);
        while (getline(ss, token, '.')) {
            tokens.push_back(token.empty() ? 0 : stoi(token)); // handle empty token (e.g., "1..0") as zero
        }
        return tokens;
    }

public:
    int compareVersion(string version1, string version2) {
        auto v1 = splitToInts(version1);
        auto v2 = splitToInts(version2);

        // Normalize lengths by padding with zeros
        if (v1.size() < v2.size()) v1.resize(v2.size(), 0);
        else if (v2.size() < v1.size()) v2.resize(v1.size(), 0);

        // Compare revisions
        for (size_t i = 0; i < v1.size(); i++) {
            if (v1[i] > v2[i]) return 1;
            if (v1[i] < v2[i]) return -1;
        }
        return 0;
    }
};
#endif

#if USE_INLINE_PARSE_AND_COMPARE
class Solution {
public:
    int compareVersion(string version1, string version2) {
        size_t i = 0, j = 0;
        size_t n1 = version1.size(), n2 = version2.size();

        while (i < n1 || j < n2) {
            // Find next dot positions
            size_t nextDot1 = version1.find('.', i);
            size_t nextDot2 = version2.find('.', j);

            // Extract substring representing revision
            string part1 = (nextDot1 == string::npos) ? version1.substr(i) : version1.substr(i, nextDot1 - i);
            string part2 = (nextDot2 == string::npos) ? version2.substr(j) : version2.substr(j, nextDot2 - j);

            // Convert to int (empty treated as zero)
            int num1 = part1.empty() ? 0 : stoi(part1);
            int num2 = part2.empty() ? 0 : stoi(part2);

            // Compare revisions
            if (num1 > num2) return 1;
            if (num1 < num2) return -1;

            // Advance indices
            i = (nextDot1 == string::npos) ? n1 : nextDot1 + 1;
            j = (nextDot2 == string::npos) ? n2 : nextDot2 + 1;
        }

        return 0;
    }
};
#endif
