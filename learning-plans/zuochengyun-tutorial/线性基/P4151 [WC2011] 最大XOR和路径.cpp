#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 50010;
int n, m;
vector<pair<int, ll>> g[maxn];
ll s[maxn]; // 从起点到节点u的异或和
bool vis[maxn];
ll basis[64];

void insert_basis(ll x) {
    for (int i = 63; i >= 0; --i) {
        if ((x >> i) & 1) {
            if (!basis[i]) {
                basis[i] = x;
                return;
            }
            x ^= basis[i];
        }
    }
}

void dfs(int u) {
    vis[u] = true;
    for (auto [v, w] : g[u]) {
        if (!vis[v]) {
            s[v] = s[u] ^ w;
            dfs(v);
        } else {
            ll cycle_xor = s[u] ^ w ^ s[v];
            if (cycle_xor) {
                insert_basis(cycle_xor);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    int u, v;
    ll w;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        if (u != v) // 处理自环
            g[v].push_back({u, w});
    }
    dfs(1);
    ll ans = s[n];
    for (int i = 63; i >= 0; --i) {
        if ((ans ^ basis[i]) > ans) {
            ans ^= basis[i];
        }
    }
    cout << ans << '\n';
    return 0;
}


/*
BFS的原始思路(实现复杂并且空间消耗很大):
异或线性基具有压缩的性质，对于一个非常庞大的整数集，其中的线性基的数量非常小。
因此，我们可以对于每一个节点使用异或线性基来表示所有可能的到达该点路径的结果集。
但是其中的难点在于寻找和更新。首先，我们可以初始化节点1为空，然后进队，寻找相邻的点进行更新。b[u] U {w} -> s[u] ^ w
如果周围的点更新了，就进队。这样的话，所有节点最多进队64次。
不过这里有一个小的开销，就是检查周围的点，看起来耗时很高。
仔细分析一下，对于一个点最多检查 64 * k 次，而 sum(64 * k) = 2 * E * 64，这也是与边的总数直接挂钩。
*/
