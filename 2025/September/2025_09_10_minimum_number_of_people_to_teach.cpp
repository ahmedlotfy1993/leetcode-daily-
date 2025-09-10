/*
 * Problem:
 * --------
 * We have `m` users and `n` languages. Each user knows some subset of languages.
 * There are friendships defined as pairs of users. Two friends can communicate if
 * they share at least one common language.
 *
 * Task:
 * -----
 * You can choose one language and teach it to some users so that *all friendships*
 * become communicable. Return the minimum number of users you need to teach.
 *
 * Notes:
 * - Friendships are not transitive.
 * - You may teach different subsets of users the same chosen language.
 *
 * Example:
 * --------
 * Input:
 *   n = 3
 *   languages = [[2],[1,3],[1,2],[3]]
 *   friendships = [[1,2],[1,3],[2,4]]
 * Output: 2
 *
 * Approaches:
 * -----------
 *
 * 1. USER_TO_LANGUAGES (active)
 *    - Build a mapping from each user -> set of languages.
 *    - For each friendship, check if the two friends share a language.
 *      If not, mark both users as "need to learn".
 *    - For each possible language, count how many of the "need-to-learn" users
 *      don't know it yet. The minimum across all languages is the answer.
 *
 *    Time Complexity: O(m * avg_languages_per_user + |friendships| * avg_languages_per_user + n * m)  
 *    Space Complexity: O(m * avg_languages_per_user)
 *
 * 2. LANGUAGE_TO_USERS
 *    - Build a mapping language -> set of users.
 *    - For each friendship, check if there exists at least one language both know
 *      (slower since you may check all languages).
 *    - If not, mark both users as "need to learn".
 *    - Then same counting step as approach (1).
 *
 *    Time Complexity: O(n * |friendships|) in worst case  
 *    Space Complexity: O(n * m)
 */

#define USER_TO_LANGUAGES   1   // Active solution
#define LANGUAGE_TO_USERS   0

class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
#if USER_TO_LANGUAGES
        int users = languages.size();
        vector<unordered_set<int>> user_to_languages(users + 1);
        for (int i = 0; i < users; i++) {
            user_to_languages[i + 1] = unordered_set<int>(languages[i].begin(), languages[i].end());
        }

        unordered_set<int> users_need_learn;
        for (auto& f : friendships) {
            int user1 = f[0], user2 = f[1];
            bool common_language = false;

            for (int lang : user_to_languages[user1]) {
                if (user_to_languages[user2].count(lang)) {
                    common_language = true;
                    break;
                }
            }
            if (!common_language) {
                users_need_learn.insert(user1);
                users_need_learn.insert(user2);
            }
        }

        if (users_need_learn.empty()) return 0;
        int result = INT_MAX;
        for (int lang = 1; lang <= n; lang++) {
            int langNotKnow = 0;
            for (int user : users_need_learn) {
                if (!user_to_languages[user].count(lang)) {
                    langNotKnow++;
                }
            }
            result = min(result, langNotKnow);
        }
        return result;
#endif

#if LANGUAGE_TO_USERS
        int users = languages.size();
        unordered_map<int, unordered_set<int>> languages_to_users;
        for (int i = 0; i < users; i++) {
            for (const auto& language : languages[i]) {
                languages_to_users[language].insert(i + 1);
            }
        }

        unordered_set<int> users_need_learn;
        for (const auto& friendship : friendships) {
            bool common_language = false;
            int user1 = friendship[0];
            int user2 = friendship[1];
            for (const auto& [language, users_set] : languages_to_users) {
                if (users_set.count(user1) && users_set.count(user2)) {
                    common_language = true;
                    break;
                }
            }
            if (!common_language) {
                users_need_learn.insert(user1);
                users_need_learn.insert(user2);
            }
        }

        if (users_need_learn.empty()) return 0;
        int result = INT_MAX;
        for (int lang = 1; lang <= n; lang++) {
            int langNotKnow = 0;
            for (int user : users_need_learn) {
                auto lang_it = find(languages[user - 1].begin(), languages[user - 1].end(), lang);
                if (lang_it == languages[user - 1].end()) {
                    langNotKnow++;
                }
            }
            result = min(result, langNotKnow);
        }
        return result;
#endif
    }
};
