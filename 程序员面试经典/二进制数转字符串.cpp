class Solution {
public:
    static constexpr double eps = 1e-7;
    string printBin(double num) {
        int cur = 30;
        string ans = "0.";
        while (cur-- && (num > eps)) {
            num = num * 2;
            if (num >= 1) ans += '1', num -= 1;
            else ans += '0';
        }
        return (num < eps) ? ans : "ERROR";
    }
};