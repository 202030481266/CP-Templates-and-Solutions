#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;


// O(nklogU)
class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        vector<vector<int>> left, right, up, down;
        for (int i = 0; i < n; ++i) {
            int x = points[i][0], y = points[i][1];
            if (x == 0) {
                left.push_back({x, y});
            }
            else if (x == side) {
                right.push_back({x, y});
            }
            else if (y == 0) {
                down.push_back({x, y});
            }
            else {
                up.push_back({x, y});
            }
        }

        // 顺时针
        sort(left.begin(), left.end()); 
        sort(up.begin(), up.end());
        sort(right.rbegin(), right.rend());
        sort(down.rbegin(), down.rend());
        vector<vector<int>> ps;
        for (auto &p : left) ps.push_back(p);
        for (auto &p : up) ps.push_back(p);
        for (auto &p : right) ps.push_back(p);
        for (auto &p : down) ps.push_back(p);
        for (int i = 0; i < n; ++i) {
            ps.push_back(ps[i]);
        }
        
        auto cal = [&](int i, int j) -> int {
            return abs(ps[i][0] - ps[j][0]) + abs(ps[i][1] - ps[j][1]);
        };
        
        auto check = [&](int d) -> bool {
            for (int i = n-1; i < 2*n; ++i) {
                int pre = i, cnt = 1, left = max(0, i-n+1);
                // use binary search
                while (cnt < k) {
                    int r = pre-1, l = left, ans = -1;
                    while (l <= r) {
                        int mid = (l + r) >> 1;
                        if (cal(mid, pre) >= d) {
                            if (cal(mid, i) >= d) {
                                ans = mid;
                            }
                            l = mid + 1;
                        }
                        else {
                            if (cal(mid, i) < d && pre < i) { // 这里是最为巧妙的一步
                                l = mid + 1;
                            }
                            else {
                                r = mid - 1;
                            }
                        }
                    }
                    if (ans == -1) {
                        break;
                    }
                    pre = ans;
                    ++cnt;
                }
                if (cnt == k) {
                    return true;
                }
            }
            return false;
        };
        
        int l = 0, r = side + 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                l = mid;
            }
            else {
                r = mid;
            }   
        }
        return l;
    }
};