class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<pair<int,int>> a;
        for (int i = 0; i < n; i++) 
            a.emplace_back(make_pair(nums2[i], nums1[i]));
        sort(a.begin(), a.end());

        long long temp = 0;
        vector<long long> dp(n, 0);
        priority_queue<long long, vector<long long>, greater<long long>> q;
        for (int i = n - 1; i >= n - k; --i) {
            temp += a[i].second;
            q.emplace(a[i].second);
        }
        // 0~n-k
        long long ans = INT_MIN;
        for (int i = n - k; i >= 0; --i) {
            ans = max(ans, temp * a[i].first);
            if (i >= 1 && q.top() < a[i - 1].second) {
                long long x = q.top();
                temp += (a[i - 1].second - x);
                q.pop();
                q.emplace(a[i - 1].second);
            }
        }
        return ans;
    }
};