// 背包dp + 二项式反演

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

const int maxn = 2010;
const int mod = 1e9 + 9;
int n, k;
ll C[maxn][maxn], dp[maxn][maxn], fac[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    
    if ((n+k) & 1) {
    	cout << 0 << endl;
    	return 0;
    }
    k = (n+k)/2;
    for (int i = 0; i <= n; ++i) C[i][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
        }
    }
    
    vector<ll> candy(n), tablet(n);
    for (int i = 0; i < n; ++i) cin >> candy[i];
    for (int i = 0; i < n; ++i) cin >> tablet[i];
    sort(candy.begin(), candy.end());
    sort(tablet.begin(), tablet.end());

    vector<int> arr(n); 
    int p = 0;
    for (int i = 0; i < n; ++i) {
        while (p < n && tablet[p] < candy[i]) ++p;
        arr[i] = p;
    }

    dp[0][0] = 1; // [0, p[0])
    dp[0][1] = arr[0];
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= i+1; ++j) {
            dp[i][j] = dp[i-1][j];
            if (j > 0) dp[i][j] = (dp[i][j] + dp[i-1][j-1] * (arr[i] - j + 1) % mod) % mod;
        }
    }

    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i % mod;

    vector<ll> g(n+1);
    for (int i = 0; i <= n; ++i) {
        g[i] = dp[n-1][i] * fac[n-i] % mod;
    }

    ll ans = 0;
    for (int i = k; i <= n; ++i) {
        if ((i - k) & 1) {
            ans = (ans - g[i] * C[i][k] % mod + mod) % mod;
        }
        else {
            ans = (ans + g[i] * C[i][k] % mod) % mod;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}