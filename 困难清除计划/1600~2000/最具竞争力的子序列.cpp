class Solution {
public:
    // 单调栈模板题目
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int n = nums.size();
        stack<int> s;

        for (int i = 0; i < nums.size(); ++i) {
            while (!s.empty() && (s.size() + n - i) > k && nums[s.top()] > nums[i]) s.pop();
            s.push(i);
        }
        while (s.size() > k) s.pop();
        vector<int> a(k);
        for (int i = k; i; --i) {
            a[i] = nums[s.top()];
            s.pop();
        }
        return a;
    }
};