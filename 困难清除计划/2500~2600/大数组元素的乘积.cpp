#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll f[] = {
    0,
    1,
    4,
    12,
    32,
    80,
    192,
    448,
    1024,
    2304,
    5120,
    11264,
    24576,
    53248,
    114688,
    245760,
    524288,
    1114112,
    2359296,
    4980736,
    10485760,
    22020096,
    46137344,
    96468992,
    201326592,
    419430400,
    872415232,
    1811939328,
    3758096384,
    7784628224,
    16106127360,
    33285996544,
    68719476736,
    141733920768,
    292057776128,
    601295421440,
    1236950581248,
    2542620639232,
    5222680231936,
    10720238370816,
    21990232555520,
    45079976738816,
    92358976733184,
    189115999977472,
    387028092977152,
    791648371998720,
    1618481116086272
};
class Solution {
public:
    ll S(ll a) {
        // [0,a]所有的数字中二进制1的个数
        if (a == 0) return 0;
        int msb = 63 - __builtin_clzll(a);
        ll sum = 0;
        for (int i = msb; i >= 0 && a; --i) {
            if (a & (1ll << i)) {
                a -= 1ll << i;
                sum += f[i] + a;
            }
        }
        return sum;
    }
    ll upper_bound(ll x) {
        ll l = 0, r = 44470852534273; // s(r-1)=10^15
        while (l + 1 < r) {
            ll mid = l + (r - l) / 2;
            if (S(mid) >= x) r = mid;
            else l = mid;
        }
        return r;
    }
    ll pow_mod(ll a, ll b, ll p) {
        ll res = 1;
        a %= p; // a <= 2^50
        for (; b; b >>= 1, a = a * a % p) {
            if (b & 1) res = res * a % p;
        }
        return res;
    }
    ll cal(ll b, ll x) { // 观察周期性就可以计算出来
        ll div = x / (1ll << (b + 1)), r = x % (1ll << (b + 1));
        return div * (1ll << b) + (r >= (1ll << b) ? r - (1ll << b) + 1 : 0);
    }
    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        vector<int> res;
        for(auto& q : queries) {
            ll from = q[0] + 1, end = q[1] + 1, mod = q[2], ans=1; // 1-index
            ll lo = upper_bound(from), hi = upper_bound(end);
            if (lo == hi) {
                // 表明在一个[from,end]全部在lo-1一个数字中
                ll s = S(lo-1), t = 0;
                for (int i = 0; i < 50; i++) {
                    if ((lo-1) & (1ll<<i)) {
                        ++t;
                        if (t >= from-s && t <= end-s) {
                            ans = ans*(1ll<<i)%mod;
                        }
                    }
                }
            }
            else {
                // 拆位
                // [0, lo)1的个数大于from, [0,hi)的个数大于end
                ll s1 = S(lo-1), s2 = S(hi-1); // s1表示lo-1中应该保留的高位1的个数,s2表示hi-1中应该保留的低位1的个数
                for (int i = 0, t = 0; i < 50; i++) {
                    if ((lo-1) & (1ll<<i)) {
                        ++t;
                        if (t >= from-s1) ans = ans*(1ll<<i)%mod;
                    }
                }
                for (int i = 0, t = 0; i < 50; i++) {
                    if ((hi-1) & (1ll<<i)) {
                        ++t;
                        if (t <= end-s2) ans = ans*(1ll<<i)%mod;
                    }
                }
                // lo-1, (lo-1,hi-1), hi-1
                if (hi - lo - 1 > 0) {
                    for (int i = 0; i < 50; ++i) {
                        ll cnt = cal(i, hi-2) - cal(i, lo-1);
                        if (cnt > 0) 
                            ans = ans * pow_mod(1ll<<i, cnt, mod) % mod;
                    }
                }
            }
            res.push_back(ans);
        }
        return res;
    }
};
