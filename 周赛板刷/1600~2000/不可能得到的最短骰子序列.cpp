// 似乎是一个很巧妙的问题
class Solution {
public:
    int shortestSequence(vector<int>& rolls, int k) {
        // 贪心构造？尽量将一些能够匹配的放在后面
        int vis[k + 1], n = rolls.size(), cnt = 0, ans = 0;
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n; ++i) {
            if (!vis[rolls[i]]) {
                ++cnt;
                vis[rolls[i]] = 1;
                if (cnt == k) {
                    ++ans;
                    cnt = 0;
                    memset(vis, 0, sizeof(vis));
                }
            }
            // cout << i << ' ' << cnt << endl;
        }
        return ans + 1;
    }
};