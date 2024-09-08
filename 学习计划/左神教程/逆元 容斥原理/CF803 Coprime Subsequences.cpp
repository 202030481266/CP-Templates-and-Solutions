// https://codeforces.com/problemset/problem/803/F

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

int cnt[maxn], dp[maxn];
int p[maxn];

void solve() {
    int n, tmp, mx = -1;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        cnt[tmp]++;
        if (tmp > mx) mx = tmp;
    }
    p[0] = 1;
    for (int i = 1; i <= n; ++i) {
        p[i] = p[i-1] * 2 % MOD;
    }
    for (int i = mx; i >= 1; --i) {
        // 动态规划 + 容斥原理
        int res = 0;
        for (int j = i; j <= mx; j += i) res += cnt[j];
        dp[i] = (p[res] - 1 + MOD) % MOD;
        for (int j = 2 * i; j <= mx; j += i) {
            dp[i] = (dp[i] - dp[j] + MOD) % MOD;
        }
    }
    cout << dp[1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
}