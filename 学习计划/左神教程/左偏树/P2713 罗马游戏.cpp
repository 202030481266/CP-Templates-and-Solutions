// https://www.luogu.com.cn/problem/P3261

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int n, m;

// 左偏树
int ls[maxn], rs[maxn], dis[maxn], val[maxn];
// dsu
int fa[maxn];

// 可并堆合并
int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (val[x] > val[y] || (val[x] == val[y] && x > y)) {
        swap(x, y);
    }
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
    int l = ls[x], r = rs[x];
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
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
        fa[i] = i;
    }
    cin >> m;
    char op;
    int x, y;
    vector<bool> vis(n+1);
    while (m--) {
        cin >> op;
        if (op == 'M') {
            cin >> x >> y;
            if (vis[x] || vis[y]) continue;
            int fx = find(x), fy = find(y);
            if (fx == fy) continue;
            fa[fx] = fa[fy] = merge(fx, fy);
        }
        else {
            cin >> x;
            if (vis[x]) {
                cout << 0 << '\n';
                continue;
            }
            int fx = find(x);
            vis[fx] = true;
            cout << val[fx] << '\n';
            pop(fx);
        }
    }
    return 0;
}