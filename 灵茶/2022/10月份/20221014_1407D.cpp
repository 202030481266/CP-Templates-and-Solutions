// Problem: D. Discrete Centrifugal Jumps
// Contest: Codeforces - Codeforces Round 669 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1407/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
static constexpr int MAXN = 300005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

void solve() {
    int n;
    cin >> n;
    vi arr(n);
    for (int& v : arr) cin >> v;
    stack<int> st;
    vi rg(n, n), rl(n, n);
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            rg[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] >= arr[i]) {
            rl[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    queue<int> q;
    vii vis(n, vi(2));
    vi dis(n, INF);
    dis[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == n - 1) {
            cout << dis[u] << '\n';
            return;
        }
        if (arr[u + 1] == arr[u]) {
            if (dis[u + 1] > dis[u] + 1) {
                dis[u + 1] = dis[u] + 1;
                q.push(u + 1);
            }
        }
        if (arr[u + 1] > arr[u]) {
            if (!vis[u + 1][0]) {
                int v = u + 1, last = u;
                while (v < rl[u]) {
                    vis[v][0] = 1;
                    if (arr[v] != arr[last] && dis[v] > dis[u] + 1) {
                        dis[v] = dis[u] + 1;
                        q.push(v);
                    }
                    last = v;
                    v = rl[v];
                }
                if (v < n) {
                    if (dis[v] > dis[u] + 1) {
                        dis[v] = dis[u] + 1;
                        q.push(v);
                    }
                } 
            }
        }
        if (arr[u + 1] < arr[u]) {
            if (!vis[u + 1][1]) {
                int v = u + 1, last = u;
                while (v < rg[u]) {
                    vis[v][1] = 1;
                    if (arr[v] != arr[last] && dis[v] > dis[u] + 1) {
                        dis[v] = dis[u] + 1;
                        q.push(v);
                    }
                    last = v;
                    v = rg[v];
                }
                if (v < n) {
                    if (dis[v] > dis[u] + 1) {
                        dis[v] = dis[u] + 1;
                        q.push(v);
                    }
                }
            }
        }
    }
    cout << dis[n - 1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}