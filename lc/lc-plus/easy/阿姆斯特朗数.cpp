class Solution {
public:
    int q_pow(long long x, int y) {
        int res = 1;
        for(; y; y >>= 1) {
            if (y & 1) res = res * x;
            x = x * x;
        }
        return res;
    }
    bool isArmstrong(int n) {
        int sum = 0, x = n;
        vector<int> a;
        while (x) {
            a.push_back(x % 10);
            x /= 10;
        }
        for (int& v : a) {
            sum += q_pow(v, a.size());
        }
        return sum == n;
    }
};