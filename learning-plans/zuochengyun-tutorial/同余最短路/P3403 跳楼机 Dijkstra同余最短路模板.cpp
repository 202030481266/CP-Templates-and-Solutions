#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

const int maxn = 1e5 + 5;
int a[3]; 
ll dis[maxn];
ll h;
vector<int> g[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> h;
    for (int i = 0; i < 3; ++i) cin >> a[i];
    sort(a, a+3);

    // [0, h-1]
    int base = a[0];
    unordered_map<ll, int> edge;

    for (int i = 1; i < 3; ++i) {
        for (int j = 0; j < base; ++j) {
            int nxt = (j + a[i]) % base;
            if (nxt != j) {
                // j -> nxt
                if (!edge.count(1ll * j * maxn + nxt)) {
                    g[j].push_back(nxt);
                    edge[1ll * j * maxn + nxt] = a[i];
                }
            }
        }
    } 
    
    // dijkstra
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = 0;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (dis[u] != d) q.pop();
        for (int v : g[u]) {
            if (dis[v] > d + edge[1ll * u * maxn + v]) {
                dis[v] = d + edge[1ll * u * maxn + v];
                q.emplace(dis[v], v);
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < base; ++i) {
        if (dis[i] < h) {
            ans += (h-dis[i]-1)/base + 1;
        }
    }
    cout << ans << endl;
    return 0;
}