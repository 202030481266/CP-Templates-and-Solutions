class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int& i, int& j){
            if (intervals[i][0] == intervals[j][0])
                return intervals[i][1] < intervals[j][1];
            return intervals[i][0] < intervals[j][0];
        });
        vector<int> ans;
        for (auto& q : intervals) {
            int l = -1, r = n - 1;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (intervals[ids[mid]][0] >= q[1]) r = mid;
                else l = mid;
            }
            if (intervals[ids[r]][0] >= q[1]) ans.push_back(ids[r]);
            else ans.push_back(-1);
        }
        return ans;
    }
};