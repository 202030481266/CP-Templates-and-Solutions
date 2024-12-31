#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 3e5 + 7;
int n, m, rs[maxn], ls[maxn], fa[maxn], dis[maxn], f[maxn], siz[maxn]; 
ll val[maxn], add[maxn], addAll;
multiset<ll> s;

// siz, add只有堆顶元素才有意义

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

// 全量更新
void pushdown(int x, int rt) {
    val[x] += add[rt];
    if (ls[x]) pushdown(ls[x], rt);
    if (rs[x]) pushdown(rs[x], rt);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (val[x] < val[y]) swap(x, y); // 大根堆
    rs[x] = merge(rs[x], y);
    f[rs[x]] = x;
    if (dis[ls[x]] < dis[rs[x]]) swap(ls[x], rs[x]);
    dis[x] = dis[rs[x]] + 1;
    fa[ls[x]] = fa[rs[x]] = x;
    return x; 
}

int remove(int x) {
    int rt = find(x);
    fa[ls[x]] = ls[x];
    fa[rs[x]] = rs[x];
    int cur = merge(ls[x], rs[x]);
    ls[x] = rs[x] = dis[x] = 0;
    fa[x] = cur;
    int father = f[x];
    f[cur] = father;
    if (x != rt) {
        // 需要往上面持续调整
        fa[cur] = rt;
        if (ls[father] == x) ls[father] = cur;
        else rs[father] = cur;
        for (int d = dis[cur]; d + 1 < dis[father]; father = f[father], ++d) {
            dis[father] = d + 1;
            if (dis[ls[father]] < dis[rs[father]]) swap(ls[father], rs[father]);
        }
    }
    return fa[cur];
}

void U(int x, int y) {
    // 找到堆顶
    int fx = find(x), fy = find(y);
    if (fx == fy) return;
    // 删除堆顶元素
    s.erase(s.find(val[fx] + add[fx]));
    s.erase(s.find(val[fy] + add[fy]));
    // 启发式合并
    if (siz[fx] < siz[fy]) swap(fx, fy);
    add[fy] = add[fy] - add[fx];
    pushdown(fy, fy);
    // 合并
    int rt = merge(fx, fy);
    // 更新堆顶元素的属性
    siz[rt] = siz[fx] + siz[fy];
    add[rt] = add[fx];
    s.insert(val[rt] + add[rt]);
}

void A1(int x, int v) {
    int rt = find(x);
    // 删除堆顶元素（因为这里可能会涉及到删除堆的顶部）
    s.erase(s.find(val[rt] + add[rt]));
    int y = remove(x);
    siz[y] = siz[rt] - 1;
    add[y] = add[rt];
    s.insert(val[y] + add[y]);
    // 设置x为新的堆
    fa[x] = x;
    siz[x] = 1;
    val[x] = val[x] + add[rt] + v; // 单点更新
    add[x] = 0;
    s.insert(val[x]);
    U(y, x);
}

void A2(int x, int v) {
    int fx = find(x);
    s.erase(s.find(val[fx] + add[fx]));
    add[fx] += v;
    s.insert(val[fx] + add[fx]);
}

void A3(int v) {
    addAll += v;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    dis[0] = -1;
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
        siz[i] = 1;
        cin >> val[i];
        s.insert(val[i]);
    }
    cin >> m;
    string op;
    int x, v;
    for (int i = 1; i <= m; ++i) {
        cin >> op;
        if (op == "A1") {
            cin >> x >> v;
            A1(x, v);
        }
        else if (op == "A2") {
            cin >> x >> v;
            A2(x, v);
        }
        else if (op == "A3") {
            cin >> v;
            A3(v);
        }
        else if (op == "U") {
            cin >> x >> v;
            U(x, v);
        }
        else if (op == "F1") {
            cin >> x;
            cout << val[x] + add[find(x)] + addAll << '\n';
        }
        else if (op == "F2") {
            cin >> x;
            int fx = find(x);
            cout << val[fx] + add[fx] + addAll << '\n';
        }
        else {
            cout << *s.rbegin() + addAll << '\n';
        }
    }
}

