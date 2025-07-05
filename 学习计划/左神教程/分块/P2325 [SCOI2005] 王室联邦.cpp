#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

// 本质上就是树上的分块，dfs + 栈

vector<int> g[1001];
stack<int> s;
int n, b, belong[1001], cap[1001], tot = 0;

void dfs(int u, int fa) {
    int sz = s.size();
    for (int& v : g[u]) {
        if (v != fa) {
            dfs(v, u);
            if ((int)s.size() - sz >= b) {
                cap[++tot] = u;
                while (s.size() > sz) {
                    belong[s.top()] = tot;
                    s.pop();
                }
            }
        }
    }
    s.push(u);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> b;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    if (tot == 0) {
        cap[++tot] = 1;
    }
    while (!s.empty()) {
        belong[s.top()] = tot;
        s.pop();
    }
    cout << tot << '\n';
    for (int i = 1; i <= n; ++i) cout << belong[i] << ' ';
    cout << endl;
    for (int i = 1; i <= tot; ++i) cout << cap[i] << ' ';
    cout << endl;
}