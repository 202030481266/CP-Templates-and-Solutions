// https://www.luogu.com.cn/problem/P5795

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 3e5 + 7;
const int B = 30;
const int N = maxn * 35;
int n, m, root[maxn], tot, tree[N][2], cnt[N];
int a[maxn], b[maxn][2];

int insert(int x, int i) {
    int rt = ++tot;
    tree[rt][0] = tree[i][0];
    tree[rt][1] = tree[i][1];
    cnt[rt] = cnt[i] + 1;
    for (int j = B, b, pre = rt, cur; j >= 0; --j) {
        b = (x >> j) & 1;
        i = tree[i][b];
        cur = ++tot;
        tree[cur][0] = tree[i][0];
        tree[cur][1] = tree[i][1];
        cnt[cur] = cnt[i] + 1; 
        tree[pre][b] = cur;
        pre = cur;
    } 
    return rt;
}

int query(int xl, int xr, int yl, int yr, int k) {
    int res = 0;
    for (int i = xl; i <= xr; ++i) {
        b[i][0] = root[yl-1];
        b[i][1] = root[yr];
    }
    for (int i = B, bit, sum; i >= 0; --i) {
        sum = 0;
        for (int j = xl; j <= xr; ++j) {
            bit = (a[j] >> i) & 1;
            sum += cnt[tree[b[j][1]][bit ^ 1]] - cnt[tree[b[j][0]][bit ^ 1]];
        }
        if (sum >= k) {
            res |= 1 << i;
            for (int j = xl; j <= xr; ++j) {
                bit = (a[j] >> i) & 1;
                b[j][0] = tree[b[j][0]][bit ^ 1];
                b[j][1] = tree[b[j][1]][bit ^ 1];
            }
        }
        else {
            k -= sum;
            for (int j = xl; j <= xr; ++j) {
                bit = (a[j] >> i) & 1;
                b[j][0] = tree[b[j][0]][bit];
                b[j][1] = tree[b[j][1]][bit];
            }
        }
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, num; i <= m; ++i) {
        cin >> num;
        root[i] = insert(num, root[i-1]);
    }
    int q;
    cin >> q;
    for (int i = 1, u, d, l, r, k; i <= q; ++i) {
        cin >> u >> d >> l >> r >> k;
        cout << query(u, d, l, r, k) << '\n';
    }
}