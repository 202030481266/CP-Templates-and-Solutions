// Problem: D. Nearest Excluded Points
// Contest: Codeforces - Educational Codeforces Round 124 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1651/D
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int n;
ll a[MAXN], b[MAXN];
ll ansX[MAXN], ansY[MAXN];
int vis[MAXN];

static constexpr int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
void solve() {
    cin >> n;
    unordered_map<ll, int> mp;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i];
        mp[(a[i] << 18) + b[i]] = i;
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        for (int k = 0; k < 4; ++k) {
            ll nx = a[i] + dirs[k][0], ny = b[i] + dirs[k][1];
            if (!mp.contains((nx << 18) + ny)) {
                ansX[i] = nx;
                ansY[i] = ny;
                q.push(i);
                vis[i] = 1;
                break;
            }
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int k = 0; k < 4; ++k) {
            ll nx = a[u] + dirs[k][0], ny = b[u] + dirs[k][1];
            if (mp.contains((nx << 18) + ny)) {
                int v = mp[(nx << 18) + ny];
                if (!vis[v]) {
                    vis[v] = 1;
                    ansX[v] = ansX[u];
                    ansY[v] = ansY[u];
                    q.push(v);
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        // cout << ansX[i] << ' ' << ansY[i] << ' ' << abs(a[i] - ansX[i]) + abs(b[i] - ansY[i]) << endl;
        cout << ansX[i] << ' ' << ansY[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}