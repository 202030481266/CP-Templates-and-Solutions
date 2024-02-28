// 反悔贪心
class Solution {
public:
    int makePrefSumNonNegative(vector<int>& nums) {
        int n = nums.size();
        priority_queue<int> q;
        long long sum = 0;
        int ans = 0;
        for (int& v : nums) {
            sum += v;
            if (v < 0) q.push(-v);
            while (sum < 0 && !q.empty()) {
                sum += q.top();
                q.pop();
                ++ans;
            }
        } 
        return ans;
    }
};