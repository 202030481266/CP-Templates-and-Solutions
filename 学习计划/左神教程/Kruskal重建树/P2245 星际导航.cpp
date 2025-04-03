// https://www.luogu.com.cn/problem/P2245
// Kruskal重建树模板

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int INF = 0x7f7f7f7f;
const int maxn = 100010;
const int maxm = 300010;
struct edge1 {int u, v, w;} e1[maxm];
struct edge2 {int next, to, val;} e2[maxn << 1];
int n, m, cnt, f[maxn], head[maxn], depth[maxn], fa[maxn][30], w[maxn][30];

bool vis[maxn];
bool cmp(edge1 A, edge1 B) {return A.w < B.w;}
void add_edge(int a, int b, int c) {
    e2[++cnt].to = b;
    e2[cnt].next = head[a];
    e2[cnt].val = c;
    head[a] = cnt;
}
int find(int x) {
    if (x == f[x]) return x;
    else return f[x] = find(f[x]);
}
void kruskal() {
    sort(e1 + 1, e1 + m + 1, cmp);
    for (int i = 1; i <= n; i++) f[i] = i;
    for (int i = 1; i <= m; i++) {
        int c1 = find(e1[i].u);
        int c2 = find(e1[i].v);
        if (c1 == c2) continue;
        f[c2] = c1;
        add_edge(c1, c2, e1[i].w);
        add_edge(c2, c1, e1[i].w);
    }
}
void dfs(int node) {
    vis[node] = true;
    for (int i = head[node]; i; i = e2[i].next) {
        int son = e2[i].to;
        if (vis[son]) continue;
        fa[son][0] = node;
        depth[son] = depth[node] + 1;
        w[son][0] = e2[i].val;
        dfs(son);
    }
    return;
}
int lca(int x, int y)
{
    if (find(x) != find(y))
        return -1; //不连通，输出-1
    int ans = 0;
    if (depth[x] > depth[y])
        swap(x, y); //保证y节点更深
    //将y节点上提到于x节点相同深度
    for (int i = 20; i >= 0; i--)
        if (depth[fa[y][i]] >= depth[x])
        {
            ans = max(ans, w[y][i]); //更新最大载重（最小边权）
            y = fa[y][i];            //修改y位置
        }
    if (x == y)
        return ans; //如果位置已经相等，直接返回答案
    //寻找公共祖先
    for (int i = 20; i >= 0; i--)
        if (fa[x][i] != fa[y][i])
        {
            ans = max(ans, max(w[x][i], w[y][i])); 
            x = fa[x][i];
            y = fa[y][i]; //修改x,y位置
        }
    ans = max(ans, max(w[x][0], w[y][0]));
    //更新此时x,y到公共祖先最大载重，fa[x][0], fa[y][0]即为公共祖先
    return ans;
}
int main() {
    int x, y, z, q;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        e1[i].u = x;
        e1[i].v = y;
        e1[i].w = z;
    }
    kruskal();
    for (int i = 1; i <= n; i++) 
        if (!vis[i]) {
            depth[i] = 1;
            dfs(i);
            fa[i][0] = i;
            //w[i][0] = INF;
        }
    //LCA初始化
    for (int i = 1; i <= 20; i++)
        for (int j = 1; j <= n; j++)
        {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
            w[j][i] = max(w[j][i - 1], w[fa[j][i - 1]][i - 1]);
        }
    cin >> q;
    while (q--) {
        scanf("%d%d", &x, &y);
        int ans = lca(x, y);
        if(ans == -1) printf("impossible\n");
        else printf("%d\n", ans);
    }
    return 0;
}