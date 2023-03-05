class Solution {
public:
    map<int, int> factorize(int n) {
        map<int, int> factors;
        for (int d = 2; (int)d * d <= n; d++) {
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

    int findValidSplit(vector<int>& nums) {
        int n = nums.size();
        
        if (n < 2) return -1;
        
        vector<int> a(1000000, INT_MAX), b(1000000, INT_MIN);
        unordered_set<int> s;

        for (int i = 0; i < n; ++i) {
            auto factors = factorize(nums[i]);
            for (auto it : factors) {
                a[it.first] = min(a[it.first], i);
                b[it.first] = max(b[it.first], i);
                s.emplace(it.first);
            }
        }
        vector<pair<int,int>> vec;
        for (auto c : s) {
            vec.emplace_back(make_pair(a[c], b[c]));
        }
        sort(vec.begin(), vec.end());
        int p = 0;

        if (vec.size() == 0) return 0;
        if (vec.size() == 1) return -1;
        
        int i = 0, j = 1, mx = vec[0].second;
        while (j < vec.size() && vec[j].first <= mx) {
            mx = max(mx, vec[j++].second);
        }
        if (j == vec.size()) return -1;
        return mx;
    }
};