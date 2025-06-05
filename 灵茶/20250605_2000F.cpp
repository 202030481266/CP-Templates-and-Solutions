// https://codeforces.com/problemset/problem/2000/F
#include <bits/stdc++.h>
using namespace std;

static constexpr int maxn = 1001;
static constexpr int maxk = 101;
int n, k;
int dp[maxn][maxk]; 

int cal(int a, int h, int w, int mid) {
    int x, up = min(a, w);
    if (1 <= mid && mid <= up) {
        x = mid;
    }
    else if (mid < 1) x = 1;
    else x = up;
    return a * w + x * x + (h - w - a) * x;
}

int f(int a, int h, int w) {
	if (h > w) swap(h, w);
    int x; // 1 <= x <= w
    if ((a + w - h) % 2 == 0) {
        return cal(a, h, w, (a + w - h) / 2);
    }
    int mid1 = (a + w - h) / 2, mid2 = mid1 + 1;
    return min(cal(a, h, w, mid1), cal(a, h, w, mid2));
}

void cf2000F() {
    cin >> n >> k;
    memset(dp, 0x3f, sizeof(dp));
    // f(a) = min(x * h + (a - x) * (w - x))
    // f(a) = min(x * h + a * w - x * w - a * x + x * x) 
    // f(a) = min(a * w + x * x + (h - w - a) * x)
    // x = -(h-w-a)/2
    // dp[i][j] = min(dp[i-1][j], dp[i-1][j-x] + cost(i, x))
    dp[0][0] = 0;
    for (int i = 1, h, w; i <= n; ++i) {
        cin >> w >> h;
        for (int a = 0; a <= h + w; ++a) {
            int cost = f(a, h, w);
            for (int j = a; j <= k; ++j) {
                dp[i][j] = min(dp[i][j], min(dp[i-1][j], dp[i-1][j-a] + cost));
            }
        }
    }
    cout << (dp[n][k] == 0x3f3f3f3f ? -1 : dp[n][k]) << '\n';
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) cf2000F();
}
