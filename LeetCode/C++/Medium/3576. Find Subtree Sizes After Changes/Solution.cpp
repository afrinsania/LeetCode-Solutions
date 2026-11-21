class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }

        vector<int> new_parent = parent;
        vector<int> last_seen(26, -1);

        // First DFS: find the closest matching ancestor for each node
        auto findParents = [&](auto& self, int u) -> void {
            int char_idx = s[u] - 'a';
            int prev_ancestor = last_seen[char_idx];

            if (prev_ancestor != -1) {
                new_parent[u] = prev_ancestor;
            }

            last_seen[char_idx] = u;
            for (int v : adj[u]) {
                self(self, v);
            }
            // Backtrack
            last_seen[char_idx] = prev_ancestor;
        };

        findParents(findParents, 0);

        // Build the new tree using the updated parent array
        vector<vector<int>> new_adj(n);
        for (int i = 1; i < n; ++i) {
            new_adj[new_parent[i]].push_back(i);
        }

        vector<int> ans(n, 1);

        // Second DFS: compute subtree sizes in the final tree
        auto calcSizes = [&](auto& self, int u) -> int {
            for (int v : new_adj[u]) {
                ans[u] += self(self, v);
            }
            return ans[u];
        };

        calcSizes(calcSizes, 0);
        return ans;
    }
};