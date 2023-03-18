class Solution {
public:
    int maximizeGreatness(vector<int>& nums) {
        priority_queue<int> q;
        for (auto c : nums) q.emplace(c);

        sort(nums.begin(), nums.end());
        int ans = 0;
        int n = nums.size();
        for (int i = n - 1; i >= 0; --i) {
            if (q.top() > nums[i]) {
                ++ans;
                q.pop();
            }
        }
        return ans;
    }
};