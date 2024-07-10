// https://leetcode.cn/problems/find-a-value-of-a-mysterious-function-closest-to-target/description/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int N = 100005, inf = ~0u >> 1;
int s[N], s1[N], l, l1;
class Solution
{
public:
    int closestToTarget(vector<int> &a, int t)
    {
        int n = a.size(), ans = inf;
        l = l1 = 0;
        s[0] = s1[0] = inf;
        for (int i = 0; i < n; ++i)
        {
            s1[l1 + 1] = s1[l1] & a[i];
            ++l1;
            while ((s[l]&s1[l1]) < t)
            {
                if (!l)
                {
                    l = (l1 + 1) / 2;
                    for (int j = 1; j <= l; ++j)s[j] = s[j - 1] & a[i - l1 + l + 1 - j];
                    l1 -= l;
                    for (int j = 1; j <= l1; ++j)s1[j] = s1[j - 1] & a[i - l1 + j];
                }
                --l;
            }
            ans = min(ans, (s[l] & s1[l1]) - t);
            if (i >= l + l1)ans = min(ans, t - (s[l] & s1[l1] & a[i - l - l1]));
        }
        return ans;
    }
};


// https://leetcode.cn/problems/shortest-subarray-with-or-at-least-k-ii/

int s0[200010], s1[200010], l, l1;

class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        if (k == 0) return 1; // 特判一下
        int n = nums.size(), ans = 0x3f3f3f3f;
        s0[0] = s1[0] = 0;
        l = l1 = 0;
        for (int i = 0; i < n; ++i) {
            s1[l1 + 1] = s1[l1] | nums[i];
            ++l1;
            while ((s1[l1] | s0[l]) >= k) {
                ans = min(ans, l1 + l);
                if (l == 0) {
                    // 需要对半划分
                    l = (l1 + 1) / 2;
                    for (int j = 1; j <= l; ++j) {
                        // 将区间[1,l0]划分出去，但是记得是从右到左进栈
                        s0[j] = s0[j - 1] | nums[i - l1 + l + 1 - j];
                    }
                    l1 -= l;
                    for (int j = 1; j <= l1; ++j) {
                        // 重新进行一个计算
                        s1[j] = s1[j - 1] | nums[i - l1 + j];
                    }
                }
                else --l;
            }
        }
        return ans == 0x3f3f3f3f ? -1 : ans;
    }
};