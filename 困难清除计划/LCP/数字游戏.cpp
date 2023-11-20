class Solution {
    static constexpr int mod = 1e9 + 7;
public:
    vector<int> numsGame(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i)
            nums[i] -= i;

        vector<int> ans;

        // 维护中位数
        priority_queue<int> q1; // 最大堆
        priority_queue<int, vector<int>, greater<int>> q2; // 最小堆
        long long s1 = 0, s2 = 0;

        for (int i = 0; i < n; ++i) {
            if (q1.size() > q2.size()) q2.push(nums[i]), s2 = (s2 + nums[i]) % mod;
            else q1.push(nums[i]), s1 = (s1 + nums[i]) % mod;
            while (!q1.empty() && !q2.empty() && q1.top() > q2.top()) {
                int u = q1.top(), v = q2.top();
                q1.pop(), s1 = (s1 - u + mod) % mod;
                q2.pop(), s2 = (s2 - v + mod) % mod;
                q1.push(v), s1 = (s1 + v) % mod;
                q2.push(u), s2 = (s2 + u) % mod;
            }
            long long mid = q1.top();
            ans.push_back((q1.size() * mid - s1 + s2 - q2.size() * mid + mod) % mod);
        }

        return ans;
    }
};