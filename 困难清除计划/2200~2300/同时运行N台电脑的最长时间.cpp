class Solution {
public:
    long long maxRunTime(int n, vector<int> &batteries) {
        long tot = accumulate(batteries.begin(), batteries.end(), 0L);
        long l = 0, r = tot / n;
        while (l < r) {
            long x = (l + r + 1) / 2, sum = 0;
            for (long b : batteries) {
                sum += min(b, x);
            }
            if (n * x <= sum) {
                l = x;
            } else {
                r = x - 1;
            }
        }
        return l;
    }
};