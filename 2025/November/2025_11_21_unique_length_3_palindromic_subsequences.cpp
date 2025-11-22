/*
    Problem Summary:
    ----------------
    Given a string s, count the number of **unique palindromic subsequences of length 3**.
    A subsequence is of the form "a_b_a", where the first and last characters are the same,
    and the middle character can be any character between them.

    Approach:
    ---------
    1. Track for each character ('a' to 'z'):
        - The first occurrence index.
        - The last occurrence index.
    2. For each character that appears at least twice:
        - Look at the substring between its first and last occurrence.
        - Count all unique characters appearing in between → each can form a unique palindrome.
    3. Sum the number of unique middle characters for all characters.

    Time Complexity:
    ----------------
    - O(n) to scan the string and record first/last indices.
    - O(n) in total for filling the middle characters sets.
    - O(26) to compute the final answer.
    → Overall: O(n)

    Space Complexity:
    -----------------
    - O(26) for first/last occurrence array.
    - O(26 * 26) in worst case for middle character sets.
    → Overall: O(1) practically, since 26 is constant.
*/

class Solution {
public:
    int countPalindromicSubsequence(string s) {
        // Record first and last occurrence of each character
        vector<vector<int>> char_indexPairs(26, vector<int>(2, -1));

        // Map from character index to set of middle characters
        unordered_map<int, set<int>> charIndex_to_middleCharsIndex;

        int n = s.size();
        for (int i = 0; i < n; i++) {
            int idx = s[i] - 'a';
            if (char_indexPairs[idx][0] == -1) char_indexPairs[idx][0] = i; // first occurrence
            char_indexPairs[idx][1] = i; // last occurrence
        }

        int ans = 0;

        for (int j = 0; j < 26; j++) {
            int first = char_indexPairs[j][0];
            int last  = char_indexPairs[j][1];
          
            for (int k = first + 1; k < last; k++)charIndex_to_middleCharsIndex[j].insert(s[k] - 'a');
            if (charIndex_to_middleCharsIndex.count(j))ans += charIndex_to_middleCharsIndex[j].size();
        }

        return ans;
    }
};
