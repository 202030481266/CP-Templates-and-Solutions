// Problem: P9474 [yLOI2022] 长安幻世绘
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9474
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// 在值域上做滑窗，维护当前的值域在数组上分布的能够取到的最大值，因为问题存在单调性，对于每一个新加入的值，必然存在一个最大的最小值


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int n, m, arr[MAXN], b[MAXN];

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r

int sum[MAXN << 2], l_mx[MAXN << 2], r_mx[MAXN << 2];

void pushup(int rt, int l, int r) {
    sum[rt] = sum[ls] + sum[rs];
    sum[rt] -= (r_mx[ls] + 1) / 2 + (l_mx[rs] + 1) / 2;
    sum[rt] += (r_mx[ls] + l_mx[rs] + 1) / 2;
    if (l_mx[ls] == mid - l + 1) l_mx[rt] = l_mx[ls] + l_mx[rs];
    else l_mx[rt] = l_mx[ls];
    if (r_mx[rs] == r - mid) r_mx[rt] = r_mx[rs] + r_mx[ls];
    else r_mx[rt] = r_mx[rs];
}

void update(int rt, int l, int r, int p, int val) {
    if (l == r) {
        l_mx[rt] = r_mx[rt] = val;
        sum[rt]= (val + 1) / 2;
        return;
    }
    if (p <= mid) update(lson, p, val);
    else update(rson, p, val);
    pushup(rt, l, r);
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) b[i] = i;
    sort(b + 1, b + 1 + n, [&](int i, int j){ return arr[i] < arr[j]; });
    int l = 1, ans = INF;
    for (int i = 1; i <= n; ++i) {
        update(1, 1, n, b[i], 1);
        while (sum[1] >= m) {
            ans = min(ans, arr[b[i]] - arr[b[l]]);
            update(1, 1, n, b[l++], 0);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}