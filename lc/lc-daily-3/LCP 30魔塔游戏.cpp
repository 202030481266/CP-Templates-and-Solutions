class Solution {
public:
    int magicTower(vector<int>& nums) {
        int n = nums.size();
        long long positive = 0, negative = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) positive += nums[i];
            else if (nums[i] < 0) negative -= nums[i];
        }
        if (positive < negative) return -1;
        priority_queue<int> q;
        long long life = 1;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) life += nums[i];
            else if (nums[i] < 0) {
                life += nums[i];
                q.push(-nums[i]);
                while (!q.empty() && life <= 0) {
                    life += q.top();
                    q.pop();
                    ++ans;
                }
            }
        }
        return ans;
    }
};