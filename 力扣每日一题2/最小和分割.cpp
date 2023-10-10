class Solution {
public:
    int splitNum(int num) {
        vector<int> a;
        int xx = num;
        while (xx) {
            if (xx % 10) 
                a.push_back(xx % 10);
            xx /= 10;
        }
        sort(a.begin(), a.end());
        int n = a.size(), x = n / 2, ans = 0, start = 0;
        if (n & 1) {
            ans += a[0] * pow(10, x);
            start = 1;
        }
        for (int i = start, j = x - 1; i < n; i += 2, --j) {
            ans += (a[i] + a[i + 1]) * pow(10, j);
        }
        return ans;
    }
};