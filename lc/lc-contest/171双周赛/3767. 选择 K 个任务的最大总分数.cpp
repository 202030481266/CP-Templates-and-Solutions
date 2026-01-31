#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;


class Solution {
public:
    long long maxPoints(vector<int>& a, vector<int>& b, int k) {
        int n = a.size();
        vector<int> arr;
        vector<int> use(n);
        for (int i = 0; i < n; ++i) {
            if (b[i] > a[i]) arr.push_back(i);
        }
        ranges::sort(arr, [&](int i, int j){ return b[i] - a[i] > b[j] - a[j]; });
        ll ans = 0;
        for (int i = 0; i < min(n - k, (int)arr.size()); ++i) {
            use[arr[i]] = 1;
            ans += b[arr[i]];
        }
        for (int i = 0; i < n; ++i) {
            if (!use[i]) ans += a[i];
        }
        return ans;
    }
};