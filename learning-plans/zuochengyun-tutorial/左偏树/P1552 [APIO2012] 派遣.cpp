#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
int n, m;

// 左偏树
int ls[maxn], rs[maxn], dis[maxn], val[maxn];
// dsu
int fa[maxn];
int lead[maxn], b[maxn];
long long sum[maxn], siz[maxn];

// 可并堆合并
int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (val[x] < val[y]) swap(x, y); // 大根堆
    rs[x] = merge(rs[x], y);
    if (dis[ls[x]] < dis[rs[x]]) {
        swap(ls[x], rs[x]);
    }
    dis[x] = dis[rs[x]] + 1;
    fa[ls[x]] = fa[rs[x]] = x;
    return x;
}

// 删除堆顶元素
int pop(int x) {
    fa[ls[x]] = ls[x];
    fa[rs[x]] = rs[x];
    fa[x] = merge(ls[x], rs[x]);
    ls[x] = rs[x] = dis[x] = 0;
    return fa[x]; // 返回新的堆顶
}

// dsu 查找
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        cin >> b[i] >> val[i] >> lead[i];
        sum[i] = val[i];
        siz[i] = 1;
    }
    long long ans = 0;
    for (int i = n; i >= 1; --i) {
        int rt = find(i);
        while (sum[i] > m && siz[i]) {
            sum[i] -= val[rt];
            siz[i]--;
            rt = pop(rt);
        }
        if (siz[i]) {
            ans = max(ans, lead[i] * siz[i]);
            if (i > 1) {
                int f = find(b[i]);
                fa[f] = fa[rt] = merge(f, rt);
                sum[b[i]] += sum[i];
                siz[b[i]] += siz[i];
            }
        }
    }
    cout << ans << '\n';
    return 0;
}