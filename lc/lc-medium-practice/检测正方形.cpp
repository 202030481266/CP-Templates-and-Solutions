#include <bits/stdc++.h>
using namespace std;

const int N = 1001; // [0,1001)
class DetectSquares {
public:
    unordered_map<int, int> points[N];
    unordered_map<int, int> cnt;
    DetectSquares() {}
    
    void add(vector<int> point) {
        // 更新 points
        points[point[1]][point[0]]++;
        // 更新cnt
        cnt[point[0]*N + point[1]]++;
    }
    
    int count(vector<int> point) {
        int ans = 0;
        // x1, y, x2, y, 
        // x1, y+abs(x1-x2) / x1, y-abs(x1-x2)
        // x2, y+abs(x1-x2) / x2, y-abs(x1-x2)
        int y = point[1], x1 = point[0];
        for (auto [x2, c] : points[y]) {
            if (x2 == x1) continue;
            int d = abs(x1 - x2);
            // type1
            ans += c * cnt[x1*N + y + d] * cnt[x2*N + y + d];
            // type2
            if (y - d >= 0) // 这是一个坑
                ans += c * cnt[x1*N + y - d] * cnt[x2*N + y - d];
        }
        return ans;
    }
};
