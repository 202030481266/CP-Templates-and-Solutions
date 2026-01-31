// 其实本质上还是利用了笛卡尔树的区间划分的性质，而这种划分恰好反应了一种子结构

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;
const int maxn = 507;
const int N = 1e6 + 7;

int n, k, st[maxn], a[maxn], ls[maxn], rs[maxn], b[maxn];
ll dp[maxn][maxn], sum[maxn]; // n * k
vector<int> arr;

// 逆元组合数
long long fac[N], ifac[N];
long long quick_power(long long a, long long b, int p) { 
    long long ans = 1 % p;
    for(; b; b >>= 1) {
        if(b & 1) ans = ans * a % p;
        a = a * a % p;
    }
    return ans;
}
long long inv(long long x, int p = mod) {
	return quick_power(x, p - 2, p) % mod;
}
long long binomial(int x, int y) {
	return fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}

ll cal(ll n, ll m, ll k) {
    if (n < k || m < k) return 0;
    return binomial(n, k) * binomial(m, k) % mod * fac[k] % mod;
}
void dfs(int u, int l, int r, int h) {
    // [l, u) [b[u], r], [u, b[u])
    if (u==0) return;
    dfs(ls[u], l, u-1, a[u]);
    dfs(rs[u], b[u], r, a[u]);
    memset(sum, 0, sizeof(sum));
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; i+j <= k; ++j) {
            sum[i+j] = (sum[i+j] + dp[ls[u]][i] * dp[rs[u]][j] % mod) % mod;
        }
    }
    // i, sum[0] * C
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j <= i; ++j) {
            dp[u][i] = (dp[u][i] + sum[j] * cal(r-l+1-j, a[u]-h, i-j) % mod) % mod;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; // use 1-index avoid 0
        if (a[i] > mx) mx = a[i];
    }

    // duplicate
    int l = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i] != a[l]) {
            arr.push_back(l);
            b[l] = i; // [l, i)
            l = i;
        }
    }
    arr.push_back(l);
    b[l] = n+1;

    // 笛卡尔树
    int top = 0; 
    for (int i : arr) {
        int p = top;
        while (p > 0 && a[st[p-1]] > a[i]) p--;
        if (p > 0) rs[st[p-1]] = i;
        if (p < top) ls[i] = st[p];
        st[p++] = i;
        top = p;
    }

    // dfs
    init(max(mx, n));
    dp[0][0] = 1;
    dfs(st[0], 1, n, 0);
    cout << dp[st[0]][k] << endl;
}