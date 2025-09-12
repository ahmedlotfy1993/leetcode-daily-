/*
  Problem:
  --------
    Alice and Bob play a game on string s:
      - Alice starts, she can remove any substring with an ODD number of vowels.
      - Bob then removes any substring with an EVEN number of vowels.
      - The first player unable to make a valid move loses.
    Determine if Alice wins assuming both play optimally.

    Approaches:
    -----------
    1) USE_UNORDERED_SET_APPROACH:
      - Use an unordered_set<char> to store vowels and count them by lookup.
      - Simple but involves hash lookups.

    2) USE_INLINE_HELPER_FUNCTION_APPROACH: [Default]
      - Use a helper function is_vowel() for direct comparisons.
      - Slightly faster, avoids hashing overhead.

    Time Complexity:
    ----------------
    O(n), where n = |s| (just one pass to count vowels)
    
    Space Complexity:
    -----------------
    O(1), constant extra space.
*/
#define USE_INLINE_HELPER_FUNCTION_APPROACH 1
#define USE_UNORDERED_SET_APPROACH 0
class Solution {
    bool is_vowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

public:
    bool doesAliceWin(string s) {
#if USE_UNORDERED_SET_APPROACH
        unordered_set<char> vowels {'a', 'e', 'i', 'o', 'u'};
        int num_vowels = 0;
        for (char ch : s) {
            if (vowels.contains(ch)) num_vowels++;
        }
        return num_vowels != 0;
#endif

#if USE_INLINE_HELPER_FUNCTION_APPROACH
        int num_vowels = 0;
        for (char ch : s) {
            if (is_vowel(ch)) num_vowels++;
        }
        return num_vowels != 0;
#endif
    }
};
