class Solution {
    int vis[2][26][26];
public:
    int minimizeConcatenatedLength(vector<string>& words) {
        int n = words.size();
        vector<int> a;
        memset(vis, 0x3f, sizeof(vis));
        int cur = 1;
        vis[0][words[0][0] - 'a'][words[0].back() - 'a'] = words[0].size();
        for (int i = 1; i < n; ++i) {
            memset(vis[cur], 0x3f, sizeof(vis[cur]));
            int xx = words[i][0] - 'a', yy = words[i].back() - 'a', pre = cur ^ 1, len = words[i].size();
            for (int x = 0; x < 26; ++x)
                for (int y = 0; y < 26; ++y) 
                    if (vis[pre][x][y] != 0x3f3f3f3f) {
                        // x y xx yy
                        // xx yy x y
                        if (y == xx) 
                            vis[cur][x][yy] = min(vis[cur][x][yy], vis[pre][x][y] + len - 1);
                        else
                            vis[cur][x][yy] = min(vis[cur][x][yy], vis[pre][x][y] + len);
                        if (yy == x) 
                            vis[cur][xx][y] = min(vis[cur][xx][y], vis[pre][x][y] + len - 1);
                        else
                            vis[cur][xx][y] = min(vis[cur][xx][y], vis[pre][x][y] + len);
                    }
            cur ^= 1;
        }
        int ans = 0x3f3f3f3f;
        for (int i = 0; i < 26; ++i)
            for (int j = 0; j < 26; ++j)
                ans = min(ans, vis[cur ^ 1][i][j]);
        return ans;
    }
};