class Solution {
public:
    using pii = pair<int, int>;
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        vector<pii> a;
        for (int i = 0; i < n; ++i)
            a.push_back({nums[i], i});

        sort(a.begin(), a.end());
        priority_queue<int, vector<int>,greater<int>> q;

        int pre = 0;
        vector<int> ans(n);
        q.push(a[0].second);
        for (int i = 1; i < n; ++i) {
            if (a[i].first - a[i - 1].first > limit) {
                while (!q.empty()) {
                    ans[q.top()] = a[pre++].first;
                    q.pop();
                }
            }
            q.push(a[i].second);
        }
        while (!q.empty()) {
            ans[q.top()] = a[pre++].first;
            q.pop();
        }
        return ans;
    }
};