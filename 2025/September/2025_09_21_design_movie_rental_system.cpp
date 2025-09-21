/**
 * @brief Problem Description:
 * ---------------------------
 * You manage a movie renting company with `n` shops, each shop may carry multiple movies with a given rental price.
 * You need to design a data structure that supports:
 *
 * 1. search(movie):
 *      - Return up to 5 cheapest shops where the movie is available (unrented).
 *      - If tie on price → shop with smaller ID first.
 *
 * 2. rent(shop, movie):
 *      - Mark movie as rented from given shop (only called if available).
 *
 * 3. drop(shop, movie):
 *      - Return previously rented movie (only called if rented).
 *
 * 4. report():
 *      - Return up to 5 currently rented movies (shop, movie) pairs.
 *      - Sort by price first, then by shop ID, then by movie ID.
 *
 * Constraints:
 * ------------
 * - shops carry at most one copy per movie.
 * - rent/drop always called in valid state (no invalid operations).
 * - We must maintain order efficiently for both available and rented sets.
 *
 * Solution Approaches:
 * --------------------
 * Approach 1 (MAP + NESTED SETS) [Less Compact]:
 * ----------------------------------------------
 * - inventory: shop -> (movie -> price)
 * - unrented: movie -> set<(price, shop)>
 * - rented: map<price, set<(shop, movie)>> (allows price-ordered traversal)
 *
 * Approach 2 (TUPLE-BASED SET + COMPARATOR) [More Compact]:
 * ---------------------------------------------------------
 * - inventory: movie -> (shop -> price)
 * - unrented: movie -> set<(price, shop)> (kept sorted)
 * - rented: single set<tuple<price, shop, movie>> with custom comparator
 *   so iteration gives globally cheapest rented movies in order.
 *
 * Complexity:
 * -----------
 * Let n = number of entries, m = number of rented movies.
 *
 * search(movie): O(log k + 5) where k = copies of that movie  
 * rent(movie):   O(log k + log m)  
 * drop(movie):   O(log k + log m)  
 * report():      O(min(5, m))  
 *
 * Space Complexity: O(n) for inventory + O(n) for unrented + O(m) for rented.
 */

#define USE_TUPLE_BASED_RENTED_SET 1

#if !USE_TUPLE_BASED_RENTED_SET
// ----------------------- Approach 1: MAP + NESTED SETS -----------------------
class MovieRentingSystem {
    // 1. Inventory: shop -> (movie -> price)
    using MoviePriceMap = unordered_map<int, int>;
    unordered_map<int, MoviePriceMap> inventory;

    // 2. Unrented movies: movie -> set of (price, shop)
    using PriceShopPair = pair<int, int>;
    using ShopSetByPrice = set<PriceShopPair>;
    unordered_map<int, ShopSetByPrice> unrented;

    // 3. Rented movies: price -> set of (shop, movie)
    using ShopMoviePair = pair<int, int>;
    using ShopMovieSet = set<ShopMoviePair>;
    map<int, ShopMovieSet> rented;

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (int i = 0; i < entries.size(); i++) {
            int shopID  = entries[i][0];
            int movieID = entries[i][1];
            int price   = entries[i][2];
            inventory[shopID][movieID] = price;
            unrented[movieID].emplace(price, shopID);
        }
    }

    vector<int> search(int movie) {
        vector<int> shops;
        if (unrented.count(movie)) {
            for (const auto& [price, shop] : unrented[movie]) {
                shops.push_back(shop);
                if (shops.size() == 5) break;
            }
        }
        return shops;
    }

    void rent(int shop, int movie) {
        int price = inventory[shop][movie];
        unrented[movie].erase({price, shop});
        if (unrented[movie].empty()) unrented.erase(movie);
        rented[price].emplace(shop, movie);
    }

    void drop(int shop, int movie) {
        int price = inventory[shop][movie];
        rented[price].erase({shop, movie});
        if (rented[price].empty()) rented.erase(price);
        unrented[movie].emplace(price, shop);
    }

    vector<vector<int>> report() {
        vector<vector<int>> result;
        for (const auto& [price, shopMovieSet] : rented) {
            for (const auto& [shop, movie] : shopMovieSet) {
                result.emplace_back(vector<int>{shop, movie});
                if (result.size() == 5) return result;
            }
        }
        return result;
    }
};
#endif

#if USE_TUPLE_BASED_RENTED_SET
// ----------------------- Approach 2: TUPLE-BASED SINGLE SET ------------------
class MovieRentingSystem {
    struct RentedComparator {
        bool operator()(const tuple<int,int,int>& a,
                        const tuple<int,int,int>& b) const {
            if (get<0>(a) != get<0>(b)) return get<0>(a) < get<0>(b); // price
            if (get<1>(a) != get<1>(b)) return get<1>(a) < get<1>(b); // shop
            return get<2>(a) < get<2>(b); // movie
        }
    };

    // 1. movie -> (shop -> price)
    unordered_map<int, unordered_map<int, int>> inventory;
    // 2. movie -> sorted (price, shop)
    unordered_map<int, set<pair<int,int>>> unrented;
    // 3. single sorted set for rented movies
    set<tuple<int,int,int>, RentedComparator> rented;

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        inventory.reserve(entries.size());
        unrented.reserve(entries.size());
        for (auto& e : entries) {
            int shop = e[0], movie = e[1], price = e[2];
            inventory[movie][shop] = price;
            unrented[movie].emplace(price, shop);
        }
    }

    vector<int> search(int movie) {
        vector<int> result;
        auto it = unrented.find(movie);
        if (it != unrented.end()) {
            for (auto iter = it->second.begin();
                 iter != it->second.end() && result.size() < 5; ++iter)
                result.push_back(iter->second);
        }
        return result;
    }

    void rent(int shop, int movie) {
        int price = inventory[movie][shop];
        auto it = unrented.find(movie);
        it->second.erase({price, shop});
        if (it->second.empty()) unrented.erase(it);
        rented.emplace(price, shop, movie);
    }

    void drop(int shop, int movie) {
        int price = inventory[movie][shop];
        rented.erase({price, shop, movie});
        unrented[movie].emplace(price, shop);
    }

    vector<vector<int>> report() {
        vector<vector<int>> result;
        for (auto it = rented.begin(); it != rented.end() && result.size() < 5; ++it) {
            auto [price, shop, movie] = *it;
            result.push_back({shop, movie});
        }
        return result;
    }
};
#endif
