#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

class Solution {
public:
    long long minMaxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        stack<int> st;
        vector<int> mn_l(n, -1), mn_r(n, n);
        vector<int> mx_l(n, -1), mx_r(n, n);
        // mn_r
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                mn_r[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        st=stack<int>{};
        // mn_l
        for (int i = n-1; i >= 0; --i) {
            while (!st.empty() && nums[st.top()] > nums[i]) {
                mn_l[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        st=stack<int>{};
        // mx_r
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                mx_r[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        st=stack<int>{};
        // mx_l
        for (int i = n-1; i >= 0; --i) {
            while (!st.empty() && nums[st.top()] < nums[i]) {
                mx_l[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        ll ans = 0;
        auto f = [&](ll left, ll right) -> ll {
            if (left < right) swap(left, right);
            // [0, k-1]
            if (k-1 < right) {
                // [0, right-1] -> [1, right]
                // [0, k-1] -> [1, k]
                return 1ll*k*(k+1)/2;
            }
            if (k-1 <= left) {
                // [0, right-1] -> [1, right]
                // [right, k-1] -> right+1
                return (1ll*(right+1)*right/2 + (k-right)*(right+1));
            }
            ll res = (1ll*(right+1)*right/2 + (left-right+1)*(right+1));
            // [0, right-1] -> [1, right]
            // [right, left] -> right+1
            // [left+1, k-1] -> [right, 1]
            ll up = min(left + right, 1ll*(k-1))-left;
            // right, right-1, ..., right-up+1
            return (res + 1ll*(right*2-up+1)*up/2);
        };
        for (int i = 0; i < n; ++i) {
            ll cnt = 0;
            cnt = (cnt + f(i-mn_l[i]-1, mn_r[i]-i-1));
            cnt = (cnt + f(i-mx_l[i]-1, mx_r[i]-i-1));
            ans = (ans + cnt * nums[i]);
        }
        return ans;
    }
};