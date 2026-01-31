#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

const int maxn = 60; 
int n, q;
ll v[maxn], w[maxn];
ll dp[100010];

// 非常困难的问题，首先需要按照性价比最高的物品进行一个同余分组，这样子就可以按照性价比最高的物品的一个基准来快速求解
// 这里的DP实际上是一个收益最大化的判断，比如 基准值是 10, 那么余5 + 16 = 21 实际上的收益就是相当于我们要按照基准值进行权衡, -2*w[10] + w[16]，然后得到了一个余1的状态
// 简单解释就是说，我们在最后计算的时候是直接使用性价比最高的基准值10来计算的，所以21本质上可以有2个10加上一个多余的1组成
// 这里相当于将状态分组的同时（减少规模），计算相对于性价比最高的物品的最大收益（同余最长路），非常巧妙

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> v[i] >> w[i];

    int mx = 0;
    // c[i] / v[i] > c[mx] / v[mx]
    // c[i] * v[mx] > c[mx] * v[i]
    for (int i = 1; i < n; ++i) {
        if (w[i] * v[mx] > w[mx] * v[i]) mx = i;
    }

    // 按照 v[mx] 同余分组
   	vector<ll> dp(100010, -llinf);
   	dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        ll g = gcd(v[mx], v[i]);
        for (int j = 0; j < g; ++j) {
            int cur = j;
            for (int k = 0; k < 2; k += (cur == j ? 1 : 0)) {
                int nxt = (cur + v[i]) % v[mx], t = (cur + v[i]) / v[mx];
                if (dp[nxt] < dp[cur] - t * w[mx] + w[i] && dp[cur] != -llinf) {
                    dp[nxt] = dp[cur] - t * w[mx] + w[i];
                }
                cur = nxt;
            }
        }
    }
    
    for (int i = 0; i < q; ++i) {
        ll tmp;
        cin >> tmp;
        ll r = tmp % v[mx], k = tmp / v[mx];
        if (dp[r] == -llinf) cout << -1 << endl;
        else cout << k * w[mx] + dp[r] << endl;
    }

    return 0;
}