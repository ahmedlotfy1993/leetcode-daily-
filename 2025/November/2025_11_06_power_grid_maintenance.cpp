/********************************************************************************************
 * Problem:
 * You are given `c` power stations (1-based index). Connections form power grids where
 * stations are connected directly or indirectly.
 *
 * Queries:
 *   [1, x] → Maintenance check:
 *              - If station x is ONLINE → return x
 *              - If station x is OFFLINE → return smallest ONLINE station id in its grid
 *              - If no online station exists in that grid → return -1
 *
 *   [2, x] → Take station x OFFLINE (station structure/grid does NOT change)
 *
 * Important:
 *   - Connectivity is FIXED; taking a station offline does NOT break the graph.
 *   - We only change whether a station is considered online or offline.
 *
 * -----------------------------------------------------------------------------------------
 * APPROACH 1 (MACRO: USE_BFS_COMPONENTS)
 *   - Build adjacency list
 *   - BFS to assign a component ID to each station
 *   - Per component, maintain a sorted `set<int>` of ONLINE nodes
 *   - Query type [1]:
 *        - If x is online → answer is x
 *        - Else → return smallest element in component's set
 *   - Query type [2]:
 *        - Remove x from component's set
 *
 * Time Complexity:
 *   - Building components: O(c + n)
 *   - Each query: O(log c) due to set insert/erase
 *
 * Space Complexity:
 *   - O(c + n)
 *
 * -----------------------------------------------------------------------------------------
 * APPROACH 2 (MACRO: USE_DSU)
 *   - Use DSU (Union-Find) to group stations into power grids
 *   - For each DSU root maintain a `set<int>` holding ONLINE stations
 *   - Query operations same logic as above
 *
 * Time Complexity:
 *   - DSU: O( (c + n) α(c) )
 *   - Each query: O(log c)
 *
 * Space Complexity:
 *   - O(c)
 *
 * -----------------------------------------------------------------------------------------
 * Both approaches produce the same output.
 ********************************************************************************************/

#define USE_BFS_COMPONENTS 0
#define USE_DSU            1

class DSU {
public:
    DSU(int n) : parent(n + 1), rank(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa == pb) return;

        if (rank[pa] < rank[pb])
            parent[pa] = pb;
        else
            parent[pb] = pa;

        if (rank[pa] == rank[pb]) rank[pa]++;
    }

private:
    vector<int> parent;
    vector<int> rank;
};

class Solution {
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
#if USE_BFS_COMPONENTS

        vector<vector<int>> graph(c + 1);
        for (auto& e : connections) {
            int u = e[0], v = e[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<int> component(c + 1, -1);
        vector<bool> visited(c + 1, false);
        int compId = 0;
        
        for (int station = 1; station <= c; ++station) {
            if (!visited[station]) {
                queue<int> q;
                q.push(station);
                visited[station] = true;
                component[station] = compId;

                while (!q.empty()) {
                    int node = q.front(); q.pop();
                    for (int neigh : graph[node]) {
                        if (!visited[neigh]) {
                            visited[neigh] = true;
                            component[neigh] = compId;
                            q.push(neigh);
                        }
                    }
                }
                compId++;
            }
        }

        vector<set<int>> compSets(compId);
        for (int i = 1; i <= c; ++i)
            compSets[component[i]].insert(i);

        vector<bool> online(c + 1, true);
        vector<int> result;

        for (auto& q : queries) {
            int type = q[0];
            int x = q[1];

            if (type == 2 && online[x]) {
                online[x] = false;
                compSets[component[x]].erase(x);
            }
            else if (type == 1 && online[x]) {
                result.push_back(x);
            }
            else if (type == 1 && !online[x]) {
                int cid = component[x];
                if (compSets[cid].empty()) result.push_back(-1);
                else result.push_back(*compSets[cid].begin());
            }
        }

        return result;
#endif

#if USE_DSU
        DSU dsu(c);
        for (auto& e : connections)
            dsu.unite(e[0], e[1]);
        
        unordered_map<int, set<int>> compOnline;
        for (int i = 1; i <= c; ++i)
            compOnline[dsu.find(i)].insert(i);

        vector<bool> online(c + 1, true);
        vector<int> result;

        for (auto& q : queries) {
            int type = q[0];
            int x = q[1];
            int root = dsu.find(x);

            if (type == 2 && online[x]) {
                online[x] = false;
                compOnline[root].erase(x);
            }
            else if (type == 1 && online[x]) {
                result.push_back(x);
            }
            else if (type == 1 && !online[x]) {
                if (compOnline[root].empty()) result.push_back(-1);
                else result.push_back(*compOnline[root].begin());
            }
        }

        return result;
#endif
    }
};
