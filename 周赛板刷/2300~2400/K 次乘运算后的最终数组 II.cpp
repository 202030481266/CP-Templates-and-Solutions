#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// math
// 推导原理不难，重点在于实现
ll quick_pow(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        if (multiplier == 1) return nums;
        int n = nums.size();
        // t2 = t1 - ceil(logm(ceil(a2/a1)))
        vector<ll> val{1}, cut(n);
        ll mx_val = *max_element(nums.begin(), nums.end());
        ll mn_val = *min_element(nums.begin(), nums.end());
        for (int i = 1; val.back() <= mx_val; ++i) {
            val.push_back(val.back() * multiplier);
        }
        ll sum = 0;
        for (int i = 0; i < n; ++i) {
            int div = nums[i] / mn_val;
            // find the maximum x that multipier ^ x <= div
            // can use binary search and use array preprocess
            int l = -1, r = val.size();
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (val[mid] > 1ll * div) r = mid; // (left, mid)
                else l = mid; // (mid, r)，already record the answer
            }
            cut[i] = l;
            sum += cut[i];
        }
        // sum(max(0,t-cut[i])) >= k
        auto check = [&](int t) -> ll {
            ll res = 0;
            for (ll &v : cut) res += (t - v <= 0 ? 0 : t - v);
            return res;
        };
        int l = 0, r = k+1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid) >= 1ll * k) r = mid; // (left, mid)
            else l = mid; // (mid, right)
        }
        int mn = (check(r) == k ? r : r-1); // base opertion times of the minimum number
        vector<int> ans(n), ids(n);
        iota(ids.begin(), ids.end(), 0);
        // need to understand cpp cmp function (how it works)
        sort(ids.begin(), ids.end(), [&](int i, int j){
            int ai = nums[i], bi = mn-cut[i] <= 0 ? 0 : mn - cut[i]; 
            int aj = nums[j], bj = mn-cut[j] <= 0 ? 0 : mn - cut[j];
            // ai * M ^ bi < aj * M ^ bj
            if (bi == bj) return ai < aj;
            else if (bi < bj) {
                // bi < bj
                // ai / aj < M ^ (bj - bi)
                int tmp = (ai-1)/aj + 1, l = -1, r = val.size();
                // find the first x that multipiler ^ x >= tmp
                while (l + 1 < r) {
                    int mid = (l + r) >> 1;
                    if (val[mid] >= 1ll * tmp) r = mid; // (left, mid)
                    else l = mid; // (mid, right)
                }
                // strict
                return (ai % aj == 0 && val[r] == ai/aj) ? (r == bj - bi ? i < j : r < bj - bi) : r <= bj - bi;
            }
            else {
                // bi > bj
                // M ^ (bi - bj) < aj / ai
                int tmp = aj/ai, l = -1, r = val.size();
                if (tmp < multiplier) return false; // M ^ (bi - bj) >= M
                // find the max x that multiplier ^ x <= tmp
                while (l + 1 < r) {
                    int mid = (l + r) >> 1;
                    if (val[mid] <= 1ll * tmp) l = mid; // (mid, right)
                    else r = mid; // (left, mid)
                } 
                // strict
                return (aj % ai == 0 && val[l] == aj/ai) ? (l == bi - bj ? i < j : l > bi - bj) : l >= bi - bj;
            }
        });

        //debug
        // for (int v : cut) cout << mn-v << ' '; cout << endl;
        // for (int v : ids) cout<< v << ' '; cout << endl;
        
        int p = k - check(mn);
        for (int i = 0; i < p; ++i) ans[ids[i]] = quick_pow(multiplier, max(0ll,mn+1-cut[ids[i]])) * nums[ids[i]] % mod;
        for (int i = p; i < n; ++i) ans[ids[i]] = quick_pow(multiplier, max(0ll,mn-cut[ids[i]])) * nums[ids[i]] % mod;
        return ans;
    }
};