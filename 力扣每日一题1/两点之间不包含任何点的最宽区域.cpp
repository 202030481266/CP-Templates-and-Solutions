class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        int n = points.size();

        vector<int> a;
        for (auto c : points) a.emplace_back(c[0]);

        sort(a.begin(), a.end());
        int ans = 0;
        for (int i = 1; i < n; ++i) {
            ans = max(ans, a[i] - a[i - 1]);
        }
        return ans;
    }
};