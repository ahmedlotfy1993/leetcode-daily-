class Solution {
    struct Pair_Comparetor{
        bool operator ()(const pair<int, int>& p1, const pair<int, int>& p2) const{
            return (p1.first != p2.first) ? p1.first < p2.first : p1.second < p2.second;
        }
    };
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int basket_size = baskets.size();
        int fruit_size = fruits.size();
        int non_found_type = 0;
        set<pair<int, int>, Pair_Comparetor>capacity_index;
        for(int i = 0; i < basket_size; i++){
            capacity_index.insert({baskets[i], i});
        }
        for(int i = 0; i < fruit_size; i++){
            auto it = lower_bound(capacity_index.begin(), capacity_index.end(), fruits[i], 
                                    [](const pair<int,int>& p, const int value){return p.first < value;});
            if(it == capacity_index.end()){
                non_found_type++;
            }else{
                int smallest_index = it->second;
                auto next_it = next(it);
                while(next_it != capacity_index.end()){
                    if(next_it->second < smallest_index){
                        smallest_index = next_it->second;
                        it = next_it;
                    }
                    next_it = next(next_it);
                }
                capacity_index.erase(it);
            }
        }
        return non_found_type;
    }
};
