// Problem: L. Odd Federalization
// Contest: Codeforces - 2018-2019 ICPC, NEERC, Southern Subregional Contest (Online Mirror, ACM-ICPC Rules, Teams Preferred)
// URL: https://codeforces.com/problemset/problem/1070/L
// Memory Limit: 256 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <vector>
#include <bitset>
#include <numeric>

using namespace std;


const int MAXN = 2005;
bitset<MAXN> mat[MAXN];

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    bool all_even = true;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] % 2 != 0) {
            all_even = false;
        }
    }

    if (all_even) {
        cout << 1 << "\n";
        for (int i = 1; i <= n; ++i) {
            cout << 1 << (i == n ? "" : " ");
        }
        cout << "\n";
        return;
    }


    for (int i = 0; i < n; ++i) {
        mat[i].reset();
    }


    for (int i = 1; i <= n; ++i) {
        int row = i - 1; // 矩阵行从 0 开始
        for (int v : adj[i]) {
            mat[row][v] = 1; // 邻居节点的系数为 1
        }
        
        if (deg[i] % 2 != 0) {
            mat[row][i] = 1;       // di 是奇数时：xor(Xv) ^ Xi = 1
            mat[row][n + 1] = 1;
        } else {
            mat[row][i] = 0;       // di 是偶数时：xor(Xv) = 0
            mat[row][n + 1] = 0;
        }
    }

    vector<int> pivot_row(n + 1, -1);
    int r = 0;
    for (int c = 1; c <= n; ++c) {
        int sel = -1;
        // 寻找当前列主元
        for (int i = r; i < n; ++i) {
            if (mat[i][c]) {
                sel = i;
                break;
            }
        }
        if (sel == -1) continue; // 自由变量，跳过
        
        swap(mat[r], mat[sel]);
        pivot_row[c] = r;

        for (int i = 0; i < n; ++i) {
            if (i != r && mat[i][c]) {
                mat[i] ^= mat[r];
            }
        }
        r++;
    }

    cout << 2 << "\n";
    for (int i = 1; i <= n; ++i) {
        int val = 0;
        if (pivot_row[i] != -1) {
            val = mat[pivot_row[i]][n + 1]; // 获取常数项的值 (0 或 1)
        }
        cout << (val == 0 ? 1 : 2) << (i == n ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}