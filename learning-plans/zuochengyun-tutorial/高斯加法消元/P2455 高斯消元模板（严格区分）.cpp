// https://www.luogu.com.cn/problem/P2455

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

double mat[100][100];
const double eps = 1e-7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            cin >> mat[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        int mx = i;
        for (int j = 0; j < n; ++j) {
            if (j < i && mat[j][j] >= eps) continue;
            if (fabs(mat[j][i]) > fabs(mat[mx][i])) mx = j;
        }
        if (mx != i)
        	swap(mat[mx], mat[i]);
        if (fabs(mat[i][i]) < eps) continue; // can not eliminate
        double rate = mat[i][i];
        for (int j = i; j <= n; ++j) {
            mat[i][j] /= rate;
        }
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            rate = mat[j][i];
            for (int k = i; k <= n; ++k) 
                mat[j][k] -= rate * mat[i][k];
        }
    }
    int sign = 0;
    for (int i = 0; i < n; ++i) {
        if (mat[i][i] < eps) { // 1 or 0
            sign++;
            if (fabs(mat[i][n]) >= eps) { // need fabs
                cout << -1 << endl;
                return 0;
            }
        }
    }
    if (!sign) {
        for (int i = 1; i <= n; ++i) {
            cout << "x" << i << "=";
            cout << setprecision(2) << fixed <<mat[i-1][n] << endl;
        }
    }
    else cout << 0 << endl;
    return 0;
}