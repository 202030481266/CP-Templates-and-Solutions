#include <bits/stdc++.h>
using namespace std;

// 根据 lc大数组元素的乘积 自创的题目 

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
class Solution
{
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
        ll l = 0, r = 44470852534272; // s(r)=10^15
        while (l + 1 < r) {
            ll mid = l + (r - l) / 2;
            if (S(mid) >= x) r = mid;
            else l = mid;
        }
        return r;
    }
    // 由于mod值每一次不一样，所以只能使用在线的算法
    vector<int> findSumOfElements(vector<vector<long long>> &queries)
    {
        vector<int> res;
        // s函数是容易计算的，但是s的反函数不容易计算
        for (auto& q : queries) {
            ll from = q[0], ed = q[1], mod = q[2];
            ll u = upper_bound(from)-1, v = upper_bound(ed)-1, ans = 0;
            // (u,v) + rem(v) + rem(u)
            int s1 = S(u+1) - from, s2 = S(v+1) - ed;//[0,u+1),[0,v+1)
            int m1 = 63 - __builtin_clzll(u), m2 = 63 - __builtin_clzll(v);
            for (int i = m1; i >= 0 && s1; --i) { // 保留高位
                if (u & (1ll << i)) {
                    ans += (1ll << i);
                    --s1;
                }
            }
            ans += v;
            for (int i = m2; i >= 0 && s2; --i) { // 保留低位
                if (v & (1ll << i)) {
                    ans -= (1ll << i); // 先加后减
                    --s2;
                }
            }
            if (v - u - 1 > 0) {
                // 等差数列
                ll n = v - u - 1; // (u,v)=[u+1,v-1]
                ans += (u+v) * n / 2;
            }
            res.push_back(ans);
        }
        return res;
    }
};
