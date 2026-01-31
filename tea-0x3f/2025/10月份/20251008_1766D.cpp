#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 1000005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

// 巧妙的点在于只需要枚举其中的质因数, (x + k) % f == 0 等价于 (x + k) % s == 0，其中 s 是 f 的一个质因子
// 而且这个肯定是最优的

int primes[MAXN], tot = 0;
int lp[MAXN * 10];

void init() {
    lp[1] = 1;
    for (int i = 2; i <= 10000000; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes[tot++] = i;
        }
        for (int j = 0; j < tot && primes[j] <= lp[i] && 1ll * i * primes[j] <= 1ll * 10000000; ++j) {
            lp[i * primes[j]] = primes[j];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, x, y;
    cin >> t;
    init();
    while (t--) {
        cin >> x >> y;
        if (y == x + 1) {
            cout << -1 << '\n';
            continue;
        }
        int g = gcd(x, y);
        if (g > 1) {
            cout << 0 << '\n';
            continue;
        }
        int m = y - x, ans = INF;
        while (m > 1) {
            ans = min(ans, lp[m] - x % lp[m]);
            m /= lp[m];
        }
        cout << ans << '\n';
    }
}