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

static constexpr int C[] = {0,0,1,2,5,16,65,326,1957,13700,109601,986410,9864101,108505112};

void test(int n) {
    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= min(i, n); j++) {
            if (j == 0 || j == i) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            }
        }
    }
    vl fac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i;
    ll tot = 0;
    for (int i = n - 2; i >= 0; --i) {
        tot += dp[n - 2][i] * fac[i];
    }
    cout << tot << ',';
}


void solve_no_shortest_path() { // this greedy solutions will get an answer nearly equal the actual one which is a NP-HARD problem
    // this is far more difficult than the shortest version
    int k;     
    cin >> k;
    vector<pii> ans;
    int N = 2;
    --k; // add 1-2
    for (int i = 13; i >= 3 && k; --i) {
        int x = k / (C[i] - 1);  // edge 1-2 contribute once globaly
        if (x > 0) {
            ans.emplace_back(i, x);
            k %= C[i] - 1;
            N += x * (i - 2);
        }
    }
    vii grid(N + 1, vi(N + 1, 0));
    int last = 3;
    grid[1][2] = grid[2][1] = 1;
    for (auto [block, cnt] : ans) {
        while (cnt--) {
            int l = last, r = last + block - 2;
            for (int i = l; i < r; ++i) {
                for (int j = l; j < r; ++j) {
                    if (i != j) grid[i][j] = 1;
                }
            }
            for (int i = l; i < r; ++i) {
                grid[1][i] = grid[i][1] = 1;
                grid[2][i] = grid[i][2] = 1;
            }
            last = r;
        }
    }
    cout << N << '\n';
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) cout << (grid[i][j] ? 'Y' : 'N');
        cout << '\n';
    }
}

void solve() {
    int k;
    cin >> k;
    // we can use the binary seperate it into some numbers
    // but with minimal n, we should use some trick to reuse our nodes
    int w = bit_width(1u * k);
    vii ans(200, vi(200, 0));
    int p = 3;
    vii layer(w + 1, vi(2));
    layer[0][0] = layer[0][1] = 1;
    layer[w][0] = layer[w][1] = 2;
    for (int t = 1; t <= w; ++t) {
        if (t < w) {
            layer[t][0] = p++;
            layer[t][1] = p++;
        }
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                int u = layer[t - 1][i];
                int v = layer[t][j];
                ans[u][v] = ans[v][u] = 1;
            }
        }
    }
    if (k > 1 << w - 1) {
        int pre = 1;
        for (int i = 1; i <= w - 1; ++i) {
            int cur = p++;
            ans[pre][cur] = ans[cur][pre] = 1;
            if (k >> w - 1 - i & 1) {
                for (int j = 0; j < 2; ++j) {
                    ans[cur][layer[i + 1][j]] = 1;
                    ans[layer[i + 1][j]][cur] = 1;
                }
            }
            pre = cur;
        }
    }
    cout << p - 1 << '\n';
    for (int i = 1; i < p; ++i) {
        for (int j = 1; j < p; ++j) {
            cout << (ans[i][j] ? 'Y' : 'N');
        }
        cout << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}

