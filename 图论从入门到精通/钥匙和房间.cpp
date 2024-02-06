// 简单的图遍历
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        // 简而言之，就是连通块问题，是否会造成死锁
        int n = rooms.size();
        vector<bool> vis(n, false);
        vis[0] = true;
        function<void(int)> dfs = [&](int u) {
            for (int& v : rooms[u]) 
                if (!vis[v]) {
                    vis[v] = 1;
                    dfs(v);
                }
        };
        dfs(0);
        for (int i = 0; i < n; ++i)
            if (!vis[i]) return false;
        return true;
    }
};