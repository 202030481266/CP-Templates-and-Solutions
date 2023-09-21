typedef unsigned long long ull;
class Solution {
    ull pow(ull a, ull b) {
        ull res = 1;
        for (; b; b >>= 1) {
            if (b & 1) res = res * a;
            a = a * a;
        }
        return res;
    }
public:
    int longestValidSubstring(string word, vector<string>& forbidden) {
        int n = word.size();
        ull h[n + 1], p = 1e9 + 7;
        unordered_set<ull> hash;
        h[0] = 0;
        for (int i = 0; i < n; ++i)
            h[i + 1] = h[i] * p + word[i];
        for (string& s : forbidden) {
            ull tmp = 0;
            for (int i = 0; i < s.size(); ++i)
                tmp = tmp * p + s[i];
            hash.insert(tmp);
        }
        int l = 1, ans = 0;
        auto check = [&](int r) -> bool {
            int left = max(l, r - 9);
            for (int i = left; i <= r; ++i) {
                // [i, r]
                ull tmp = h[r] - h[i - 1] * pow(p, r - i + 1);
                if (hash.count(tmp)) return false;
            }
            return true;
        };
        for (int r = 1; r <= n; ++r) {
            while (l <= r && !check(r)) 
                ++l;
            if (r >= l) ans = max(ans, r - l + 1);
        }
        return ans;
    }
};