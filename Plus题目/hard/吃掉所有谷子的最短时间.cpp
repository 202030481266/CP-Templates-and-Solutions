class Solution {
    // 玄学复杂度
public:
    int minimumTime(vector<int>& hens, vector<int>& grains) {
        vector<int> a, b;
        map<int, int> mp;
        for (int& v : hens) {
            mp[v] += 1;
        }
        for (int& v : grains) {
            if (!mp.count(v)) {
                mp[v] = 0;
            }
        }
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            a.push_back(it->first);
            b.push_back(it->second);
        }
        int m = a.size();
        vector<int> nearest(m + 1), pre(m + 1);
        vector<int> dp(m + 1, INT_MAX);
        dp[0] = 0;
        int last = 0, cur = 0;
        for (int i = 1; i <= m; ++i) {  // 1 - index
            if (b[i - 1]) {
                last = cur;
                cur = i;
            }
            nearest[i] = cur;
            pre[i] = last;
        }
        for (int i = 1; i <= m; ++i) { // 1 - index
            int h = nearest[i];
            if (h <= 0) continue;
            for (int j = h; j > pre[i]; --j) { 
                // [j, i]
                int x = min(a[i - 1] - a[h - 1], a[h - 1] - a[j - 1]);
                int y = max(a[i - 1] - a[h - 1], a[h - 1] - a[j - 1]);
                if (mp[a[h - 1]] == 1) // 一只母鸡需要往回跑
                    dp[i] = min(dp[i], max(dp[j - 1], x + a[i - 1] - a[j - 1]));
                else dp[i] = min(dp[i], max(dp[j - 1], y)); // 多只母鸡分开跑
            }
        }
        return dp[m];
    }
};