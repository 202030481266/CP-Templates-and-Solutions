#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;

const int maxn = 1e5 + 10;
const int N = 1e5;
int c[4], n, d[4], m;
ll dp[maxn];

// 有限制条件的背包问题
// 并且有多次查询，每一次的查询的限制都不一样，所以简单的背包肯定是走不通的
// 2 * 4 = 16 种模式
// f(x1 <= a1 && x2 <= a2) = f(x1, x2) - (f(x1 > a1, x2) + f(x1, x2 > a2) - f(x1 > a1, x2 > a2))
// f(x1 > a1, x2 > a2, sum) = f(x1, x2, sum - x1 * (a1 + 1) - x2 * (a2 + 1)), 意思就是先拿掉其中的一些，然后后面就是完全背包
// 非常好的题目，其实本题最难的并不是容斥原理而是对于完全背包的本质洞察
// 完全背包可以解决具有下限无上限的问题，但是不能解决有上限而无下限的问题

void solve() {
    for (int i = 0; i < 4; ++i) cin >> c[i];
    cin >> n;
    dp[0] = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = c[i]; j <= N; ++j) dp[j] += dp[j-c[i]];
    }
    ll cnt = 0, sum = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) cin >> d[j];
        cin >> m;
        ans = 0;
        for (int S = 0; S < (1<<4); ++S) {
            cnt = 0, sum = 0;
            for (int k = 0; k < 4; ++k) {
                if ((S>>k) & 1) {
                    ++cnt;
                    sum += (d[k]+1) * c[k];
                }
            }
            if (m >= sum) {
                ans += ((cnt & 1) ? -dp[m-sum] : dp[m-sum]);
            }
        }
        cout << ans << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
}
