class Solution {
public:
    int maxIntersectionCount(vector<int>& y) {
        // 扫描线原理 
        int n = y.size();

        vector<pair<int, int>> p;

        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                if (y[1] > y[0]) p.emplace_back(y[0], 0);
                else p.emplace_back(y[0], 3);
            }
            else if (i == n - 1) {
                if (y[n - 1] < y[n - 2]) p.emplace_back(y[n - 1], 0);
                else p.emplace_back(y[n - 1], 3);
            }
            else if (y[i] > y[i - 1] && y[i] > y[i + 1]) p.emplace_back(y[i], 1);
            else if (y[i] < y[i - 1] && y[i] < y[i + 1]) p.emplace_back(y[i], 2);
        }

        sort(p.begin(), p.end());

        int cur = 0, ans = 0, tot = 0;
        for (int i = 0; i < p.size(); ++i) {
            int j = i;
            while (j < p.size() && p[j].first == p[i].first) {
                if (p[j].second == 0) ++cur;
                else if (p[j].second == 3) --tot;
                else if (p[j].second == 2) ++cur, ++tot;
                else if (p[j].second == 1) --cur, --tot;
                ++j;
            }
            ans = max(ans, max(cur, cur + tot));
            cur += tot;
            tot = 0;
            i = j - 1;
        }
        return ans;
    }
};