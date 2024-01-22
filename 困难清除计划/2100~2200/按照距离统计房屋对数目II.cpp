class Solution {
    using ll = long long;
public:
    vector<long long> countOfPairs(int n, int x, int y) {
        vector<ll> ans(n + 1);
        if (x == y) {
            // 链
            for(int i = 1; i <= n; ++i) {
                ans[i] = 2 * (n - i);
            }
            return vector<ll>(ans.begin() + 1, ans.end());
        }
        --x;
        --y;
        if (x > y) swap(x, y);
        ll C = y - x + 1; 
        for (int i = 1; i <= C / 2; ++i) {
            if (i == C / 2) ans[i] += (C & 1 ? 2 * C : C);
            else ans[i] += 2 * C;
        }
        int N = x + 1 + n - y, D = N - 1;
        if (N > 2) { // N == 2 只能是环
            for (int i = 1; i <= D; ++i) {
                ans[i] += 2 * (N - i);
            }
            ans[1] -= 2; // x 和 y 重复了
            vector<ll> rs(n + 10);
            for (int i = x - 1, j = 1; i >= 0; --i, ++j) {
                // [1 + j, C / 2 + j]
                if (C & 1) {
                    // all add 2
                    rs[j + 1] += 2;
                    rs[C / 2 + j + 1] -= 2;
                }
                else {
                    // [1 + j, C / 2 + j - 1] add 2, C / 2 + j add 1
                    rs[1 + j] += 2;
                    rs[C / 2 + j] -= 1;
                    rs[C / 2 + j + 1] -= 1;
                }
                ans[j + 1] -= 2;
            }
            for (int i = y + 1, j = 1; i < n; ++i, ++j) {
                // [1 + j, C / 2 + j]
                if (C & 1) {
                    // all add 2
                    rs[j + 1] += 2;
                    rs[C / 2 + j + 1] -= 2;
                }
                else {
                    // [1 + j, C / 2 + j - 1] add 2, C / 2 + j add 1
                    rs[1 + j] += 2;
                    rs[C / 2 + j] -= 1;
                    rs[C / 2 + j + 1] -= 1;
                }
                ans[j + 1] -= 2;
            }
            for (int i = 1; i <= n; ++i) {
                rs[i] += rs[i - 1];
                ans[i] += rs[i] * 2;
            }
        }
        return vector<ll>(ans.begin() + 1, ans.end());
    }
};