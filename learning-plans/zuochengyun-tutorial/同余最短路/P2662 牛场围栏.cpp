#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

int n, m;
int edge[3010][3010];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    vector<int> a(n);

    for (int& v : a) cin >> v;
    sort(a.begin(), a.end());

    vector<int> b;
    int last = 0;
    for (int v : a) {
        if (v-m <= 1) {
            cout << -1 << endl;
            return 0;
        }
        int l = v-m;
        if (l > last) last = l;
        for (int i = last; i <= v; ++i) {
            b.push_back(i);
        }
        last = v+1;
    }
    vector<int> g[b[0]];    
    for (int v : b) {
        for (int j = 0; j < b[0]; ++j) {
            int nxt = (j + v) % b[0];
            if (!edge[j][nxt]) {
                edge[j][nxt] = v;
                g[j].push_back(nxt);
            }
        }
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    vector<int> dis(b[0], inf);
    for (int v : b) {
        int id = v % b[0];
        if (dis[id] == inf) {
	        dis[id] = v;
	        q.emplace(dis[id], id);
	    }
    }
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (d != dis[u]) continue;
        for (int v : g[u]) {
            if (dis[v] > dis[u] + edge[u][v]) {
                dis[v] = dis[u] + edge[u][v];
                q.emplace(dis[v], v);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < b[0]; ++i)
        if (dis[i] > ans) ans = dis[i];

    if (ans == inf) cout << -1 << endl;
    else cout << ans - b[0] << endl;

    return 0;
}