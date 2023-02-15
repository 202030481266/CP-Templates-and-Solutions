// https://leetcode.cn/problems/sum-of-subarray-minimums/
// 经典单调栈问题，对于以ai为开始的子数组，需要找到右边第一个小于ai的数字


class Solution {
public:
    static constexpr int mod = 1000000007;
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        vector<int> a(n, -1);
        vector<int> b(n);
        stack<int> s;

        for (int i = 0; i < n; ++i) {
            while (!s.empty() && arr[s.top()] > arr[i]) {
                int u = s.top();
                s.pop();
                a[u] = i;
            }
            s.push(i);
        }
        int ans = 0;
        for (int i = n - 1; i >= 0; --i) {
            int v = a[i];
            // i ~ n - 1
            if (v == -1) 
                b[i] = (n - i) * arr[i] % mod;
            else {
                // i ~ v - 1
                b[i] = (b[i] + arr[i] * (v - i) % mod) % mod;
                // v ~ n - 1
                b[i] = (b[i] + b[v]) % mod;
            }
            ans = (ans + b[i]) % mod;
        }
        return ans;
    }
};