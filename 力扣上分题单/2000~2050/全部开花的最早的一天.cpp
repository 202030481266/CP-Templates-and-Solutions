// https://leetcode.cn/problems/earliest-possible-day-of-full-bloom/



class Solution {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        vector<pair<int, int>> a;

        int n = plantTime.size();
        for (int i = 0; i < n; ++i) {
            a.emplace_back(growTime[i], plantTime[i]);
        }
        sort(a.begin(), a.end(), greater<pair<int, int>>());
        int ans = a[0].first + a[0].second;
        int cur = a[0].second;
        for (int i = 1; i < n; ++i) {
            // plant time is start from cur
            ans = max(ans, cur + a[i].first + a[i].second);
            cur += a[i].second;
        }
        return ans;
    }
};