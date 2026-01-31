#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ll = long long;

class Solution {
public:
    int maxCapacity(vector<int>& costs, vector<int>& capacity, int budget) {
        using pii = pair<int, int>;
        vector<pii> a;
        int n = costs.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (costs[i] < budget) ans = max(ans, capacity[i]);
            a.emplace_back(costs[i], capacity[i]);
        }
        ranges::sort(a);
        vi right(n);
        int r = n - 1, l = 0;
        while (l < r) {
            while (r > l && a[r].first + a[l].first >= budget) --r;
            if (r > l) {
                right[l] = r;
                ++l;
            }
        }
        if (l == 0) return ans;
        int p = l, mx = 0;
        for (int i = l - 1; i >= 0; --i) {
            while (p <= right[i]) {
                mx = max(mx, a[p].second);
                ++p;
            }
            ans = max(ans, mx + a[i].second);
            mx = max(mx, a[i].second);
        }
        return ans;        
    }
};
