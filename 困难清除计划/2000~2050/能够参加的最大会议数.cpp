// https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended/
// set 维护可用集合 + 贪心排序


class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        int n = events.size();

        sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b){
            return a[1] < b[1];
        });

        set<int> s;
        for (int i = 1; i <= events[n - 1][1] + 1; ++i)
            s.emplace(i);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            auto it = s.lower_bound(events[i][0]);
            if (it != s.end() && *it <= events[i][1]) {
                ++ans;
                s.erase(it);
            }
        }
        return ans;
    }
};