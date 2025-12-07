#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int fenwick[MAXN], N;

inline int lowbit(int i) {
    return i & -i;
}

void update(int p, int val) {
    while (p <= N) {
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
    long long totalScore(int hp, vector<int>& damage, vector<int>& requirement) {
        int n = damage.size();
        // score[j]的本质上就是右边 hp - (sum[i] - sum[j-1]) >= r[i] 的满足要求的和
        // hp + sum[j-1] >= r[i] + sum[i]
        vector<ll> sum(n + 1);
        for (int i = 0; i < n; ++i) sum[i + 1] = sum[i] + damage[i];
        vector<ll> arr;
        for (int i = 1; i <= n; ++i) {
            arr.push_back(hp + sum[i - 1]);
            arr.push_back(requirement[i - 1] + sum[i]);
        }
        ranges::sort(arr);
        arr.erase(unique(arr.begin(), arr.end()), arr.end());
        N = arr.size();
        memset(fenwick, 0, (N + 1) * sizeof(int));
        ll ans = 0;
        for (int i = n; i >= 1; --i) {
            int v = lower_bound(arr.begin(), arr.end(), requirement[i - 1] + sum[i]) - arr.begin() + 1;
            int x = lower_bound(arr.begin(), arr.end(), hp + sum[i - 1]) - arr.begin() + 1;
            update(v, 1);
            ans += query(x);
        }
        return ans;
    }
};
