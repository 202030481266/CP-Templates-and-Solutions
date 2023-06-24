class Solution {
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        int n = nums.size();
        for (auto& c : nums) c = (threshold / c + 1);
        vector<int> left(n, -1), right(n, n);
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && nums[s.top()] < nums[i]) {
                right[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        s = stack<int>{};
        for (int i = n - 1; i >= 0; --i) {
            while (!s.empty() && nums[s.top()] < nums[i]) {
                left[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        for (int i = 0; i < n; ++i) 
            if (right[i] - left[i] - 1 >= nums[i]) 
                return nums[i];
        return -1;
    }
};