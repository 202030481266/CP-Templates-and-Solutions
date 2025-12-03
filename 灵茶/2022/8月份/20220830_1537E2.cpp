#include <bits/stdc++.h>
using namespace std;

static constexpr int MAXN = 500005;

int n, k;
char s[MAXN];

void solve() {
    cin >> n >> k;
    cin >> s;
    int ed = 0, p = 0;
    for (int i = 1; i < min(n, k); ++i) {
        if (s[i] == s[p]) {
            p = (p + 1) % (ed + 1);
        }
        else if (s[i] > s[p]) {
            break;
        }
        else {
            ed = i;
            p = 0;
        }
    }
    for (int i = 0, j = 0; j < k; ++j, i = (i + 1) % (ed + 1)) cout << s[i];
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
}
