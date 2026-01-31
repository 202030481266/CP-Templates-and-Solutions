#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
int n, m;

// 左偏树
int ls[maxn], rs[maxn], dis[maxn], val[maxn];
// dsu
int fa[maxn];

// 可并堆合并
int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (val[x] < val[y] || (val[x] == val[y] && x < y)) {
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
    while (cin >> n) {
    // Reset arrays for new test case
    memset(ls, 0, sizeof(ls));
    memset(rs, 0, sizeof(rs));
    memset(dis, 0, sizeof(dis));
    
    // Read initial values
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
        fa[i] = i;
    }
    
    cin >> m;
    while (m--) {
        int x, y;
        cin >> x >> y;
        int fx = find(x), fy = find(y);
        if (fx == fy) {
            cout << -1 << '\n';
        } 
        else {
            val[fx] /= 2;
            val[fy] /= 2;
            int nx = pop(fx), ny = pop(fy);
            // merge both
            int r1 = merge(fx, fy), r2 = merge(nx, ny);
            fa[fx] = fa[fy] = r1;
            fa[nx] = fa[ny] = r2;
            fa[r1] = fa[r2] = merge(r1, r2);
            cout << val[fa[r1]] << '\n';
        }
    }
}
    return 0;
}