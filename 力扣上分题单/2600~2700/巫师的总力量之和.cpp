typedef unsigned long long ull;
class Solution {
    static constexpr int mod = 1e9 + 7;
    int sum[100010], S[100010], l[100010], r[100010];
public:
    int totalStrength(vector<int>& strength) {
        int n = strength.size();
        for (int i = 0; i < n; ++i) sum[i + 1] = (sum[i] + strength[i]) % mod;
        for (int i = 1; i <= n; ++i) S[i] = (S[i - 1] + sum[i]) % mod;
        stack<int> s;
        fill(l + 1, l + n + 1, 0);
        fill(r + 1, r + n + 1, n + 1);
        for (int i = 1; i <= n; ++i) {
            // 寻找右边严格小于
            while (!s.empty() && strength[s.top() - 1] > strength[i - 1]) {
                r[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        while (!s.empty()) s.pop();
        for (int i = n; i >= 1; --i) {
            // 寻找左边小于等于
            while (!s.empty() && strength[s.top() - 1] >= strength[i - 1]) {
                l[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        int ans = 0;
        auto f = [&](int left, int right) -> int {
            if (left == 0) {
                return S[right];
            }
            return (S[right] - S[left - 1] + mod) % mod;
        };
        for (int i = 1; i <= n; ++i) {
            int x = f(i, r[i] - 1), y = f(l[i], i - 1);
            ans = (ans + ((ull)(i - l[i]) * x % mod - (ull)(r[i] - i) * y % mod + mod) * strength[i - 1] % mod) % mod;
        }
        return ans;
    }
};
