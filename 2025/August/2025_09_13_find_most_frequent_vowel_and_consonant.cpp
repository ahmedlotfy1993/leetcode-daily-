/*
  Problem:
  --------
    Given a string s:
      1) Find the vowel (a, e, i, o, u) with maximum frequency.
      2) Find the consonant with maximum frequency.
    Return the sum of these two maximum frequencies.
    - If no vowels or consonants exist, their contribution is 0.
    - If multiple vowels/consonants share the maximum frequency, any one can be chosen.

  Approaches:
  -----------
  1) USE_UNORDERED_MAP_APPROACH:
      - Use unordered_map<char,int> to store frequency counts.
      - For each character, increment its frequency and update max vowel/consonant.
      - Simple and direct but requires hashing for each character.

  2) USE_VECTOR_COUNTING_APPROACH:
      - Use a vector<int> of size 26 for direct indexing (freq[ch - 'a']).
      - Faster than unordered_map (O(1) array access).
      - Still a single pass through the string.

  Time Complexity:
  ----------------
  O(n) – Single traversal of the string, updating counts in O(1) per character.

  Space Complexity:
  -----------------
  O(1) – Constant space (26 for vector or up to 26 keys in unordered_map).
*/

#define USE_UNORDERED_MAP_APPROACH 0
#define USE_VECTOR_COUNTING_APPROACH 1

class Solution {
public:
    int maxFreqSum(string s) {
#if USE_UNORDERED_MAP_APPROACH
        unordered_map<char, int> freq;
        int max_vowels = 0;
        int max_consonant = 0;

        for (char ch : s) {
            freq[ch]++;
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                max_vowels = max(max_vowels, freq[ch]);
            } else {
                max_consonant = max(max_consonant, freq[ch]);
            }
        }
        return max_vowels + max_consonant;
#endif

#if USE_VECTOR_COUNTING_APPROACH
        vector<int> freq(26, 0);
        int max_vowels = 0;
        int max_consonant = 0;

        for (char ch : s) {
            int idx = ch - 'a';
            freq[idx]++;
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                max_vowels = max(max_vowels, freq[idx]);
            } else {
                max_consonant = max(max_consonant, freq[idx]);
            }
        }
        return max_vowels + max_consonant;
#endif
    }
};
