#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [&](const auto& a, const auto& b){
            return a[1] == b[1] ? a[0] < b[0] : a[1] < b[1]; 
        });
        int p = 0, n = points.size();
        vector<int> cnt;
        while (p < n) {
            int i = p + 1;
            while (i < n && points[i][1] == points[p][1]) ++i;
            cnt.push_back(i - p);
            p = i;
        }
        if (cnt.size() == 1) return 0;
        ll sum = 0, ans = 0;
        for (ll v : cnt) {
            ll s = (v - 1) * v / 2;
            ans = (ans + s * sum % mod) % mod;
            sum = (sum + s) % mod;
        }
        return ans;
    }
};
