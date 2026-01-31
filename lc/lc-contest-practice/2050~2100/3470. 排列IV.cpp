#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

ll dp[12][12][2];
int flag = 0;

class Solution {
public:
    vector<int> permute(int n, long long k) {
        // 最多解决的n的规模就是22，也就是说最多11个偶数和11个奇数
        // 分治 + dp
        if (!flag) {
            flag = 1;
            dp[1][0][0] = dp[0][1][1] = 1;
            for (int i = 1; i <= 11; ++i) {
                for (int j = 1; j <= 11; ++j) {
                    dp[i][j][0] = i * dp[i-1][j][1];
                    dp[i][j][1] = j * dp[i][j-1][0];
                }
            }
        }
        int odd = n-n/2, even = n/2;
        if (n <= 22) {
            if (dp[even][odd][0] + dp[even][odd][1] < k) return {};
        }
        vector<int> ans;
        int st = 1, m = n;
        while (odd + even > 22) {
            ans.push_back(st);
            if (st&1) odd--;
            else even--;
            m--;
            st++;
        }
        vector<int> use(n+1, 0);
        int pre = (ans.empty() ? -1 : ans.back()&1);
        for (int i = m; i >= 1; --i) {
            for (int j = st; j <= n; ++j) {
                int tmp = j&1;
                if (!use[j] && (pre == -1 || pre != tmp)) {
                    ll cnt = 0;
                    if (tmp == 0) {
                        cnt = dp[even-1][odd][1];
                    }
                    else {
                        cnt = dp[even][odd-1][0];
                    }
                    if (cnt < k) {
                        k -= cnt;
                    }
                    else {
                        use[j] = 1;
                        pre = j&1;
                        if (tmp) odd--;
                        else even--;
                        ans.push_back(j);
                        break;
                    }
                }
            }
        }
        for (int j = st; j <= n; ++j) {
            if (!use[j]) {
                ans.push_back(j);
            }
        }
        return ans;
    }
};