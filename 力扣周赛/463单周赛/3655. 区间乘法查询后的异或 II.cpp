#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

static constexpr int maxn = 100003;
static constexpr int maxb = 318;

int arr[maxn][maxb];

ll quick_pow(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

ll inv(ll x) {
    return quick_pow(x, mod - 2);
}

class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), m = (int)sqrt(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= m; ++j) arr[i][j] = 1;
        }
        for (auto& q : queries) {
            int l = q[0], r = q[1], k = q[2], v = q[3];
            int change = (r - l) / k + 1;
            if (change <= m || k > m) {
                for (int i = l; i <= r; i += k) {
                    nums[i] = 1ll * nums[i] * v % mod;
                }
            }
            else {
                arr[l][k] = 1ll * arr[l][k] * v % mod;
                int inv_k = inv(v), right = change * k + l;
                if (right < n) arr[right][k] = 1ll * arr[right][k] * inv_k % mod;
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (arr[i][j] == 1) continue;
                if (i + j < n) arr[i + j][j] = 1ll * arr[i + j][j] * arr[i][j] % mod;
                nums[i] = 1ll * nums[i] * arr[i][j] % mod;
            }
            ans ^= nums[i];
        }
        return ans;
    }
};