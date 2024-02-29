class Solution {
public:
    int minDayskVariants(vector<vector<int>>& points, int k) {
        // 需要二分答案然后判断
        // 将坐标轴旋转45度，就可以了，因为一个点的相同距离的集合是一个菱形，旋转后就变成了正方形，然后滑动窗口判断是否存在k个正方形相交即可
        vector<pair<int, int>> newPoints;
        for (auto& p : points)
            newPoints.emplace_back(p[0] + p[1], p[1] - p[0]);
        sort(newPoints.begin(), newPoints.end());

        auto check = [&](int t) {
            map<int,int> m;
            int pos = 0;
            for (auto&& [x, y] : newPoints) {
                m[y]++;
                while (x - newPoints[pos].first > 2 * t) {
                    --m[newPoints[pos].second];
                    
                    pos++;
                }
                for (auto i = m.begin(); i != m.end(); ++i) {
                    auto cur = m.upper_bound(i->first + 2 * t);
                    int cnt = 0;
                    for(auto j = i; j != cur; ++j)
                        cnt += j->second;
                    if (cnt >= k&&!((x+i->first)%2 && 2*t == x - newPoints[pos].first && (--cur)->first-2*t == i->first))
                        return true;
                }
            }
            return false;
        };

        int l = 0, r = 1e9;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
};

