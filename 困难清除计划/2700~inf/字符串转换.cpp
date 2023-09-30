// KMP + 数学公式推导 
typedef unsigned long long ull;
class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    vector<int> prefix_function(string s) {
        vector<int> p(s.length());
        int k = 0;
        for (int i = 1; i < s.length(); i++) {
            while (k > 0 && s[k] != s[i])
                k = p[k - 1];
            if (s[k] == s[i])
                ++k;
            p[i] = k;
        }
        return p;
    }
    vector<int> find_substring(string haystack, string needle) {
        int m = needle.length();
        if (m == 0)
            return {};
        vector<int> p = prefix_function(needle);
        vector<int> res;
        for (int i = 0, k = 0; i < haystack.size(); i++) {
            while (k > 0 && needle[k] != haystack[i])
                k = p[k - 1];
            if (needle[k] == haystack[i])
                ++k;
            if (k == m) {
                k = p[k - 1];
                if (i - m + 1 < m) res.push_back(i - m + 1);
            }
        }
        return res;
    }
    ull power(ull a, ull b) {
        ull res = 1;
        for (; b; b >>= 1) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
        }
        return res;
    }
    int numberOfWays(string s, string t, long long k) {
        string ss = s + s;
        auto res = find_substring(ss, t);
        ull n = s.size(), A = n - 1, M = power(n, mod - 2), x, cnt = res.size();
        if (k & 1) x = ((power(A, k) + 1) % mod * M % mod * cnt % mod);
        else x = ((power(A, k) - 1 + mod) % mod * M % mod * cnt % mod);
        if (cnt > 0 && res[0] == 0) {
            if (k & 1) x = (x - 1 + mod) % mod;
            else x = (x + 1) % mod;
        }
        return x;
    }
};


// 字符串HASH + 数学公式推导 （最后一个样例过不了，主要的锅在字符串hash冲突了）
typedef unsigned long long ull;
class Solution {
    static constexpr int mod = 1e9 + 7;
    int valid[500002], ans[500002];
    ull h[1000002];
public:
    ull power(ull a, ull b) {
        ull res = 1;
        for (; b; b >>= 1) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
        }
        return res;
    }
    ull quick_power(ull a, ull b) {
        ull res = 1;
        for (; b; b >>= 1) {
            if (b & 1) res = res * a;
            a = a * a;
        }
        return res;
    }
    int numberOfWays(string s, string t, long long k) {
        ull n = s.size();
        double mx = (n - 1) * k;
        if (mx < k + n - 1) {
            for (ull i = k; i <= (n - 1) * k; ++i)
                valid[i % n] = 1;
        }
        else {
            for (int i = 0; i < n; ++i)
                valid[i] = 1;
        }
        ull hash_t = 0, c = quick_power(mod, n);
        string ss = s + s;
        for (int i = 0; i < n; ++i) hash_t = hash_t * mod + t[i];
        for (int i = 1; i <= 2 * n; ++i) {
            h[i] = h[i - 1] * mod + ss[i - 1];
            if (i >= n) {
                ull tmp = h[i] - h[i - n] * c;
                if (tmp == hash_t && valid[i - n]) {
                    ans[i - n] = 1;
                }
            }
        }
        ull A = n - 1, M = power(n, mod - 2);
        ull x = 0, res = 0;
        for (int i = 0; i < n; ++i) if (ans[i]) ++res;
        if (k & 1) x = ((power(A, k) + 1) % mod * M % mod * res % mod);
        else x = ((power(A, k) - 1 + mod) % mod * M % mod * res % mod);
        if (ans[0]) {
            if (k & 1) x = (x - 1 + mod) % mod;
            else x = (x + 1) % mod;
        }
        return x;
    }
};