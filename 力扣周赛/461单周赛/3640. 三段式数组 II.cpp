#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;
static constexpr ll llinf = 0x3f3f3f3f3f3f3f3f;

static constexpr int maxn = 100005;

ll a[maxn], b[maxn], c[maxn];
ll arr[maxn];

class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        for (int i = 1; i <= n; ++i) {
            a[i] = b[i] = c[i] = -llinf;
            arr[i] = nums[i-1];
        }
        for (int i = 2; i <= n; ++i) {
            if (arr[i] > arr[i-1]) {
                if (a[i-1] != -llinf) a[i] = max(a[i], a[i-1] + arr[i]);
                a[i] = max(a[i], arr[i-1] + arr[i]);
            }
        }
        for (int i = 2; i <= n; ++i) {
            if (arr[i] < arr[i-1]) {
                if (b[i-1] != -llinf) b[i] = max(b[i], b[i-1] + arr[i]);
                if (a[i-1] != -llinf) b[i] = max(b[i], a[i-1] + arr[i]);
            }
        }
        ll ans = -llinf;
        for (int i = 2; i <= n; ++i) {
            if (arr[i-1] < arr[i]) {
                if (c[i-1] != -llinf) c[i] = max(c[i], c[i-1] + arr[i]);
                if (b[i-1] != -llinf) c[i] = max(c[i], b[i-1] + arr[i]);
            }
            ans = max(ans, c[i]);
        }
        return ans;
    }
};