#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;


class Solution {
public:
    long long bowlSubarrays(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        vector<int> left(n, -1), right(n, n);
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && nums[i] >= nums[st.top()]) {
                right[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        while (!st.empty()) st.pop();
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && nums[i] >= nums[st.top()]) {
                left[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            // (left[i], right[i])
            if (left[i] != -1 && i - left[i] >= 2) ++ans;
            if (right[i] != n && right[i] - i >= 2) ++ans;
        }
        return ans;
    }
};