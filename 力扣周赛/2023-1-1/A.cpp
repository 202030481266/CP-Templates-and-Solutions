class Solution {
public:
    int countDigits(int num) {
        vector<int> a;
        int x = num;
        while (x) {
            a.emplace_back(x % 10);
            x /= 10;
        }
        int ans = 0;
        for (auto c : a) {
            if (num % c == 0) ans++;
        }
        return ans;
    }
};