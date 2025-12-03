#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MX = 100;

class Matrix {
public:
    vector<vector<long long>> a;
    int n, m;
    
    Matrix(int _n, int _m) : n(_n), m(_m) {
        a.assign(n, vector<long long>(m, 0));
    }
    
    Matrix mul(const Matrix& b) const {
        Matrix c(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                if (a[i][k] == 0) continue;
                for (int j = 0; j < b.m; j++) {
                    c.a[i][j] = (c.a[i][j] + a[i][k] * b.a[k][j]) % MOD;
                }
            }
        }
        return c;
    }
    
    Matrix powMul(int exp, Matrix f1) const {
        Matrix res = f1;
        Matrix base = *this;
        while (exp > 0) {
            if (exp % 2 == 1) {
                res = base.mul(res);
            }
            base = base.mul(base);
            exp /= 2;
        }
        return res;
    }
};

void solve() {
    int n, x;
    cin >> n >> x;
    
    vector<int> cnt(MX + 1, 0);
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        cnt[v]++;
    }
    
    Matrix m(MX + 1, MX + 1);
    
    // m[0] = append(cnt[1:], 1)
    for (int j = 0; j < MX; j++) {
        m.a[0][j] = cnt[j + 1];
    }
    m.a[0][MX] = 1;
    
    // for j := 1; j < mx; j++ { m[j][j-1] = 1 }
    for (int j = 1; j < MX; j++) {
        m.a[j][j - 1] = 1;
    }
    
    // m[mx][mx] = 1
    m.a[MX][MX] = 1;
    
    Matrix f0(MX + 1, 1);
    f0.a[0][0] = 1;
    f0.a[MX][0] = 1;
    
    Matrix fn = m.powMul(x, f0);
    cout << fn.a[0][0] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}