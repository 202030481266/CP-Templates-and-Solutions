// https://www.luogu.com.cn/problem/P3389

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

int n;
double a[110][110];
double eps = 1e-7;

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        int mx = i;
        for (int j = i + 1; j < n; ++j) {
            if (fabs(a[j][i]) > fabs(a[mx][i])) {
                mx = j;
            }
        }
        if (mx != i) swap(a[mx], a[i]);
        if (fabs(a[i][i]) < eps) {
            cout << "No Solution" << endl;
        	return 0;
        } 
        double rate = a[i][i]; 
        for (int j = i; j <= n; ++j) a[i][j] /= rate;
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                rate = a[j][i];
                for (int k = i; k <= n; ++k)
                    a[j][k] -= rate * a[i][k];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << setprecision(2) << fixed << a[i][n] << endl;
    }
    return 0;
}




