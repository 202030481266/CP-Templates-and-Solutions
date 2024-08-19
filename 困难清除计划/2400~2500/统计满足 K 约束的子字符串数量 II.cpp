#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 统计变量，最左边区间，没有难度

class Solution {
public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int n = s.size(), m = queries.size();
        vector<int> left(n, -1);
        vector<int> cnt(2, 0);
        int l = 0;
        for (int i = 0; i < n; ++i) {
            ++cnt[s[i]-'0'];
            while (cnt[0] - (s[l]=='0' ? 1 : 0) > k && cnt[1] - (s[l]=='1'?1:0) > k) {
                cnt[s[l++]-'0']--;
            }
            if (cnt[0] > k && cnt[1] > k) left[i] = l; // [0, left[i]]
        }
        vector<ll> sum(n+1);
        for (int i = 2; i <= n; ++i) {
            sum[i] = sum[i-1];
            if (left[i-1] >= 0) sum[i] += left[i-1];
        }
        vector<ll> ans;
        for (auto q : queries) {
            int st = q[0], ed = q[1], len = ed-st+1;
            if (left[ed] < st) ans.push_back(1ll*len*(len+1)/2);
            else {
                int l = st, r = ed; // (l,r)
                while (l+1 < r) {
                    int mid = (l+r)>>1;
                    if (left[mid] >= st) r = mid;
                    else l = mid;
                }
                // [r,ed]
                ll res = sum[ed+1]-sum[r]-1ll*(st-1)*(ed-r+1);
                ans.push_back(1ll*len*(len+1)/2 - res);
            }
        }
        return ans;
    }
};