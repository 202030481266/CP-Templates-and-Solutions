class Solution {
    typedef long long ll;
    typedef pair<ll, int> pii;
public:
    long long kSum(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<pii> q;
        ll sum = 0;
        for (int& c : nums) {
            if (c >= 0) sum += c;
            else c = -c;
        }
        sort(nums.begin(), nums.end());
        q.emplace(sum, 0);
        while (--k) {
            auto [s, i] = q.top();
            q.pop();
            if (i < n) {
                q.emplace(s - nums[i], i + 1);
                if (i) q.emplace(s - nums[i] + nums[i - 1], i + 1);
            }
        }
        return q.top().first;
    }

};