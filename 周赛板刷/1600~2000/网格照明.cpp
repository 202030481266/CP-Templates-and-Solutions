typedef long long ll;
class Solution {
    unordered_map<ll, int> exist;
    unordered_map<ll, int> cnt[4];
public:
    // 需要判断是否超过边界（不然的话hash点就会产生哈希冲突）
    // 这道题目有重复的点
    vector<int> gridIllumination(int n, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        for (auto& v : lamps) {
            ll x = v[0], y = v[1];
            if (exist[x * n + y]) continue;
            exist[x * n + y] = 1;
            ++cnt[0][x];
            ++cnt[1][y];
            ++cnt[2][x + y];
            ++cnt[3][y - x];
        }
        vector<int> ans;
        for (auto& q : queries) {
            ll x = q[0], y = q[1];
            if (cnt[0][x] || cnt[1][y] || cnt[2][x + y] || cnt[3][y - x]) {
                // cout << x << ' ' <<y << ' ' << endl;
                // printf("%d %d %d %d\n", cnt[0][x], cnt[1][y], cnt[2][x + y], cnt[3][y - x]);
                ans.push_back(1);
                for (int i = -1; i <= 1; ++i)
                    for (int j = -1; j <= 1; ++j) {
                        ll nx = x + i, ny = y + j;
                        if (0 <= nx && nx < n && 0 <= ny && ny < n && exist[nx * n + ny]) {
                            // cout << "nx : " << nx << " ny : " << ny << endl;
                            --cnt[0][nx];
                            --cnt[1][ny];
                            --cnt[2][nx + ny];
                            --cnt[3][ny - nx];
                            exist[nx * n + ny] = 0;
                        }
                    }
            }
            // absolutely there is no lights
            else ans.push_back(0);
        }
        return ans;
    }
};