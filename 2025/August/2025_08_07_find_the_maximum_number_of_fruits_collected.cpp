/*
 Calculate the fruit collected by the 1st children start (0,0) and move diagonal
 For the 2nd child & 3rd child use BFS with their starting point, fruit being collected and initial remaining steps number n - 1
 Explore next steps based on available directions for each child and avoid the following:
   1- Go to out of range rooms
   2- Go to diagonal room unless it's destination 
   3- Go to rooms which can not be reached by comparing distance (next move ,destination) with number of remaining steps - 1 
 When reach to destination room update the maximum collected fruits.
*/
class Solution {
    struct point{
        int x;
        int y;
    };
    int scaler_distance(const point& p1, const point& p2){
        return max (abs(p2.x - p1.x), abs(p2.y - p1.y));
    }
    int bfs_collect(const vector<vector<int>>& fruits, point start) {
        int n = fruits.size();
        point destination{ n - 1, n - 1 };
        int max_steps = n - 1;

        vector<point> directions;
        if (start.x == 0 && start.y == n - 1) 
            directions = { {1, -1}, {1, 0}, {1, 1} }; // second child moves
        else 
            directions = { {-1, 1}, {0, 1}, {1, 1} }; // third child moves
        
        int max_fruits = 0;
        queue<tuple<point, int, int>> q;
        q.push({ start, fruits[start.x][start.y], max_steps });

        while (!q.empty()) {
            auto [current_p, current_fruit, steps_left] = q.front();
            q.pop();

            if (current_p.x == destination.x && current_p.y == destination.y) {
                max_fruits = max(max_fruits, current_fruit);
                continue;
            }

            for (const auto& dir : directions) {
                point next_p = { current_p.x + dir.x, current_p.y + dir.y };
                int dist = scaler_distance(next_p, destination);

                bool out_of_grid = (next_p.x < 0 || next_p.y < 0 || next_p.x >= n || next_p.y >= n);
                bool is_reachable = (dist <= steps_left - 1);
                bool is_diag = (next_p.x == next_p.y);
                bool is_dest = (next_p.x == destination.x && next_p.y == destination.y);

                if (out_of_grid || !is_reachable || (is_diag && !is_dest))continue;

                int fruit_here = is_dest ? 0 : fruits[next_p.x][next_p.y];
                q.push({ next_p, current_fruit + fruit_here, steps_left - 1 });
            }
        }
        return max_fruits;
}
public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {

        int n = fruits.size();
        int fruit_collected = 0;
        
        // First child: moves diagonally from (0,0) to (n-1,n-1)
        for (int i = 0; i < n; ++i)fruit_collected += fruits[i][i];

        // Second child: BFS from (0, n-1)
        fruit_collected += bfs_collect(fruits, { 0, n - 1 });

        // Third child: BFS from (n-1, 0)
        fruit_collected += bfs_collect(fruits, { n - 1, 0 });

        // Total fruits collected
        return fruit_collected;
    }
};
