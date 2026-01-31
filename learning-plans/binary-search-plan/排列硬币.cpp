class Solution {
public:
    int arrangeCoins(int n) {
        // 1 + 2 + ...  + k 需要的硬币数量： (k + 1) * k / 2
        if (n == 1)
            return 1;
        int l = 1, r = n;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            if (1ll * (mid + 1) * mid / 2 <= 1ll * n)
                l = mid;
            else
                r = mid;
        }
        return l;
    }
};