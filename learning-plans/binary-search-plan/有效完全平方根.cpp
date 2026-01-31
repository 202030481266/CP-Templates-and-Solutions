class Solution {
public:
    bool isPerfectSquare(int num) {
        if (num == 1) return true;
        int l = 1, r = num;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            if (1ll * mid * mid <= 1ll * num) l = mid;
            else r = mid;
        }
        return l * l == num;
    }
};