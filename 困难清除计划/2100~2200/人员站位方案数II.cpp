class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        int n = points.size();
        sort(points.begin(), points.end());

        // group points by x axis
        vector<vector<int>> group(1);
        group[0].push_back(0);
        for (int i = 1; i < n; ++i) {
            if (points[i][0] != points[i - 1][0]) {
                group.push_back(vector<int>{i});
            }
            else group[group.size() - 1].push_back(i);
        }
        vector<int> p(group.size());
        int ans = 0;
        for (int i = 0; i < group.size(); ++i) {
            fill(p.begin() + i, p.end(), 0);
            for (int j = 0; j < group[i].size(); ++j) {
                // y is ascend!
                int y = points[group[i][j]][1];
                int start = (j > 0 ? points[group[i][j - 1]][1] : INT_MIN);
                int res = (j > 0 ? 1 : 0);
                for (int k = i + 1; k < group.size(); ++k) {
                    while (p[k] < group[k].size() && points[group[k][p[k]]][1] <= y) {
                        ++p[k];
                    }
                    if (p[k] - 1 >= 0 && points[group[k][p[k] - 1]][1] > start) {
                        ++res;
                        start = points[group[k][p[k] - 1]][1];
                    }
                }
                ans += res;
            }
        }
        return ans;
    }
};