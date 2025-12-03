#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, m;
    cin >> n >> m;
    vector g(n, vector<char>(m));
    vector<int> row(n), col(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> g[i][j];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == '*') ++row[i];
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[j][i] == '*') ++col[i];
        }
    }
    int mx_row = *max_element(row.begin(), row.end());
    int mx_col = *max_element(col.begin(), col.end());
    if (mx_row == n && mx_col == m) {
        cout << 0 << '\n';
        return;
    }
    int flag = 0;
    for (int i = 0; i < n && !flag; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == '.' && row[i] == mx_row && col[j] == mx_col) {
                flag = 1;
                break;
            }
        }
    }
    if (flag) cout << (n + m - mx_row - mx_col - 1) << '\n';
    else cout << (n + m - mx_row - mx_col) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}