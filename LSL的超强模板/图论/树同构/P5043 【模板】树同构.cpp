// https://www.luogu.com.cn/problem/P5043

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
const ull mask = mt19937_64(time(nullptr))();

ull xorShift(ull x) {
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= mask;
    return x;
}

const int maxn = 6000;
int head[maxn], to[maxn], w[maxn], nxt[maxn], eCount = 0;
int d1[maxn], d2[maxn], up[maxn], minRadius = 1e9;
int cX, cY, roots[maxn], len[maxn], st[maxn];
ull treeValue[maxn];

void AddEdge(int u, int v, int weight) {
    to[eCount] = v;
    w[eCount] = weight;
    nxt[eCount] = head[u];
    head[u] = eCount++;
}

void dfs_d(int u, int fa) {
    for (int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
            dfs_d(v, u);
            if (d1[v] + w[i] > d1[u]) {
                d2[u] = d1[u];
                d1[u] = d1[v] + w[i];
            }
            else if (d1[v] + w[i] > d2[u]) {
                d2[u] = d1[v] + w[i];
            }
        }
    }
}

void dfs_u(int u, int fa) {
    for (int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
            up[v] = up[u] + w[i];
            if (d1[v] + w[i] != d1[u]) {
                up[v] = max(up[v], d1[u] + w[i]);
            }
            else {
                up[v] = max(up[v], d2[u] + w[i]);
            }
            dfs_u(v, u);
        }
    }
}

void center(int idx) {
    dfs_d(roots[idx], 0);
    dfs_u(roots[idx], 0);
    cX = 0;
    cY = 0;
    minRadius = 1e9;
    for (int i = 1 + st[idx]; i <= len[idx] + st[idx]; ++i) {
        int mx = max(d1[i], up[i]);
        if (mx < minRadius) {
            minRadius = mx;
            cX = i;
            cY = 0;
        }
        else if (mx == minRadius) {
            cY = i;
        }
    }
}

ull dfs_hash(int u, int fa) {
    ull hashValue = 1;
    for (int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
            hashValue += xorShift(dfs_hash(v, u));
        }
    }
    return hashValue;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int M, offset = 0;
    cin >> M;
    memset(head, -1, sizeof(head));
    for (int i = 0, n; i < M; ++i) {
        cin >> n;
        len[i] = n;
        st[i] = offset;
        for (int j = 1, fa; j <= n; ++j) {
            cin >> fa;
            if (!fa) roots[i] = offset + j;
            else {
            	AddEdge(offset + fa, offset + j, 1);
            	AddEdge(offset + j, offset + fa, 1);
            }
        }
        offset += n;
    }
    ull xValue, yValue;
    for (int i = 0; i < M; ++i) {
        center(i);
        if (cX && cY) {
            xValue = dfs_hash(cX, 0);
            yValue = dfs_hash(cY, 0);
            treeValue[i] = min(xValue, yValue);
        }
        else {
            treeValue[i] = dfs_hash(cX, 0);
        }
        for (int j = 0; j <= i; ++j) {
            if (treeValue[j] == treeValue[i]) {
                cout << j + 1 << '\n';
                break;
            }
        }
    }
    return 0;
}