// 构造+数学
class Solution {
public:
    int makeTheIntegerZero(int num1, int num2) {
        if (num2 > 0 && num1 < num2) return -1;
        long long tmp, steps;
        for (int i = 1; i <= 100; ++i) {
            tmp = num1 - 1ll * i * num2;
            if (tmp < 0) break;
            steps = __builtin_popcountll(tmp);
            if (steps > 0 && steps <= 1ll * i && tmp >= i) return i; 
        }
        return -1;
    }
};