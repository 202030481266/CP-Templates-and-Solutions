#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const int maxn = 107;
const int maxk = 2e5 + 7;
const int N = 1e6+7;

int n, k, cnt;
int ls[N], rs[N], dis[N], val[N], len[maxn], pre[N], pos[N], block[N];
vector<vector<int>> a;
priority_queue<int, vector<int>, decltype([](const int i, const int j){
    return pre[i] + val[i] > pre[j] + val[j];
})> pq;

int init(int id, int p) {
    // 最为重要的一句，哪怕是走到头了，依然要保留这个节点，因为这个左偏树还包含其他的决策节点
    // 后面的最优决策很有可能是基于这个版本的左偏树（也就是p==len[id]了的情况下继续做的决策）
    val[++cnt] = (p+1 < len[id] ? a[id][p+1] : inf) - a[id][p];
    ls[cnt] = rs[cnt] = dis[cnt] = 0;
    pos[cnt] = p;
    block[cnt] = id;
    return cnt;
}
int clone(int x) {
    val[++cnt] = val[x];
    ls[cnt] = ls[x];
    rs[cnt] = rs[x];
    dis[cnt] = dis[x];
    pos[cnt] = pos[x];
    block[cnt] = block[x];
    return cnt;
}
int merge(int x, int y) {
    if (!x || !y) return x + y;
    // 小根堆
    if (val[x] > val[y]) swap(x, y);
    int rt = clone(x);
    rs[rt] = merge(rs[rt], y); // merge(rs[rt], y)
    if (dis[ls[rt]] < dis[rs[rt]]) swap(ls[rt], rs[rt]);
    dis[rt] = dis[rs[rt]] + 1;
    return rt;
}
int pop(int x) {
    if (ls[x] == 0 && rs[x] == 0) return 0;
    if (!ls[x] || !rs[x]) return clone(ls[x] + rs[x]);
    return merge(ls[x], rs[x]);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); 
    cin >> n >> k;
    int mn = 0, h = 0; 
    dis[0] = -1;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> len[i];
        a[i].resize(len[i]);
        for (int j = 0; j < len[i]; ++j) cin >> a[i][j];
        sort(a[i].begin(), a[i].end());
        mn += a[i][0];
        if (len[i] > 1) {
            h = merge(h, init(i, 0));
        }
    }
    vector<int> ans(k);
    ans[0] = mn;
    pre[h] = mn;
    pq.push(h);
    for (int i = 1; i < k; ++i) {
        int rt = pq.top();
        pq.pop();
        ans[i] = pre[rt] + val[rt];
        h = pop(rt);
        if (h) {
            pre[h] = pre[rt];
            pq.push(h);
        }
        if (pos[rt]+1 < len[block[rt]]) {
            h = merge(h, init(block[rt], pos[rt]+1));
            pre[h] = ans[i];
            pq.push(h);
        }
    }
    for (int i = 0; i < k; ++i) {
        cout << ans[i] << " \n"[i==k-1];
    }
    return 0;
}