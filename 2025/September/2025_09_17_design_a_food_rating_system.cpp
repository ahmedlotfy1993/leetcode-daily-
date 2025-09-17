/*
  Problem:
  --------
  Design a food rating system that supports the following operations:

  1) changeRating(food, newRating):
       Updates the rating of the specified food.

  2) highestRated(cuisine):
       Returns the food with the highest rating for the specified cuisine.
       If multiple foods have the same highest rating, return the lexicographically smallest food name.

  Input:
  ------
  - foods[i]: name of the i-th food
  - cuisines[i]: cuisine type of the i-th food
  - ratings[i]: initial rating of the i-th food

  Approach:
  ---------
  - We use a map `cuisine_to_foods` to store, for each cuisine, a sorted set of (rating, food) pairs.
    The set is ordered by:
      - Highest rating first (descending order)
      - Lexicographically smallest name first (for ties)

  - For faster `changeRating`, we optionally maintain `food_info`, a direct lookup map:
      food -> {cuisine, rating}

    This allows O(log N) update instead of O(N log N) search.

  Macros:
  -------
  - USE_INLINE_LAMBDA_COMPARATOR : Choose between lambda comparator (1) or functor comparator (0)
  - USE_FOOD_INFO_MAP           : Enable optimized direct lookup for changeRating (1) or use linear search (0)

  Complexity:
  -----------
  - Each `changeRating` and `highestRated` operation:
      O(log N) with USE_FOOD_INFO_MAP = 1
      O(N log N) with USE_FOOD_INFO_MAP = 0
  - Space complexity: O(N)

*/

#define USE_INLINE_LAMBDA_COMPARATOR 1
#define USE_FOOD_INFO_MAP 1

struct FoodComparator {
    bool operator()(const pair<int, string>& a, const pair<int, string>& b) const {
        return a.first != b.first ? a.first > b.first : a.second < b.second;
    }
};

class FoodRatings {
#if USE_INLINE_LAMBDA_COMPARATOR
    inline static auto food_comp = [](const pair<int, string>&f1, const pair<int, string>& f2) {
        return f1.first != f2.first ? f1.first > f2.first : f1.second < f2.second;
    };
    using FoodSet = set<pair<int, string>, decltype(food_comp)>;
    unordered_map<string, FoodSet> cuisine_to_foods;
#else
    using FoodSet = set<pair<int, string>, FoodComparator>;
    unordered_map<string, FoodSet> cuisine_to_foods;
#endif

#if USE_FOOD_INFO_MAP
    unordered_map<string, pair<string, int>> food_info;
#endif

public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n = foods.size();
        for (int i = 0; i < n; i++) {
#if USE_INLINE_LAMBDA_COMPARATOR
            cuisine_to_foods.try_emplace(cuisines[i], food_comp);
#endif
            cuisine_to_foods[cuisines[i]].emplace(ratings[i], foods[i]);
#if USE_FOOD_INFO_MAP
            food_info[foods[i]] = {cuisines[i], ratings[i]};
#endif
        }
    }
    
    void changeRating(string food, int newRating) {
#if USE_FOOD_INFO_MAP
        auto& [cuisine, oldRating] = food_info[food];
        auto& food_set = cuisine_to_foods[cuisine];

        food_set.erase({oldRating, food});
        oldRating = newRating;
        food_set.emplace(newRating, food);
#else
        for (auto& [cuisine, food_list] : cuisine_to_foods) {
            auto it = std::find_if(food_list.begin(), food_list.end(),
                [=](const auto& item) { return item.second == food; });

            if (it != food_list.end()) {
                auto updated = *it;
                food_list.erase(it);
                updated.first = newRating;
                food_list.insert(updated);
                break;
            }
        }
#endif
    }
    
    string highestRated(string cuisine) {
        return cuisine_to_foods[cuisine].begin()->second;
    }
};

