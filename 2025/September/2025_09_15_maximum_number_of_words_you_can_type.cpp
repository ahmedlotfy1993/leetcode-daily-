/*
  Problem:
  --------
    You are given:
      - text: a string of words separated by a single space (no leading/trailing spaces)
      - brokenLetters: a string of distinct characters representing broken keys.
    Task: Count how many words in text can be fully typed using this keyboard.

  Approaches:
  -----------
  1) FIND_WITHIN_WORD_APPROACH (#if 0):
     - For each word in text, check if any broken letter appears using word.find().
     - If no broken letters are found, increment result.
     - Simple to implement but each find() scans the whole word repeatedly for each broken letter.
       → Potentially O(W * L * B), where B = number of broken letters.

  2) UNORDERED_SET_APPROACH (#if 1) [Default]:
     - Preprocess brokenLetters into an unordered_set<char> for O(1) membership check.
     - For each word, scan characters once, if any character is in broken set → discard word.
     - Efficient because each character check is constant time.

  Time Complexity:
  ----------------
    Approach 1: O(W * L * B)
    Approach 2: O(W * L)
    where:
      W = number of words, L = average word length, B = number of broken letters.

  Space Complexity:
  -----------------
    Approach 1: O(1)
    Approach 2: O(B) for the unordered_set.

*/
#define FIND_WITHIN_WORD_APPROACH 0
#define UNORDERED_SET_APPROACH    1
class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
#if FIND_WITHIN_WORD_APPROACH
        istringstream in{text};
        string word;
        int result = 0;

        while (in >> word) {
            bool haveBrokenCh = false;
            for (const auto& ch : brokenLetters) {
                if (word.find(ch) != string::npos) {
                    haveBrokenCh = true;
                    break;
                }
            }
            if (!haveBrokenCh) result++;
        }
        return result;
#endif

#if UNORDERED_SET_APPROACH
        unordered_set<char> broken(brokenLetters.begin(), brokenLetters.end());
        istringstream in{text};
        string word;
        int result = 0;

        while (in >> word) {
            bool canType = true;
            for (char c : word) {
                if (broken.count(c)) {
                    canType = false;
                    break;
                }
            }
            if (canType) result++;
        }
        return result;
#endif
    }
};
