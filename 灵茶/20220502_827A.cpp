#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int MAXM = 1000005;

#define INT(x) static_cast<int>(x)

int n, N, mx[MAXM];
string s[MAXN];
char ans[MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, k; i <= n; ++i) { // s[0] = ""
        cin >> s[i];
        cin >> k;
        for (int j = 0, x; j < k; ++j) {
            cin >> x;
            N = max(N, INT(s[i].size()) + x - 1); // [x, x + len - 1]
            if (s[i].size() > s[mx[x]].size()) {
                mx[x] = i;
            }
        }
    }
    int r = 1;
    for (int i = 1, m; i <= N; ++i) {
        if (!mx[i]) {
            if (i == r) {
                cout << 'a';
                ++r;
            }
        }
        else {
            m = INT(s[mx[i]].size());
            if (r >= i + m) continue;
            for (int j = r - i; j < m; ++j) cout << s[mx[i]][j];
            r = i + m;
        }
    }
}