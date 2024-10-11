#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<int> findMaximums(vector<int>& nums) {
        // 单调桟 + 区间更新
        int n = nums.size();
        stack<int> s;
        vector<int> left(n,-1), right(n,n);
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && nums[s.top()] > nums[i]) {
                right[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        s = stack<int>();
        for (int i = n-1; i >= 0; --i) {
            while (!s.empty() && nums[s.top()] > nums[i]) {
                left[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        vector<int> ans(n,0);
        for (int i = 0; i < n; ++i) {
            // (l,r)
            int l = left[i], r = right[i], mx = r-l-1;
            ans[mx-1] = max(ans[mx-1], nums[i]);
        }
        int mx = ans[n-1];
        for (int i = n-2; i >= 0; --i) {
            mx = max(mx, ans[i]);
            ans[i] = mx;
        }
        return ans;
    }
};