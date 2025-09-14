/*
  Problem:
  --------
    Implement a spellchecker with the following rules:
      1) Exact Match: Return the word itself if query exactly matches a word in wordlist.
      2) Case-Insensitive Match: If query matches ignoring capitalization, return first such match.
      3) Vowel-Insensitive Match: If query matches when all vowels are replaced with a wildcard
         (e.g. '*' or any vowel), return first such match.
      4) If no match found, return "".

    Precedence:
      Exact match > case-insensitive match > vowel-insensitive match.

  Approach:
  ---------
    - Build three data structures from wordlist:
        1) unordered_set for exact matches.
        2) unordered_map from lowercase form → first occurrence in wordlist.
        3) unordered_map from vowel-insensitive key → first occurrence in wordlist.
    - For each query:
        1) If exact match exists, return query.
        2) Else if lowercase match exists, return first mapped word.
        3) Else if vowel-insensitive match exists, return first mapped word.
        4) Else return "".

  Helper Functions:
  -----------------
    - toLower(): Converts string to lowercase.
    - makeVowelInsensitiveKey(): Converts string to lowercase and replaces vowels with '*'.

  Time Complexity:
  ----------------
    Preprocessing:
      O(W * L) where W = number of words in wordlist, L = average word length.
    Query Handling:
      O(Q * L) where Q = number of queries.
    Overall: O((W+Q)*L)

  Space Complexity:
  -----------------
    O(W * L) to store exact set, lowercase map, and vowel-insensitive map.

*/

class Solution {
    string toLower(const string& s) {
        string result = s;
        transform(result.begin(), result.end(), result.begin(),
                  [](unsigned char c) { return tolower(c); });
        return result;
    }

    string makeVowelInsensitiveKey(const string& s) {
        auto replace_vowels = [](unsigned char c) {
            return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') ? '*' : c;
        };
        string result = toLower(s);
        transform(result.begin(), result.end(), result.begin(),
                  [replace_vowels](unsigned char c) { return replace_vowels(c); });
        return result;
    }

public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
      
        unordered_set<string> exactMatchSet(wordlist.begin(), wordlist.end());
        unordered_map<string, string> caseInsensitiveMap;
        unordered_map<string, string> vowelInsensitiveMap;
        vector<string> result;

        for (const string& word : wordlist) {
            string lowercaseKey = toLower(word);
            string vowelKey = makeVowelInsensitiveKey(word);

            if (!caseInsensitiveMap.count(lowercaseKey))
                caseInsensitiveMap[lowercaseKey] = word;
            if (!vowelInsensitiveMap.count(vowelKey))
                vowelInsensitiveMap[vowelKey] = word;
        }

        for (const string& query : queries) {
            string lowercaseQueryKey = toLower(query);
            string vowelQueryKey = makeVowelInsensitiveKey(query);

            if(exactMatchSet.count(query))
                result.push_back(query);
            else if (caseInsensitiveMap.count(lowercaseQueryKey))
                result.push_back(caseInsensitiveMap[lowercaseQueryKey]);
            else if (vowelInsensitiveMap.count(vowelQueryKey))
                result.push_back(vowelInsensitiveMap[vowelQueryKey]);
            else
                result.push_back("");
        }

        return result;
    }
};
