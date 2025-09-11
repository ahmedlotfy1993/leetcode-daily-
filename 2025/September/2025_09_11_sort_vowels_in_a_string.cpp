/*
  Problem:
  --------
  Given a 0-indexed string s, return a new string t such that:
    - All consonants remain in their original positions.
    - All vowels ('a','e','i','o','u' in any case) are sorted by ASCII value.

  Approaches:
  -----------
    1) Multiset Approach (USE_MULTISET_APPROACH):
      - Traverse s, collect vowel indices and insert vowels into a multiset (keeps them sorted automatically).
      - Replace vowels at their indices in order by iterating over the multiset.
      - Simpler logic but multiset insertions cost O(log k) each.

    2) Vector + Sort Approach (USE_VECTOR_SORT_APPROACH): [Default]
      - Traverse s, collect vowel indices and vowels in two separate vectors.
      - Sort the vowels vector manually (O(k log k)).
      - Replace vowels back in order using stored indices.
      - Slightly faster in practice (contiguous memory, single sort pass).

  Time Complexity:
  ----------------
  Both approaches are O(n + k log k), where n = |s| and k = number of vowels.
  Space Complexity: O(k) for both (storing vowels and indices).
*/
#define USE_MULTISET_APPROACH     0
#define USE_VECTOR_SORT_APPROACH  1
class Solution {
public:
    string sortVowels(string s) {
#if USE_MULTISET_APPROACH
        unordered_set<char>vowels {'A','E','I','O','U','a','e','i','o','u'};
        int len = s.size();
        vector<int>indices;
        multiset<char> string_vowels;
        string result = s;
        for (int i = 0; i < len; i++) {
            if (vowels.count(s[i])) {
                indices.push_back(i);
                string_vowels.insert(s[i]);
            }
        }
        int index = 0;
        for (const auto& ch: string_vowels) {
            result[indices[index++]] = ch;
        }
        return result;
#endif
      
#if USE_VECTOR_SORT_APPROACH
        unordered_set<char> vowels {'A','E','I','O','U','a','e','i','o','u'};
        vector<int> indices;
        vector<char> collectedVowels;

        for (int i = 0; i < s.size(); i++) {
            if (vowels.count(s[i])) {
                indices.push_back(i);
                collectedVowels.push_back(s[i]);
            }
        }

        sort(collectedVowels.begin(), collectedVowels.end());

        string result = s;
        for (int i = 0; i < indices.size(); i++) {
            result[indices[i]] = collectedVowels[i];
        }

        return result;
#endif
    }
};
