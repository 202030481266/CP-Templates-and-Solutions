#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

const int D = 201; // 猜测的
int n, s, t, m;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // 离散化技巧，非常经典和有启发性的题目    
    cin >> n >> s >> t >> m;
    vector<int> where(m+2);
    vector<int> pos(m+1);
    for (int i = 1; i <= m; ++i) cin >>pos[i];
    sort(pos.begin(), pos.end());
    int ans = inf;
    if (s == t) {
        // s==t的时候无法有效压缩，因为这个时候路径是确定的，需要精确计算
        // 这个时候使用D来压缩距离将会导致距离变得不精确
        // 更加重要的是，这个时候，dp[i] 对于未来的位置的影响是离散的，而不是连续的!（从贡献角度思考D的作用非常有帮助）
    	ans = 0;
    	for (int i = 1; i <= m; ++i) {
    		if (pos[i] % s == 0) ++ans;
    	}
    	cout << ans << endl;
    	return 0;
    }
    
    where[0] = 0; // 起点
    for (int i = 1; i <= m; ++i) {
        where[i] = where[i-1] + min(pos[i]-pos[i-1], D);
    }
    where[m+1] = where[m] + D;
    n = where[m+1];
    
    vector<int> dp(n+1, inf);
    // 由于 [s,t] 相当小，所以可以不用使用单调队列优化
    int p = 1;
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = s; j <= t && j <= i; ++j) {
            dp[i] = min(dp[i], dp[i-j]);
        }
        if (p <= m && i == where[p]) dp[i]++, p++;
    }

    for (int i = where[m]; i <= n; ++i) ans = min(ans, dp[i]);
    cout << ans << endl;

    return 0;
}