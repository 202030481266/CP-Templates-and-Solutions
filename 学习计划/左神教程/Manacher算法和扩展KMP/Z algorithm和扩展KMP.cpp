// 讲解视频：https://www.bilibili.com/video/BV1YH4y1h7MU
// 模板题目 https://www.luogu.com.cn/problem/P5410
// Z[i] 表示字符串s[i...n-1]和s[0....n-1]的最长公共前缀
// e[i] 表示字符串a[i...n-1]和b[0....m-1]的最长公共前缀
// 原理和Manacher算法类似，考虑一个加速区间，提供了一个字符的等价转换，然后再进行动态规划

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 2e7 + 10;
char a[maxn], b[maxn];
int n, m, z[maxn], e[maxn];

void Z() {
    z[0] = m;
    for (int i = 1, c = 1, r = 1; i < m; ++i) {
        int len = (i < r ? min(r - i, z[i - c]) : 0);
        while (i + len < m && b[i + len] == b[len]) ++len;
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
}

void ex_kmp() {
    Z();
    for (int i = 0, c = 0, r = 0; i < n; ++i) {
        int len = (i < r ? min(z[i - c], r - i) : 0);
        while (i + len < n && len < m && a[i + len] == b[len]) ++len;
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        e[i] = len;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a >> b;
    n = strlen(a);
    m = strlen(b);
    ex_kmp();
    ll ans1 = 0, ans2 = 0;
    for (int i = 0; i < m; ++i) ans1 ^= 1ll * (i+1) * (z[i]+1);
    for (int i = 0; i < n; ++i) ans2 ^= 1ll * (i+1) * (e[i]+1);
    cout << ans1 << endl << ans2 << endl;
    return 0;
}
