class Solution {
public:
    vector<int> generate_primes_linear_time(int n) {
        vector<int> lp(n + 1);
        vector<int> primes;
        for (int i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                primes.push_back(i);
            }
            for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= n; ++j)
                lp[i * primes[j]] = primes[j];
        }
        return primes;
    }

    vector<int> closestPrimes(int left, int right) {
        auto t = generate_primes_linear_time(right);
        int pos = 0, n = t.size();
        while (pos < n && t[pos] < left) ++pos;

        vector<int> ans{-1, -1};
        if (pos == n - 1) return ans; 
        int last = -1, res = INT_MAX;
        for (int i = pos; i < n; i++) {
            if (last == -1) last = t[i];
            else {
                if (t[i] - last < res) {
                    res = t[i] - last;
                    ans[0] = last, ans[1] = t[i];
                }
                last = t[i];
            }
        }
        return ans;
    }
};