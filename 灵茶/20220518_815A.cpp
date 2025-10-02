#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

void solve() {
    int n, m;
    cin >> n >> m;
    vector arr(n, vector<int>(m));
    int x = 0, y = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> arr[i][j];
            if (arr[x][y] > arr[i][j]) {
                x = i;
                y = j;
            }
        }
    }
    vector<int> row(n), col(m);
    row[x] = arr[x][y];
    col[y] = 0;
    for (int i = 0; i < n; ++i) {
        if (i != x) {
            row[i] = arr[i][y] - col[y];
        }
    }
    for (int i = 0; i < m; ++i) {
        if (i != y) {
            col[i] = arr[x][i] - row[x];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (arr[i][j] != row[i] + col[j]) {
                cout << -1 << '\n';
                return;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        while (row[i]--) {
            cout << "row " << i + 1 << '\n';
        }
    }
    for (int i = 0; i < m; ++i) {
        while (col[i]--) {
            cout << "col " << i + 1 << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    return 0;
}