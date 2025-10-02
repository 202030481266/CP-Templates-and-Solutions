#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 1003;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)
#define vii vector<vector<int>>
#define vi vector<int>

ll n;
int m;

vii mul(const vii& A, const vii& x) {
    // A.size() * x[0].size()
    vii res(A.size(), vi(x[0].size()));
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < x[0].size(); ++j) {
            for (int k = 0; k < A[0].size(); ++k) {
                // A[0].size() == x.size()
                res[i][j] = (res[i][j] + INT(1ll * A[i][k] * x[k][j] % MOD)) % MOD;
            }
        }
    }
    return res;
}

vii quick_pow(vii A, ll b) {
    vii res(A.size(), vi(A.size()));
    for (int i = 0; i < A.size(); ++i) res[i][i] = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = mul(res, A);
        A = mul(A, A);
    }
    return res;
}

void solve() {
    cin >> n >> m;
    vii A(m, vi(m));
    A[0][0] = A[0][m - 1] = 1;
    for (int i = 1; i < m; ++i) A[i][i - 1] = 1;
    vii B(m, vi(1));
    B[0][0] = 1;
    vii A_n = quick_pow(A, n);
    vii ans = mul(A_n, B);
    cout << ans[0][0] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}