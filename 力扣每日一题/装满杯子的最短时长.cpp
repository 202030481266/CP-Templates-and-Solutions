class Solution {
public:
    int fillCups(vector<int>& amount) {
        sort(amount.begin(), amount.end());
        return solve(amount[0], amount[1], amount[2]);
    }
    int solve(int a, int b, int c) {
        if (a + b <= c) return c;
        if (a != b) {
            return solve(a, a, c - (b - a)) + (b - a);
        }
        // a == b && a + b > c;
        int d = (c & 1 ? c / 2 + 1 : c / 2);
        return (a - d) + (c & 1 ? c + 1 : c);
    }
};