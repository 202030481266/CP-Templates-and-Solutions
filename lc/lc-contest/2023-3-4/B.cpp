class Solution {
public:
    long long coloredCells(int n) {
        long long k = 1ll * n * (n - 1) / 2;
        return 4 * k + 1;
    }
};