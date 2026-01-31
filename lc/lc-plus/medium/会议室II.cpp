class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<pair<int, int>> arr;

        for (auto& m : intervals) {
            arr.emplace_back(m[0], 1);
            arr.emplace_back(m[1], -1);
        }
        sort(arr.begin(), arr.end());
        int ans = 0, cur = 0;
        for (int i = 0; i < arr.size(); ++i) {
            cur += arr[i].second;
            ans = max(ans, cur);
        }
        return ans;
    }
};