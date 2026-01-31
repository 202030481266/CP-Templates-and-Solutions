class Solution {
public:
    int alternateDigitSum(int n) {
        vector<int> a;
        int x = n;
        while (x) {
            a.emplace_back(x % 10);
            x /= 10;
        }
        int ans = 0, cnt = 1;
        for (int i = a.size() - 1; i >= 0; --i) {
            if (cnt == 1) ans += a[i];
            else ans -= a[i];
            cnt ^= 1;
        }
        return ans;
    }
};