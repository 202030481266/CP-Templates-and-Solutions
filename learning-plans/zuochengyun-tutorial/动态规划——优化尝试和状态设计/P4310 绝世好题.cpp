#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

const int maxn = 100010;
int a[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    // 往往来说，子序列需要枚举前缀信息或者以某一个数字为结尾
    // 但是 a[i] 与之后大于零的数字很多
    // 所以这里采用了 "基" 的思想来设计状态，无论如何，最多可以拆成32个基
    // dp[j] 代表前缀中最后的一个数字 j 位为1 的最长长度
    vector<int> dp(32);
    for (int i = 0; i < n; ++i) {
    	int mx = 0;
        for (int j = 0; j < 32; ++j) {
            if ((a[i] >> j) & 1) {
                mx = max(mx, dp[j]);
            }
        }
        for (int j = 0; j < 32; ++j) {
        	if ((a[i] >> j) & 1) {
        		dp[j] = mx + 1;
        	}
        }
    }
    
    cout << *max_element(dp.begin(), dp.end()) << endl;
    return 0;
}