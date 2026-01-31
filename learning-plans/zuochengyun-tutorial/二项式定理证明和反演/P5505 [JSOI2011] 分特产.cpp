#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

const int maxn = 2010;
const int mod = 1e9 + 7;
ll C[maxn][maxn];
int n, m;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    C[0][0] = 1;
    vector<int> arr(m);
    for (int &v : arr) cin >> v;
    for (int i = 1; i <= 2000; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0) C[i][0] = 1;
            else C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
        }
    }
    vector<ll> g(n+1, 0);
    for (int i = 0; i < n; ++i) {
        g[i] = C[n][i];
        for (int j = 0; j < m; ++j)
            g[i] = (g[i] * C[n-i+arr[j]-1][n-i-1]) % mod;
    }
    ll ans = 0;
    for (int i = 0; i <= n; ++i) {
        if (i & 1) {
            ans = (ans - g[i] + mod) % mod;
        }
        else {
            ans = (ans + g[i]) % mod;
        }
    }
    cout << ans << endl;
    return 0;
}