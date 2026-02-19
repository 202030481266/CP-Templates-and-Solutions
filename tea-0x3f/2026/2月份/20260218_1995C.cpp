// Problem: C. Squaring
// Contest: Codeforces - Codeforces Round 961 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1995/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long total_ans = 0;
    long long last_ops = 0; // 上一个数额外平方的次数

    for (int i = 1; i < n; i++) {
        // 1 的特殊处理：1 永远无法通过平方变大
        if (a[i] == 1) {
            if (a[i - 1] > 1) {
                cout << -1 << "\n";
                return;
            }
            last_ops = 0; // a[i-1] 也是 1 的情况
        } else if (a[i - 1] == 1) {
            last_ops = 0; // 前一个是 1，当前大于 1，不需要操作
        } else {
            // 计算 a[i] 和 a[i-1] 之间的“基础平方差”
            long long cnt = 0;
            long long temp_prev = a[i - 1];
            long long temp_curr = a[i];

            if (temp_curr < temp_prev) {
                // a[i] 小，需要追赶
                while (temp_curr < temp_prev) {
                    temp_curr *= temp_curr;
                    cnt++;
                }
                last_ops += cnt;
            } else {
                // a[i] 大，可以抵消前一个数的部分平方次数
                while (true) {
                    // 防止平方溢出，且 a[i] 本身最大也就 10^6
                    // 如果 temp_prev 平方后依然 <= temp_curr，说明能抵消一次
                    if (temp_prev * temp_prev > temp_curr) break;
                    temp_prev *= temp_prev;
                    cnt++;
                }
                last_ops = max(0LL, last_ops - cnt);
            }
        }
        total_ans += last_ops;
    }

    cout << total_ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}