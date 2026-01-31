class Solution {
public:
    int minimumDistance(vector<vector<int>>& points) {
        int n = points.size();

        vector<pair<int, int>> p[2];
        for (int i = 0; i < n; ++i) {
            int x = points[i][0], y = points[i][1];
            p[0].emplace_back(x + y, i);
            p[1].push_back(-x + y, i);
        }
        sort(p[0].begin(), p[0].end());
        sort(p[1].begin(), p[1].end());

        auto cal = [&](int ind) -> int {
            vector<vector<int>> arr[2];
            for (int i = 0; i < n; ++i) {
                if (i == ind) continue;
                int x = points[i][0], y = points[i][1];
                arr[0].push_back(x + y);
                arr[1].push_back(-x + y);
            }
            sort(arr[0].begin(), arr[0].end());
            sort(arr[1].begin(), arr[1].end());
            return max(arr[0][n - 1] - arr[0][0], arr[1][n - 1] - arr[1][0]);
        };

        int ans = INT_MAX;
        ans = min(ans, cal(p[0][0].second));
        ans = min(ans, cal(p[0][n - 1].second));
        ans = min(ans, cal(p[1][0].second));
        ans = min(ans, cal(p[1][n - 1].second));
        return ans;
    }
};