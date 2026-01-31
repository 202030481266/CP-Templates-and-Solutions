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
    int maximumPrimeDifference(vector<int>& nums) {
        vector<int> primes = generate_primes_linear_time(101);
        // cout << "done" << endl;
        vector<int> is_prime(200);
        for (int& v : primes)
            is_prime[v] = 1;
        int n = nums.size();
        int l = -1, r = -1;
        for (int i = 0; i < n; ++i) {
            if (is_prime[nums[i]]) {
                if (l == -1) l = i, r = i;
                else r = i;
            }
        }
        return r - l;
    }
};