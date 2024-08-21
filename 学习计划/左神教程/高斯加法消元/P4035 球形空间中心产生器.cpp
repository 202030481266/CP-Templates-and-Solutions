// https://www.luogu.com.cn/problem/P4035

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


double mat[20][20];
const double eps = 1e-7;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i <= n; ++i) {
        // n + 1 points determine
        for (int j = 0; j < n; ++j) 
            cin >> mat[i][j];
    }
    for (int i = 0; i < n; ++i) {
        double s1 = 0, s2 = 0;
        for (int j = 0; j < n; ++j) {
            s1 += mat[i][j] * mat[i][j];
            s2 += mat[i+1][j] * mat[i+1][j];
            mat[i][j] = 2 * (mat[i+1][j] - mat[i][j]);
        }
        mat[i][n] = s2 - s1;
    }
    for (int i = 0; i < n; ++i) {
        int mx = i;
        for (int j = 0; j < n; ++j) {
            if (j < i && mat[j][j] >= eps) continue; // 1 or 0
            if (fabs(mat[mx][i]) < fabs(mat[j][i])) mx = j;
        }
        if (mx != i) swap(mat[mx], mat[i]);
        if (fabs(mat[mx][i]) < eps) continue;
        double rate = mat[i][i];
        for (int j = i; j <= n; ++j) mat[i][j] /= rate;
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            double rate = mat[j][i];
            for (int k = i; k <= n; ++k) mat[j][k] -= mat[i][k] * rate;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << setprecision(3) << fixed << mat[i][n] << (i == n - 1 ? "\n" : " ");
    }
    return 0;
}