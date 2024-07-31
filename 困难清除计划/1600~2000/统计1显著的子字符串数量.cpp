#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        // x^2 + x <= n, x <= 200
        // 所有一个合法的字符串的0的数量不可能超过两百
        // 维护200个指针即可
        vector<int> p(210,0);
        vector<int> sum(n+1, 0);
        for (int i = 0; i < n; ++i) {
            sum[i+1] = sum[i] + (s[i] == '1');
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int zero = min(200, i - sum[i]);
            if (s[i-1] == '0') {
                // p指针需要更新
                for (int j = zero; j > 1; --j) p[j] = p[j-1];
                p[1] = i;
                p[0] = 0;
            }
            else {
                p[0] = i; // 更新0的位置
            }
            if (p[0] > 0) ans += p[0] - p[1]; // (p[1],p[0]]
            for (int j = 1; j <= zero; ++j) {
                if (p[j] == 0) break;
                // [p[j],i]
                // (p[j+1],p[j]]
                // 我们有多少个合法的数组
                int v = sum[i]-sum[p[j]];
                int k = max(0,j*j-v), have = max(0,p[j]-p[j+1]-1);
                ans += max(0,have-k+1);
            }
        }
        return ans;
    }
};