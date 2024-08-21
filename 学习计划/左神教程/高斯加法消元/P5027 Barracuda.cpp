// https://www.luogu.com.cn/problem/P5027

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

double mat[110][110], a[110][110];
const double eps = 1e-7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, id;
    cin >> n;
    for (int i = 0; i <= n; ++i) {
        cin >> m; 
        for (int j = 0; j < m; ++j) {
            cin >> id;
            mat[i][id] = 1;
        }
        cin >> mat[i][n+1]; // 1~n n+1
    }
    int ans = 0, mn_res = 0;
    for (int err = 0; err <= n; ++err) {
        // [0, err), (err, n)
        int row = 1;
        for (int i = 0; i < err; ++i) {
            for (int j = 1; j <= n+1; ++j)
                a[row][j] = mat[i][j];
            ++row;
        }
        for (int i = err+1; i <= n; ++i) {
            for (int j = 1; j <= n+1; ++j)
                a[row][j] = mat[i][j];
            ++row;
        }
        int flag = 1;
        for (int i = 1; i <= n; ++i) {
            int mx = i;
            for (int j = i+1; j <= n; ++j) {
                if (fabs(a[j][i]) > fabs(a[mx][i])) mx = j;
            }
            if (mx != i) swap(a[mx], a[i]);
            if (fabs(a[i][i]) < eps) {
                flag = 0; // can not eliminate
                break;
            }
            double rate = a[i][i];
            for (int j = i; j <= n+1; ++j) a[i][j] /= rate;
            for (int j = 1; j <= n; ++j) {
            	if (j == i) continue;
                rate = a[j][i];
                for (int k = i; k <= n+1; ++k)
                    a[j][k] -= rate * a[i][k];
            }
        }
        if (!flag) continue;
        double mx = 0;
        int cnt = 0, mn = 0;
        for (int i = 1; i <= n; ++i) {
            if (a[i][n+1] < eps || fabs(a[i][n+1] - ceil(a[i][n+1])) >= eps) {
                flag = 0;
                break;
            }
            if (a[i][n+1] > mx) mx = a[i][n+1], cnt = 1, mn = i;
            else if (fabs(a[i][n+1] - mx) < eps) ++cnt;
        }
        if (flag && cnt == 1) {
            ++ans;
            mn_res = mn;
        }
    }
    if (ans == 1) cout << mn_res << endl;
    else cout << "illegal" << endl;
    return 0;
}