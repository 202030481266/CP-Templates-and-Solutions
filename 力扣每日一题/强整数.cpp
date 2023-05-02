class Solution {
    typedef long long ll;
public:
    ll cal(int x, int n) {
        ll res = 1;
        for (long long p = x; n > 0; n >>= 1, p = (p * p))
            if ((n & 1) != 0)
                res = res * p;
        return res;
    }
    vector<int> powerfulIntegers(int x, int y, int bound) {
        ll cntx = 1, cnty = 1, xx = x, yy = y;
        if (xx > 1)
            while (xx <= bound) xx *= x, ++cntx;
        if (yy > 1)
            while (yy <= bound) yy *= y, ++cnty;
        set<ll> res;
        for (int i = 0; i < cntx; ++i)
            for (int j = 0; j < cnty; ++j) 
                if (cal(x, i) + cal(y, j) <= 1ll * bound) res.emplace(cal(x, i) + cal(y, j));
        vector<int> a;
        for (int v : res) a.emplace_back(v);
        return a;
    }
};