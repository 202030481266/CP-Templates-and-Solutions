#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int N = 1e5 + 7;
int s[4][N], p[4];

// 单调队列其实也可以做，同时用两个单调队列来维护
// 单调递减队列维护最大值，单调递增队列维护最小值
// 这里使用了一种更加高级的维护前缀的方法

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size(), ans = 0;
        s[0][0] = s[1][0] = 0; // 最大栈
        s[2][0] = s[3][0] = inf; // 最小栈
        for (int i = 0; i < 4; ++i) p[i] = 0;
        for (int i = 0; i < n; ++i) {
            s[1][p[1]+1] = max(s[1][p[1]], nums[i]);
            s[3][p[3]+1] = min(s[3][p[3]], nums[i]);
            p[1]++, p[3]++;
            while (max(s[1][p[1]], s[0][p[0]]) - min(s[3][p[3]], s[2][p[2]]) > limit) {
                if (!p[0]) {
                    p[0] = (p[1] + 1) / 2;
                    for (int j = 1; j <= p[0]; ++j) {
                        s[0][j] = max(s[0][j-1], nums[i-p[1]+p[0]-j+1]);
                    }
                    p[1] -= p[0];
                    for (int j = 1; j <= p[1]; ++j) {
                        s[1][j] = max(s[1][j-1], nums[i-p[1]+j]);
                    }
                }
                else --p[0];
                if (!p[2]) {
                    p[2] = (p[3] + 1) / 2;
                    for (int j = 1; j <= p[2]; ++j) {
                        s[2][j] = min(s[2][j-1], nums[i-p[3]+p[2]-j+1]);
                    }
                    p[3] -= p[2];
                    for (int j = 1; j <= p[3]; ++j) {
                        s[3][j] = min(s[3][j-1], nums[i-p[3]+j]);
                    }
                }
                else --p[2];
            }
            ans = max(ans, p[1] + p[0]);
        }
        return ans;
    }
};
