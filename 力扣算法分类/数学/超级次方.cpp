// https://leetcode.cn/problems/super-pow/description/
// 快速幂取模



class Solution {
public:
    static constexpr int mod = 1337;
    int superPow(int a, vector<int>& b) {
        return dfs(a, b, b.size() - 1);
    }
    int dfs(int a, vector<int>& b, int u) {
        if (u == -1) return 1;
        return qpow(dfs(a, b, u - 1), 10) * qpow(a, b[u]) % mod;
    }
    int qpow(int a, int b)  {
        int ans = 1;
        a %= mod;
        while (b) {
            if (b & 1) ans = ans * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return ans;
    }
};