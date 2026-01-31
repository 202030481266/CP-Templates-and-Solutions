class Solution {
public:
    int confusingNumberII(int num) {
        // [1, n]
        // 0, 1, 6, 8, 9, 经典的数位dp
        string s = to_string(num);
        int n = s.size(), dp[n];
        vector<int> arr{0, 1, 6, 8, 9};
        vector<int> axis{0, 1, 8};

        memset(dp, -1, sizeof(dp));

        // 感觉记忆化不了，这道题目，因为是回文的属性，后半段是和前半段一样的，感觉是暴力dfs
        function<int(int, bool)> dfs = [&](int p, bool is_limit) -> int {
            if (p == n) return 1;
            if (!is_limit && dp[p] != -1) return dp[p]; 
            int up = (is_limit ? s[p] - '0' : 9), res = 0;
            for (int& v : arr) {
                if (v > up) break;
                res += dfs(p + 1, is_limit && (v == up));
            }
            if (!is_limit) dp[p] = res;
            return res;
        };
        int sum = dfs(0, true);
        
        // 单独使用dfs求解混淆数字感觉是更加快的
        // 因为混淆数字是很少的
        vector<int> c{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
        vector<int> cur;
        unordered_map<int, int> mp {{0, 0}, {1, 1}, {6, 9}, {8, 8}, {9, 6}};
        function<void(int, int, bool)> cal = [&](int p, int len, bool odd) {
            if (p == len) {
                long long x = 0;
                if (!odd) {
                    // 偶数的长度, len * 2
                    for (int i = 0, j = len * 2 - 1; i < len; ++i, --j) {
                        x += 1ll * c[j] * cur[i];
                        x += 1ll * mp[cur[i]] * c[len * 2 - 1 - j];
                    }
                    if (x <= num) --sum;
                }
                else {
                    // 奇数的长度, len * 2 + 1
                    for (int i = 0, j = len * 2; i < len; ++i, --j) {
                        x += 1ll * c[j] * cur[i];
                        x += 1ll * mp[cur[i]] * c[len * 2 - j];
                    }
                    for (int& v : axis) {
                        if (x + 1ll * v * c[len] <= num)
                            --sum;
                    }
                }
                return;
            }
            for (int& v : arr) {
                if (v == 0 && p == 0) continue; // 不能从0开始
                cur.push_back(v);
                cal(p + 1, len, odd);
                cur.pop_back();
            }
        };
        for (int i = 1; i <= n; ++i) cal(0, i / 2, i & 1);
        return sum;
    }
};