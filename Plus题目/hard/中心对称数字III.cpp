// dfs也才4*10^5计算量
class Solution {
public:
    int strobogrammaticInRange(string low, string high) {
        vector<int> a{0, 1, 6, 8, 9};
        vector<int> b{0, 1, 9, 8, 6};

        vector<long long> c10
        {
            1 ,
            10 ,
            100 ,
            1000 ,
            10000 ,
            100000 ,
            1000000 ,
            10000000 ,
            100000000 ,
            1000000000 ,
            10000000000 ,
            100000000000 ,
            1000000000000 ,
            10000000000000 ,
            100000000000000 ,
            1000000000000000 ,
        };

        long long lo = stoll(low), hi = stoll(high);
        long long cur = 0;
        int n = high.size(), m = low.size(), ans = 0;
        function<void(int, int, int)> dfs = [&](int p, int len, int flag) {
            if (p == len) {
                if (cur >= lo && cur <= hi) {
                    ++ans;
                }
                return;
            }
            for (int i = 0; i < 5; ++i) {
                if ((p == 0 && i == 0 && (len > 1 || (len == 1 && !flag))) ||
                    (flag && p == len - 1 && (i == 2 || i == 4)))
                    continue; // 核心
                long long tmp;
                if (flag)
                    tmp = (p == len - 1
                               ? c10[p] * a[i]
                               : c10[p] * a[i] + c10[2 * len - 2 - p] * b[i]);
                else
                    tmp = (c10[p] * a[i] + c10[2 * len - 1 - p] * b[i]);
                cur += tmp;
                dfs(p + 1, len, flag);
                cur -= tmp;
            }
        };
        for (int i = m; i <= n; ++i) {
            dfs(0, (i + 1) / 2, i & 1);
        }
        return ans;
    }
};