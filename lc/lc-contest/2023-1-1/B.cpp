class Solution {
public:
    map<long long, int> factorize(long long n) {
        map<long long, int> factors;
        for (int d = 2; (long long)d * d <= n; d++) {
            while (n % d == 0) {
                ++factors[d];
                n /= d;
            }
        }
        if (n > 1) {
            ++factors[n];
        }
        return factors;
    }
    int distinctPrimeFactors(vector<int>& nums) {
        set<long long> ans;
        for (auto c : nums) {
            auto t = factorize(c);
            for (map<long long,int>::iterator it = t.begin(); it != t.end(); it++)
                ans.insert(it->first);
        }
        return ans.size();
    }
};