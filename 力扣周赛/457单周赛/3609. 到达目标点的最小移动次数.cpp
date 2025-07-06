#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        if (sx == 0 && sy == 0) {
            if (tx != 0 || ty != 0) return -1;
            return 0;
        }
        if (sx == tx && sy == ty) return 0;
        int res;
        if (tx > ty) {
            if (tx - ty <= ty) {
                res = minMoves(sx, sy, tx - ty, ty);
            }
            else {
                if (tx % 2) return -1;
                res = minMoves(sx, sy, tx / 2, ty);
            }
        }
        else if (tx < ty) {
            if (ty - tx <= tx) {
                res = minMoves(sx, sy, tx, ty - tx);
            }
            else {
                if (ty % 2) return -1;
                res = minMoves(sx, sy, tx, ty / 2);
            }
        }
        else {
            if (sx == 0) {
                res = minMoves(sx, sy, 0, ty);
            }
            else if (sy == 0) {
                res = minMoves(sx, sy, tx, 0);
            }
            else return -1;
        }
        return res == -1 ? -1 : res + 1;
    }
};