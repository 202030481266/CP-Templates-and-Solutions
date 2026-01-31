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

static constexpr int mod = 1e9 + 7;

set<pii> mp;
vector<pii> steps;
int n, m;
int vis[100][100];

bool dfs(int x, int y) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (vis[i][j]) ++cnt;
        }
    }
    if (cnt == n * m) return true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!vis[i][j]) {
                int dx = i - x;
                int dy = j - y;
                if (!mp.contains({dx, dy})) {
                    vis[i][j] = 1;
                    mp.insert({dx, dy});
                    steps.emplace_back(i, j);
                    if (dfs(i, j)) return true;
                    steps.pop_back();
                    vis[i][j] = 0;
                    mp.erase({dx, dy});
                }
            }
        }
    }
    return false;
}
                    
void bruteforce() {
    cin >> n >> m;
    vis[0][0] = 1;
    steps.emplace_back(0, 0);
    bool res = dfs(0, 0);
    if (res) {
        cout << "Yes" << '\n';
        // for (auto [x, y] : steps) {
        //     cout << x << ' ' << y << '\n';
        // }
        vii arr(n, vi(m));
        for (int i = 0; i < n * m; ++i) {
            int x = steps[i].first, y = steps[i].second;
            arr[x][y] = i + 1;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) cout << arr[i][j] << '\t';
            cout << '\n';
        }
    }
    else cout << "No" << '\n';
}

bool check(const vector<pii>& steps) {
    set<pii> s;
    int n = steps.size();
    for (int i = 0; i < n - 1; ++i) {
        int dx = steps[i + 1].first - steps[i].first;
        int dy = steps[i + 1].second - steps[i].second;
        if (s.contains({dx, dy})) return false;
        s.insert({dx, dy});
    }
    return true;
}


void solve() {
    // 关于矩形的中心对称的方法
    int n, m;
    cin >> n >> m;
    vii vis(n, vi(m));
    vector<pii> steps;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (vis[i][j]) continue;
            steps.emplace_back(i, j);
            vis[i][j] = 1;
            if (n - 1 - i != i || m - 1 - j != j) {
                steps.emplace_back(n - 1 - i, m - 1 - j);
                vis[n - 1 - i][m - 1 - j] = 1;
            }
        }
    }
    // if (check(steps)) cout << "\033[32mAccepted\033[0m" << '\n';
    // else cout << "\033[31mWrong Answer\033[0m" << '\n';
    for (auto [x, y] : steps) {
        cout << x + 1 << ' ' << y + 1 << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // bruteforce();
    solve();
}
