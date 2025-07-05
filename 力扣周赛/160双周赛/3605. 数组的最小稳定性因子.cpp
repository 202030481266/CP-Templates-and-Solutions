#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 100005;

int st[maxn][17]; // gcd 具有幂等性

void init(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) st[i][0] = arr[i];
    for (int i = 1; i < 17; ++i) {
        for (int j = 0; j + (1 << i) - 1 < n; ++j) {
            st[j][i] = gcd(st[j][i-1], st[j + (1 << (i-1))][i-1]);
        }
    }
}

int query(int l, int r) {
    if (l > r) return 0;
    int k = log(r - l + 1) / log(2);
    return gcd(st[l][k], st[r - (1 << k) + 1][k]);
}

class Solution {
public:
    int minStable(vector<int>& nums, int maxC) {
        int n = nums.size();
        init(nums);
        
        auto check = [&](int val) -> bool {
            int p = 0, g = 0, use = 0;
            for (int i = 0; i < n; ++i) {
                g = gcd(g, nums[i]);
                while (g == 1) {
                    g = query(++p, i);
                }
                if (i - p + 1 > val) {
                    ++use;
                    if (use > maxC) return false;
                    p = i + 1;
                    g = 0;
                }
            }
            return true;
        };
        
        int l = -1, r = n + 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) r = mid;
            else l = mid;
        }
        return r;
    }
};