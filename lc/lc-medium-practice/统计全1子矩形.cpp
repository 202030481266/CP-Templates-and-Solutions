#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 22500
    int numSubmat(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        // 数学方法，枚举行然后就是单调栈，O(mn)
        vector<int> sum(m);
        vector<int> l(m), r(m);
        auto cal = [&]() -> int {
            stack<int> s;
            for (int i = 0; i < m; ++i) {
                while (!s.empty() && sum[s.top()] >= sum[i]) {
                    r[s.top()] = i;
                    s.pop();
                }
                s.push(i);
            }
            while (!s.empty()) {
                r[s.top()] = m;
                s.pop();
            }
            for (int i = m-1; i >= 0; --i) {
                while (!s.empty() && sum[s.top()] > sum[i]) {
                    l[s.top()] = i;
                    s.pop();
                }
                s.push(i);
            }
            while (!s.empty()) {
                l[s.top()] = -1;
                s.pop();
            }
            // 计算矩形个数
            int res = 0;
            for (int i = 0; i < m; ++i) {
                res += sum[i] * (i - l[i]) * (r[i] - i);
            }
            return res;
        };
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mat[i][j]) sum[j] += 1;
                else sum[j] = 0;
            }
            ans += cal();
        }
        return ans;
    }
};
