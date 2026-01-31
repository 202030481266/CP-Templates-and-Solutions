#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;


void solve() {
    int n;
    cin >> n;
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    vii g(n + 1);
    vi a, b;
    for (int i = 1; i <= n; ++i) {
        if (i + arr[i] <= n) g[i + arr[i]].push_back(i);
        if (i - arr[i] >= 1) g[i - arr[i]].push_back(i);
        if (arr[i] & 1) b.push_back(i);
        else a.push_back(i);
    }
    vi odd(n + 1, -1), even(n + 1, -1);
    auto bfs = [&](const vi& source, vi& dis) -> void {
        fill(dis.begin(), dis.end(), INF);
        queue<int> q;
        for (int v : source) {
            dis[v] = 0;
            q.push(v);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (dis[v] > dis[u] + 1) {
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            }
        }
    };
    bfs(a, odd);
    bfs(b, even);
    for (int i = 1; i <= n; ++i) {
       if (arr[i] & 1) cout << (odd[i] == INF ? -1 : odd[i]) << ' ';
       else cout << (even[i] == INF ? -1 : even[i]) << ' ';
    }
}    


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
