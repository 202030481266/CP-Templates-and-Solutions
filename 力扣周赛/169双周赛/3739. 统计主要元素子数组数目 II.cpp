#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

constexpr int maxn = 100005;
int n, m;
ll sum[maxn], fenwick[maxn], arr[maxn], b[maxn], tot;

inline int lowbit(int i) {
    return i & -i;
}

void update(int p, int val) {
    while (p <= m) {
        fenwick[p] += val;
        p += lowbit(p);
    }
}

int query(int p) {
    int res = 0;
    while (p) {
        res += fenwick[p];
        p -= lowbit(p);
    }
    return res;
}

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        n = nums.size();
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + (nums[i] == target);
        }
        tot = 0;
        b[++tot] = 0;
        for (int i = 1; i <= n; ++i) b[++tot] = 2 * sum[i] - i;
        sort(b + 1, b + 1 + tot);
        m = unique(b + 1, b + 1 + tot) - b - 1;
        for (int i = 0; i <= m; ++i) fenwick[i] = 0;
        ll ans = 0;
        for (int i = 0; i <= n; ++i) {
            arr[i] = lower_bound(b + 1, b + 1 + m, 2 * sum[i] - i) - b;
            ans += query(arr[i] - 1);
            update(arr[i], 1);
        }
        return ans;
    }
};