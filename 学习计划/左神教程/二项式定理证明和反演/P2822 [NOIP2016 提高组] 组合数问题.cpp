#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

int c[2010][2010], n, m;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t, k;
    cin >> t >> k;
    vector<vector<int>> q(t, vector<int>(2));
    for (auto& qs : q) {
        cin >> qs[0] >> qs[1];
        n = max(n, qs[0]);
        m = max(m, qs[1]);
    }

    for (int i = 0; i <= n; ++i) c[i][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            c[i][j] = (c[i-1][j-1] + c[i-1][j]) % k;
        }
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
        	if (j <= i)
            	c[i][j] = (c[i][j] > 0 ? 0 : 1);
            if (i-1 >= 0) c[i][j] += c[i-1][j];
            if (j-1 >= 0) c[i][j] += c[i][j-1];
            if (i-1 >= 0 && j-1 >= 0) c[i][j] -= c[i-1][j-1];
        }
    }

    for (auto& qs : q) {
    	if (qs[1] > qs[0]) qs[1] = qs[0];
        cout << c[qs[0]][qs[1]] << endl;
    }
    
    return 0;
}