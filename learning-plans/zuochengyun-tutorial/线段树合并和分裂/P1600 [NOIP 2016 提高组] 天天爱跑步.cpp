// /usr/liushulin
// -*- coding:UTF-8 -*-
/*#########################################################################
# File Name: luogu_1600.cpp
# Author: xiaoshulin
# Created Time: 2021/11/24 11:11:07
#########################################################################*/
#include <bits/stdc++.h>
#define re register
using namespace std;
const int maxn = 300010, inf = 0x3f3f3f3f;
int n, m, w[maxn], dep[maxn], head[maxn], cnt, tot1, tot2;
int fa[maxn][30], lg[maxn], val[maxn], C[maxn], head1[maxn], head2[maxn];
struct edge
{
    int to, next;
} e[maxn << 1], e1[maxn << 1], e2[maxn << 1];
inline void add(int from, int to)
{
    e[++cnt].to = to;
    e[cnt].next = head[from];
    head[from] = cnt;
}
inline void add1(int from, int to)
{
    e1[++tot1].to = to;
    e1[tot1].next = head1[from];
    head1[from] = tot1;
}
inline void add2(int from, int to)
{
    e2[++tot2].to = to;
    e2[tot2].next = head2[from];
    head2[from] = tot2;
}
int b1[maxn << 1], b2[maxn << 1], js[maxn], dist[maxn], s[maxn], t[maxn], ans[maxn];
void dfs(int u, int father)
{
    fa[u][0] = father;
    dep[u] = dep[father] + 1;
    for (re int i = 1; i <= lg[dep[u]]; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (re int i = head[u]; i; i = e[i].next)
    {
        int to = e[i].to;
        if (to == father)
            continue;
        dfs(to, u);
    }
}
int lca(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    while (dep[x] > dep[y])
        x = fa[x][lg[dep[x] - dep[y]] - 1];
    if (x == y)
        return x;
    for (re int i = lg[dep[x]]; i >= 0; i--)
        if (fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
void cal(int x)
{
    int t1 = b1[w[x] + dep[x]], t2 = b2[w[x] - dep[x] + maxn];
    for (re int i = head[x]; i; i = e[i].next)
    {
        int to = e[i].to;
        if (to == fa[x][0])
            continue;
        cal(to);
    }
    b1[dep[x]] += js[x];
    for (re int i = head1[x]; i; i = e1[i].next)
    {
        int to = e1[i].to;
        b2[dist[to] - dep[t[to]] + maxn]++;
    }
    ans[x] += b1[w[x] + dep[x]] - t1 + b2[w[x] - dep[x] + maxn] - t2;
    for (re int i = head2[x]; i; i = e2[i].next)
    {
        int to = e2[i].to;
        b1[dep[s[to]]]--;
        b2[dist[to] - dep[t[to]] + maxn]--;
    }
}
int main()
{
    cin >> n >> m;
    for (re int i = 1; i <= n - 1; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    for (re int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    for (re int i = 1; i <= n + 1; i++)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    dep[1] = 1;
    dfs(1, 1);
    for (re int i = 1; i <= m; i++)
    {
        scanf("%d%d", &s[i], &t[i]);
        int anc = lca(s[i], t[i]);
        dist[i] = dep[s[i]] + dep[t[i]] - 2 * dep[anc];
        js[s[i]]++;
        add1(t[i], i);
        add2(anc, i);
        if (dep[anc] + w[anc] == dep[s[i]])
            ans[anc]--;
    }
    cal(1);
    for (re int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}