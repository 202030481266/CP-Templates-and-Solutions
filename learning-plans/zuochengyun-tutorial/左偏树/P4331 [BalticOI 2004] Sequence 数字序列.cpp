// L1 loss, PAVA algorithm
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>; 

const int maxn = 1e6 + 7;

int n, p;
int a[maxn], ls[maxn], rs[maxn], dis[maxn], fa[maxn], val[maxn];
int s[maxn], siz[maxn], b[maxn];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (val[x] < val[y]) swap(x, y);
    rs[x] = merge(rs[x], y);
    if (dis[ls[x]] < dis[rs[x]]) swap(ls[x], rs[x]);
    dis[x] = dis[rs[x]] + 1;
    fa[ls[x]] = fa[rs[x]] = x;
    return x;
}

int pop(int x) {
    fa[ls[x]] = ls[x];
    fa[rs[x]] = rs[x];
    fa[x] = merge(ls[x], rs[x]);
    ls[x] = rs[x] = dis[x] = 0;
    return fa[x]; // 返回新的堆顶
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] -= i;
        fa[i] = i;
        val[i] = a[i];
        siz[i] = 1;
    }

    // [0, p) s
    for (int i = 1; i <= n; ++i) {
        int cur = i, mid = val[i];
        while (p && mid < val[find(s[p-1])]) {
            int rt = find(s[p-1]), f = find(cur);
            fa[rt] = fa[f] = merge(rt, f);
            siz[s[p-1]] += siz[cur];
            // [cur, i]
            cur = s[p-1];
            int up = (i-cur+2)/2;
            rt = find(rt);
            while (siz[cur] > up) {
                rt = pop(rt);
                --siz[cur];
            }
            mid = val[rt];
            --p;
        }
        s[p++] = cur;
    }
    ll ans = 0;
    int k = n;
    while (p) {
        int cur = s[--p];
        int rt = find(cur);
        for (int i = k; i >= cur; --i) {
            b[i] = val[rt] + i;
            ans += abs(a[i] - val[rt]);
        }
        k = cur-1;
    }
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i) {
        if (i == n) cout << b[i] << '\n';
        else cout << b[i] << ' ';
    }
    return 0;
}


