// 模板题目: https://www.luogu.com.cn/problem/P3805
// 讲解视频：https://www.bilibili.com/video/BV1YH4y1h7MU
// Manacher算法是经典的计算最长回文子串的算法（关键的技巧在于理解最大回文半径）

// 有两种写法，一种是基于扩展串的（统一了奇数和偶数长度），第二种是基于中心扩展的（奇数和偶数长度分开处理）
// 第二种是实现看LSL的最强模板目录，这里实现第一种

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


const int maxn = 22000002;
string s, ss;
int dp[maxn], n, mx = 0;
int manacher() {
    for (int i = 0, c = 0, r = 0; i < n; ++i) {
        int len = (i < r ? min(dp[2*c - i], r - i) : 1);
        while (i - len >= 0 && i + len < n && ss[i - len] == ss[i + len]) ++len;
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        dp[i] = len;
        mx = max(mx, dp[i]);
    }
    return mx-1;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    n = s.size();
    ss.assign(2*n + 1, '#');
    for (int i = 0; i < n; ++i) ss[2*i + 1] = s[i];
    n = 2*n + 1;
    cout << manacher() << endl;
    return 0;
}