#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;


class Solution {
public:
    vector<int> maximumLengthOfRanges(vector<int>& nums) {
        stack<int> s;
        int n = nums.size();
        vector<int> left(n, -1), right(n, n);
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && nums[s.top()] < nums[i]) {
                right[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        s = stack<int>{};
        for (int i = n-1; i >= 0; --i) {
            while (!s.empty() && nums[s.top()] < nums[i]) {
                left[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = right[i] - left[i] - 1;
        }
        return ans;
    }
};