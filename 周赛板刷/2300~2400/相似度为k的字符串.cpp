class Solution {
    typedef long long ll;
public:
    int get(int i, ll s) {
        return ((s >> (3 * i)) & 7);
    }
    ll set(int i, ll s, ll v) {
        ll k = get(i, s);
        ll tmp = (s ^ (k << (3 * i)));
        tmp |= (v << (3 * i));
        return tmp;
    }
    int kSimilarity(string s1, string s2) {
        int n = s1.size();
        vector<ll> a;
        vector<ll> b;
        for (int i = 0; i < n; ++i)
            if (s1[i] != s2[i]) {
                a.emplace_back(s1[i] - 'a');
                b.emplace_back(s2[i] - 'a');
            }
        n = a.size();
        unordered_map<ll, int> f;
        ll s = 0;
        for (int i = 0; i < n; ++i) {
            s |= (a[i] << (3 * i));
        }
        function<int(int, ll)> dfs = [&](int p, ll S) -> int {
            if (p == n) return 0;
            if (f.count(S)) return f[S];
            int rs = INT_MAX, ap = get(p, S);
            if (b[p] == ap) 
                rs = min(rs, dfs(p + 1, S));
            else {
                for (int i = p + 1; i < n; ++i)
                    if (get(i, S) == b[p]) { // swap(i, p)
                        ll x = set(p, S, b[p]);
                        x = set(i, x, ap);
                        rs = min(rs, 1 + dfs(p + 1, x));
                    }
            }
            return f[S] = rs;
        };
        return dfs(0, s);
    }
};