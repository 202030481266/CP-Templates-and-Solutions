#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;

class Solution {
public:
    int maxCount(vector<int>& banned, int N, long long maxSum) {
        int n = banned.size();
        sort(banned.begin(), banned.end());
        banned.erase(unique(banned.begin(), banned.end()), banned.end()); // 去重
        vector<ll> sum(n+1);
        for (int i = 0; i < n; i++) {
            sum[i+1] = sum[i] + banned[i];
        }
        auto check = [&](int v) -> bool { // [1,v]
            int p = upper_bound(banned.begin(), banned.end(), v) - banned.begin();
            ll s = (p == 0 ? 1ll * (1+v) * v / 2 : 1ll * (1+v) * v / 2 - sum[p]); // [0,p)的前缀和[0,p-1] -> sum[p]
            return s <= maxSum;
        };
        int l = 1, r = N+1, ans = 0;
        while (l+1 < r) {
            int mid = (l +r) >> 1;
            if (check(mid)) l = mid;
            else r = mid;
        }
        int p = upper_bound(banned.begin(), banned.end(), l) - banned.begin();
        return l - p;
    }
};