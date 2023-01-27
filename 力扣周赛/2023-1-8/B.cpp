class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, less<int>> q;
        for (auto c : nums) q.emplace(c);

        long long ans = 0;
        while (k--) {
            auto t = q.top();
            q.pop();
            ans += t;
            q.emplace(ceil(t / 3.0));
        }
        return ans;
    }
};