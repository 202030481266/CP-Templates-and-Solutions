class Solution {
    int ans = 0;
public:
    void dfs(int cur, vector<int>& status, vector<int>& boxes, vector<int>& vis, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes) {
        vis[cur] = 1;
        ans += candies[cur];
        for (int& k : keys[cur]) {
            status[k] = 1;
            if (boxes[k] && !vis[k]) {
                dfs(k, status, boxes, vis, candies, keys, containedBoxes);
            }
        }
        for (int& v : containedBoxes[cur]) {
            boxes[v] = 1;
            if (status[v] && !vis[v]) {
                dfs(v, status, boxes, vis, candies, keys, containedBoxes);
            }
        }
    }
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int n = status.size();
        vector<int> boxes(n, 0);
        vector<int> vis(n, 0);
        for (int& b : initialBoxes) {
            boxes[b] = 1;
            if (status[b])
                dfs(b, status, boxes, vis, candies, keys, containedBoxes);
        }
        return ans;
    }
};