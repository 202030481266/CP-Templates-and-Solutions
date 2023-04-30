class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        int x = min({a, b, c}), y = max({a, b, c}), z = a + b + c - x - y;
        int mx = y - x - 2; // 一步一步收缩
        if (mx == 0) return {0, 0}; // 已经是连续的
        if (y - z == 1 || y - z == 2 || z - x == 1 || z - x == 2) return {1, mx};
        return {2, mx};
    }
};