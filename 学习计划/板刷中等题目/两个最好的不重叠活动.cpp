class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        int n = events.size(), ans = 0;
        sort(events.begin(), events.end(), [&](auto& x, auto& y){
            if (x[1]==y[1]) return x[0] < y[0];
            return x[1] < y[1];
        });
        vector<int> mx(n);
        mx[0] = events[0][2];
        for (int i = 1; i < n; ++i)
            mx[i] = max(mx[i-1], events[i][2]);
        for (int i = 0; i < n; ++i) {
            int l = 0, r = i;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                if (events[mid][1] < events[i][0]) l = mid;
                else r = mid;
            }
            if (events[l][1] < events[i][0])
                ans = max(ans, mx[l] + events[i][2]);
            else ans = max(ans, events[i][2]);
        }
        return ans;
    }
};