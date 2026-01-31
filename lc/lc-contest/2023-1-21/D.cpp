class Solution {
public:
    bool isReachable(int targetX, int targetY) {
        int x = targetX, y = targetY;
        while ((x & 1) == 0) x >>= 1;
        while ((y & 1) == 0) y >>= 1;
        return __gcd(x, y) == 1;
    }
};