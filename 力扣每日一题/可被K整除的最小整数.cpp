// 模拟除法+余数判环
class Solution {
public:
    int smallestRepunitDivByK(int k) {
        if (k % 2 == 0 || k % 5 == 0) return -1;
        int n = 1, T = k + 1, ans = 1;  // 因为有关k的余数是固定的，所以重复有限次数就可以了
        while (T--) {
            while (n < k) {
                n = n * 10 + 1;
                ++ans;
            }
            n %= k;
            if (n == 0) break;
        }
        if (T < 0) return -1;
        return ans;
    }
};