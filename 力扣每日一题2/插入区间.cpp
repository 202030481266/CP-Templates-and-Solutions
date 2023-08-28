typedef pair<int, int> pii;
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<pii> a;
        intervals.push_back(newInterval);
        for (auto& c : intervals) {
            a.emplace_back(c[0], 0);
            a.emplace_back(c[1], 1);
        }
        sort(a.begin(), a.end());
        int k = 0, l;
        vector<vector<int>> ans;
        for (int i = 0; i < a.size(); ++i) {
            if (a[i].second == 0) {
                ++k;
                if (k == 1) l = a[i].first;
            }
            else {
                --k;
                if (k == 0) ans.emplace_back(vector<int>{l, a[i].first});
            }
        }
        return ans;
    }
};