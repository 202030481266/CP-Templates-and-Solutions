#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 2+1+1+1
// 3+1+1, 3+2
// 4+1
// 5
// x a x b c, a x x b c, a b x x c, a b x c x (a!=b, b!=c, c!=a)
// x x x a b, x a x x b, x a x b x, a x x x b, a x x b x, a b x x x (a can be b)
// x x x x a, x x x a x, x a x x x, a x x x x
// x x x x x

// 1 1  2 2 x 2 3 4 1 x

class Solution {
public:
    int subsequencesWithMiddleMode(vector<int>& nums) {
        int n = nums.size();
        vector<int> a(nums.begin(), nums.end());
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        for (int& v : nums) {
            v = lower_bound(a.begin(), a.end(), v) - a.begin();
        }
        int m = a.size();
        vector<ll> pre(m);
        vector<ll> suf(m);
        for (int i = 0; i < n; ++i) {
            suf[nums[i]]++;
        }
        ll ans = 0;
        ll left_sum = 0, right_sum = 0;
        ll pre_mul_suf = 0, pre_pre_mul_suf = 0, pre_mul_suf_suf = 0;
        for (int i = 0; i < m; ++i) {
            right_sum = (right_sum + suf[i]*(suf[i]-1)/2) % mod;
        }
        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            right_sum = (right_sum-(suf[x]-1)%mod + mod) % mod;
            pre_mul_suf = (pre_mul_suf - pre[x]%mod + mod) % mod;
            pre_pre_mul_suf = (pre_pre_mul_suf - pre[x]*pre[x]%mod + mod) % mod;
            pre_mul_suf_suf = (pre_mul_suf_suf - pre[x]*(2*suf[x]-1)%mod + mod) % mod;
            suf[x]--;
            // x x
            // cout << x << ' '<< pre[x] << ' ' << suf[x] << ' ' << ans << endl;
            ll left_double = pre[x]*(pre[x]-1)/2%mod, right_double = suf[x]*(suf[x]-1)/2%mod;
            // a x or x a (a != x)
            // [0,i), (i, n-1]
            ll left_one = pre[x]*i-pre[x]*pre[x], right_one = suf[x]*(n-i-1)-suf[x]*suf[x];
            // a b (a!=x, b!=x)
            ll left_zero = (i*(i-1)/2-left_double%mod-left_one%mod + mod)%mod;
            ll right_zero = ((n-i-1)*(n-i-2)/2-right_double%mod-right_one%mod + mod)%mod;
            // a b (a != b, a != x, b != x)
            ll left = (left_zero - left_sum%mod + left_double + mod) % mod;
            ll right = (right_zero - right_sum%mod + right_double + mod) % mod;
            // 5
            ans = (ans + left_double*right_double) % mod;
            // 4
            ans = (ans + left_double*right_one + left_one*right_double) % mod;
            // 3
            ans = (ans + left_double*right_zero + left_zero*right_double + left_one*right_one) % mod;
            // 2
            if (left*right_one > 0) {
                ans = (ans + left*right_one) % mod;
                // a b x a x, [0,i)
                ll t = pre_mul_suf - pre[x]*suf[x];
                ll s = pre_pre_mul_suf - pre[x]*pre[x]*suf[x];
                ll extra = suf[x]*(t*(i-pre[x])%mod - s%mod + mod) % mod;
                ans = (ans - extra % mod + mod) % mod;
            }
            if (right*left_one > 0) {
                ans = (ans + right*left_one) % mod;
                // a x x a b, (i, n-1]
                ll t = pre_mul_suf - pre[x]*suf[x];
                ll s = pre_mul_suf_suf - pre[x]*suf[x]*suf[x];
                ll extra = pre[x]*(t*(n-i-1-suf[x])%mod - s%mod + mod) % mod;
                ans = (ans - extra % mod + mod) % mod;
            }
            left_sum = (left_sum + pre[x]) % mod;
            pre_mul_suf = (pre_mul_suf + suf[x]) % mod;
            pre_pre_mul_suf = (pre_pre_mul_suf + (2*pre[x]+1)*suf[x]%mod) % mod;
            pre_mul_suf_suf = (pre_mul_suf_suf + suf[x]*suf[x]) % mod;
            pre[x]++;
        }
        return ans;
    }
};